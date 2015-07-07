/*
** This file is part of toolbox.
** Copyright (C) 2008-2015 by Alan Wise (alanwise@users.sourceforge.net)
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
*** \file messagelog.c
*** \brief messagelog.h implementation.
*** \details Implementation for messagelog.h.
**/


/** Identifier for messagelog.c. **/
#define   MESSAGELOG_C


/****
*****
***** INCLUDES
*****
****/

/**
*** \brief No wrapper macros.
*** \details Expose function prototypes, but not wrapper macros.
**/
#define   MESSAGELOG_NOWRAPPERMACROS
#include  "messagelog.h"
#include  "sysdefs.h"

#include  <stdio.h>
#include  <time.h>
#include  <stdarg.h>


/****
*****
***** DEFINES
*****
****/

/**
*** \internal
*** \brief Output file name.
*** \details Output file name for the message log.
**/
#define   MESSAGELOG_FILENAME   "messagelog.txt"


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

/**
*** \internal
*** \brief Initialized flag.
*** \details Message log initialized.
**/
static int f_Initialized;


/****
*****
***** FUNCTIONS
*****
****/

char const * MessageLog_GetFilenamePointer(void)
{
  return(MESSAGELOG_FILENAME);
}

void MessageLog_Initialize(void)
{
  FILE    *pLogFile;
  time_t  Time;


  /* Initialize if not initialized. */
  if (f_Initialized==0)
  {
    /* Open the debug log and write the time. */
    pLogFile=fopen(MESSAGELOG_FILENAME,"wt");
    if (pLogFile!=NULL)
    {
      Time=time(NULL);
      if (Time!=-1)
        fprintf(pLogFile,"Run time: %s\n\n",ctime(&Time));

      fclose(pLogFile);
    }

    /* Initialize file variables. */
    f_Initialized=!0;
  }

  return;
}

void MessageLog_Printf(char const *pFilename,
    unsigned int LineNumber,unsigned int Type,char const *pFormat,...)
{
  FILE *pLogFile;
  BOOLEAN_T ErrorFlag;
  char const *pType;
  va_list VAList;


  /* Make sure we're initialized.  If this function is being called and
      we're not, the user probably forgot... */
  if (f_Initialized==0)
    MessageLog_Initialize();

  pLogFile=fopen(MESSAGELOG_FILENAME,"at");
  if (pLogFile!=NULL)
  {
    /* Assume success. */
    ErrorFlag=BOOLEAN_FALSE;

    /* Turn the type number into a type string. */
    switch(Type)
    {
      case MESSAGELOGTYPE_ERROR:
        pType="Error";
        break;
      case MESSAGELOGTYPE_WARNING:
        pType="Warning";
        break;
      case MESSAGELOGTYPE_INFORMATION:
        pType="Info";
        break;
      case MESSAGELOGTYPE_TODO:
        pType="Todo";
        break;
      default:
        ErrorFlag=BOOLEAN_TRUE;
        break;
    }

    /* Handle basic parameters. */
    if (ErrorFlag==BOOLEAN_FALSE)
      if (fprintf(pLogFile,"%s\t%u\t%s\t",pFilename,LineNumber,pType)<=0)
        ErrorFlag=BOOLEAN_TRUE;

    /* Handle the callers variable arguments. */
    if (ErrorFlag==BOOLEAN_FALSE)
    {
      va_start(VAList,pFormat);
      vfprintf(pLogFile,pFormat,VAList);
      va_end(VAList);
      fprintf(pLogFile,"\n");
    }

    fclose(pLogFile);
  }

  return;
}


#undef    MESSAGELOG_C
