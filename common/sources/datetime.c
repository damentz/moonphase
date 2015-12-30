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
  size_t Length;


  DEBUGLOG_Printf5("DateTime_Print(%d,%p,%p,%p,%p)",
      DateTimeModeFlag,pTime,pDTFormat,pOptions,ppDateTime);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pTime==NULL) || (pOptions==NULL) || (ppDateTime==NULL) )
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else if ( (DateTimeModeFlag!=0) && (pDTFormat==NULL) )
    ErrorCode=ERRORCODE_INVALIDPARAMETER;
  else if ( (DateTimeModeFlag!=0) && (pDTFormat!=NULL) &&
      (strlen(pDTFormat)>=BUFFER_SIZEOF) )
    ErrorCode=ERRORCODE_INVALIDDATA;
  else
  {
    *pFormat='\0';
    if (DateTimeModeFlag!=0)
    {
      /* Day of week? */
      if (pOptions->Flags&DATETIMEFLAG_SHOWDAYOFWEEK)
      {
        if (pOptions->Flags&DATETIMEFLAG_LONGDAYOFWEEKFORMAT)
          strcat(pFormat,"%A");                       /* Long DOW. */
        else
          strcat(pFormat,"%a.");                      /* Short DOW. */
        strcat(pFormat,", ");                         /* Comma+Space. */
      }

      strcat(pFormat,pDTFormat);                      /* Day, month, year. */

      /* Long month? */
      if (pOptions->Flags&DATETIMEFLAG_LONGMONTHFORMAT)
      {
        pPtr=strstr(pFormat,"%b.");                   /* From short month. */
        if (pPtr!=NULL)
        {
          memcpy(pPtr,"%B",2*sizeof(char));           /* to long month. */
          Length=strlen(pPtr+3);
          memmove(pPtr+2,pPtr+3,Length+1);
        }
      }

      /* 4 digit year? */
      if (pOptions->Flags&DATETIMEFLAG_4DIGITYEAR)
      {
        pPtr=strstr(pFormat,"%y");                    /* From 2 digits. */
        if (pPtr!=NULL)
          memcpy(pPtr,"%Y",2*sizeof(char));           /* to 4 digits. */
      }
      strcat(pFormat," ");                            /* Space. */
    }

    strcat(pFormat,"%I:%M");                          /* Hours:Minutes. */

    /* 24 hour format? */
    if (pOptions->Flags&DATETIMEFLAG_24HOURFORMAT)
    {
      pPtr=strstr(pFormat,"%I");                      /* From am/pm format. */
      if (pPtr!=NULL)
        memcpy(pPtr,"%H",2*sizeof(char));             /* to 24 hour format. */
    }

    /* Show seconds? */
    if (pOptions->Flags&DATETIMEFLAG_SHOWSECONDS)
      strcat(pFormat,":%S");                          /* Colon+Seconds. */

    /* Show AM/PM? */
    if (!(pOptions->Flags&DATETIMEFLAG_24HOURFORMAT))
      strcat(pFormat," %p");            /* AM/PM. */

    if (strftime(pTimeString,BUFFER_SIZEOF,pFormat,pTime)==0)
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
