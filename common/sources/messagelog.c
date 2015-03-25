/*
** This file is part of toolbox.
** Copyright (C) 2008-2013 by Alan Wise (alanwise@users.sourceforge.net)
**
** This program is free software; you can redistribute it and/or modify
**   it under the terms of the GNU General Public License as published by
**   the Free Software Foundation; either version 2 of the License, or
**   (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**   GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
**   along with this program.  If not, see
**     <http://www.gnu.org/licenses/>,
**   or write to the
**     Free Software Foundation, Inc.,
**     59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
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

#if       defined(ENABLE_MESSAGELOG) && !defined(BUILD_PLUGIN)

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

/**
*** \brief Output file name.
*** \details Output file name for the message log.
**/
static char const *f_pMessageLogFileName="messagelog.txt";


/****
*****
***** VARIABLES
*****
****/

/**
*** \brief Initialized flag.
*** \details Message log initialized.
**/
static int f_Initialized;


/****
*****
***** FUNCTIONS
*****
****/

char const * MessageLog_GetFileNamePointer(void)
{
  return(f_pMessageLogFileName);
}

void MessageLog_Initialize(void)
{
  FILE    *pLogFile;
  time_t  Time;


  /* Initialize if not initialized. */
  if (f_Initialized==0)
  {
    /* Open the debug log and write the time. */
    pLogFile=fopen(f_pMessageLogFileName,"wt");
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

void MessageLog_Printf(
    const char *pFilename,int LineNumber,int Type,const char *pFormat,...)
{
  FILE *pLogFile;
  BOOLEAN_T ErrorFlag;
  const char *pType;
  va_list VAList;


  /* Make sure we're initialized.  If this function is being called and
      we're not, the user probably forgot... */
  if (f_Initialized==0)
    MessageLog_Initialize();

  pLogFile=fopen(f_pMessageLogFileName,"at");
  if (pLogFile!=NULL)
  {
    /* Assume success. */
    ErrorFlag=0;

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
        ErrorFlag=!0;
        break;
    }

    /* Handle basic parameters. */
    if (ErrorFlag==0)
      if (fprintf(pLogFile,"%s\t%d\t%s\t",pFilename,LineNumber,pType)<=0)
        ErrorFlag=!0;

    /* Handle the callers variable arguments. */
    if (ErrorFlag==0)
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


#endif    /* defined(ENABLE_MESSAGELOG)  && !defined(BUILD_PLUGIN) */


#undef    MESSAGELOG_C
