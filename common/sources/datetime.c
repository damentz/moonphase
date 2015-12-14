/*
** This file is part of moonphase.
** Copyright (C) 2014-2015 by Alan Wise (alanwise@users.sourceforge.net)
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
*** \file datetime.c
*** \brief datetime.h implementation.
*** \details Implementation file for datetime.h.
**/


/** Identifier for datetime.c. **/
#define   DATETIME_C


/****
*****
***** INCLUDES
*****
****/

#include  "datetime.h"
#ifdef    DEBUG_DATETIME_C
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_DATETIME_C */
#include  "debuglog.h"
#include  "messagelog.h"

#include  <string.h>


/****
*****
***** DEFINES
*****
****/

/**
*** \brief Print buffer size.
*** \details Size (in chars) of the print buffer.
**/
#define   BUFFER_SIZEOF   (2048)

/**
*** \brief Check print buffer limit.
*** \details Checks if the last print operation reached the limit of the print
***   buffer.
**/
#define   CHECKBUFFER(b,s)    if ( (*((b)+(s)-1))!='\0' ) BufferError=!0;


/****
*****
***** DATA TYPES
*****
****/


/****
*****
***** PROTOTYPES
*****
****/


/****
*****
***** DATA
*****
****/


/****
*****
***** VARIABLES
*****
****/


/****
*****
***** FUNCTIONS
*****
****/

ERRORCODE_T DateTime_Print(BOOLEAN_T DateTimeModeFlag,struct tm const *pTime,
    char const *pDTFormat,DATETIMEOPTIONS_T const *pOptions,char **ppDateTime)
{
  ERRORCODE_T ErrorCode;
  char pFormat[BUFFER_SIZEOF];
  char pTimeString[BUFFER_SIZEOF];
  char *pPtr;
  BOOLEAN_T BufferError;
  size_t Length;


  DEBUGLOG_Printf5("DateTime_Print(%d,%p,%p,%p,%p)",
      DateTimeModeFlag,pTime,pDTFormat,pOptions,ppDateTime);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pTime==NULL) || (pOptions==NULL) || (ppDateTime==NULL) )
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else if ( (DateTimeModeFlag!=0) && (pDTFormat==NULL) )
    ErrorCode=ERRORCODE_INVALIDPARAMETER;
  else
  {
    BufferError=0;
    memset(pFormat,0,BUFFER_SIZEOF);
    if (DateTimeModeFlag!=0)
    {
      /* Day of week? */
      if (pOptions->Flags&DATETIMEFLAG_SHOWDAYOFWEEK)
      {
        if (pOptions->Flags&DATETIMEFLAG_LONGDAYOFWEEKFORMAT)
          strncat(pFormat,"%A",BUFFER_SIZEOF);        /* Long DOW. */
        else
          strncat(pFormat,"%a.",BUFFER_SIZEOF);       /* Short DOW. */
        CHECKBUFFER(pFormat,BUFFER_SIZEOF);
        if (BufferError==0)
        {
          strncat(pFormat,", ",BUFFER_SIZEOF);        /* Comma+Space. */
          CHECKBUFFER(pFormat,BUFFER_SIZEOF);
        }
      }

      if (BufferError==0)
      {
        strncat(pFormat,pDTFormat,BUFFER_SIZEOF);     /* Day, month, year. */
        CHECKBUFFER(pFormat,BUFFER_SIZEOF);
      }

      if (BufferError==0)
      {
        /* Long month? */
        if (pOptions->Flags&DATETIMEFLAG_LONGMONTHFORMAT)
        {
          pPtr=strstr(pFormat,"%b.");                 /* From short month. */
          if (pPtr!=NULL)
          {
            memcpy(pPtr,"%B",2*sizeof(char));         /* to long month. */
            CHECKBUFFER(pFormat,BUFFER_SIZEOF);
            if (BufferError==0)
            {
              Length=strlen(pPtr+3);
              memmove(pPtr+2,pPtr+3,Length+1);
            }
          }
        }
      }

      if (BufferError==0)
      {
        /* 4 digit year? */
        if (pOptions->Flags&DATETIMEFLAG_4DIGITYEAR)
        {
          pPtr=strstr(pFormat,"%y");                  /* From 2 digits. */
          if (pPtr!=NULL)
          {
            memcpy(pPtr,"%Y",2*sizeof(char));         /* to 4 digits. */
            CHECKBUFFER(pFormat,BUFFER_SIZEOF);
          }
        }
      }
      if (BufferError==0)
      {
        strncat(pFormat," ",BUFFER_SIZEOF);           /* Space. */
        CHECKBUFFER(pFormat,BUFFER_SIZEOF);
      }
    }

    if (BufferError==0)
    {
      strncat(pFormat,"%l:%M",BUFFER_SIZEOF);         /* Hours:Minutes. */
      CHECKBUFFER(pFormat,BUFFER_SIZEOF);
    }

    if (BufferError==0)
    {
      /* 24 hour format? */
      if (pOptions->Flags&DATETIMEFLAG_24HOURFORMAT)
      {
        pPtr=strstr(pFormat,"%l");                    /* From am/pm format. */
        if (pPtr!=NULL)
        {
          memcpy(pPtr,"%H",2*sizeof(char));           /* to 24 hour format. */
          CHECKBUFFER(pFormat,BUFFER_SIZEOF);
        }
      }
    }

    if (BufferError==0)
    {
      /* Show seconds? */
      if (pOptions->Flags&DATETIMEFLAG_SHOWSECONDS)
      {
        strncat(pFormat,":%S",BUFFER_SIZEOF);         /* Colon+Seconds. */
        CHECKBUFFER(pFormat,BUFFER_SIZEOF);
      }
    }

    if (BufferError==0)
    {
      /* Show AM/PM? */
      if (!(pOptions->Flags&DATETIMEFLAG_24HOURFORMAT))
      {
        strncat(pFormat," %p",BUFFER_SIZEOF);         /* AM/PM. */
        CHECKBUFFER(pFormat,BUFFER_SIZEOF);
      }
    }

    if (BufferError==0)
    {
      if (strftime(pTimeString,BUFFER_SIZEOF,pFormat,pTime)==0)
        BufferError=!0;
    }

    if (BufferError!=0)
      ErrorCode=ERRORCODE_SYSTEMFAILURE;
    else
    {
      *ppDateTime=strdup(pTimeString);
      if (*ppDateTime==NULL)
        ErrorCode=ERRORCODE_OUTOFMEMORY;
      else
        ErrorCode=ERRORCODE_SUCCESS;
    }
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}


#undef    DATETIME_C
