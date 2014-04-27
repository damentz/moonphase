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
*** \file debuglog.c
*** \brief debuglog.h implementation.
*** \details Implementation file for debuglog.h.
**/


/** Identifier for debuglog.c. **/
#define   DEBUGLOG_C


/****
*****
***** INCLUDES
*****
****/

#if       defined(ENABLE_DEBUGLOG) && !defined(BUILD_PLUGIN)

#include  "debuglog.h"

#include  <stdio.h>
#include  <time.h>
#include  <stdarg.h>


/****
*****
***** DEFINES
*****
****/

/**
*** \brief Output file name.
*** \details Output file name for the debug data.
**/
static char const *f_pDebugLogFileName="debuglog.txt";

/**
*** \hideinitializer
*** \brief Indents a line.
*** \details Indents a line according to the indent (function call) depth.
*** \param f Text to print indented.
**/
#define   DebugLog_IndentLine(f) \
    { int Loop; for(Loop=0;Loop<f_LogLevel;Loop++) fprintf(f,"  "); }


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

/**
*** \brief Increase/decrease indent depth.
*** \details Increases or decreases the indent depth.  If the level drops
***     below zero, the level is set to zero and a warning is written into
***     the log file.
*** \param Direction Change indent depth as follows:\n
***     <0 = Decrease indent depth.\n
***     =0 = No change.\n
***     >0 = Increase indent depth.
**/
static void LogLevel(int Direction);


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
*** \brief Indent depth.
*** \details Determines how far to indent.
**/
static int f_LogLevel;

/**
*** \brief Runtime enable/disable flag.
*** \details Enable/disable debug log at runtime.
**/
static int f_EnabledFlag;

/**
*** \brief Initialized flag.
*** \details Debug log initialized.
**/
static int f_Initialized;


/****
*****
***** FUNCTIONS
*****
****/

static void LogLevel(int Direction)
{
  /* 0=do nothing, >0=increment level <0=decrement level. */
  if (Direction>0)
    f_LogLevel++;
  else
  {
    f_LogLevel--;
    if (f_LogLevel<0)
    {
      DebugLog_Printf("Log level is less than 0.\n");
      f_LogLevel=0;
    }
  }

  return;
}

void DebugLog_SetEnabledFlag(int EnabledFlag)
{
  f_EnabledFlag=EnabledFlag;

  return;
}

int DebugLog_GetEnabledFlag(void)
{
  return(f_EnabledFlag);
}

char const * DebugLog_GetFileNamePointer(void)
{
  return(f_pDebugLogFileName);
}

void DebugLog_Initialize(int EnabledFlag)
{
  FILE    *pLogFile;
  time_t  Time;


  /* Initialize if not initialized, otherwise only save the EnabledFlag. */
  if (f_Initialized==0)
  {
    /* Open the debug log and write the time. */
    pLogFile=fopen(f_pDebugLogFileName,"wt");
    if (pLogFile!=NULL)
    {
      Time=time(NULL);
      if (Time!=-1)
        fprintf(pLogFile,"Run time: %s\n\n",ctime(&Time));

      (void)fclose(pLogFile);
    }

    /* Initialize file variables. */
    f_LogLevel=0;
    f_Initialized=!0;
  }

  f_EnabledFlag=EnabledFlag;

  return;
}

void DebugLog_LogIn(void)
{
  LogLevel(1);

  return;
}

void DebugLog_LogOut(void)
{
  LogLevel(-1);

  return;
}

void DebugLog_Printf(char const *pFormat,...)
{
  FILE *pLogFile;
  va_list VAList;


  if (f_EnabledFlag!=0)
  {
    /* Make sure we're initialized.  If this function is being called and
       we're not, the user probably forgot... */
    if (f_Initialized==0)
      DebugLog_Initialize(!0);

    pLogFile=fopen(f_pDebugLogFileName,"at");
    if (pLogFile!=NULL)
    {
      va_start(VAList,pFormat);
      DebugLog_IndentLine(pLogFile);
      (void)vfprintf(pLogFile,pFormat,VAList);
      va_end(VAList);
      (void)fclose(pLogFile);
    }
  }

  return;
}


#endif    /* defined(ENABLE_DEBUGLOG) && !defined(BUILD_PLUGIN) */


#undef    DEBUGLOG_C
