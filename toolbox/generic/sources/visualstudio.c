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
*** \file visualstudio.c
*** \brief visualstudio.h implementation file.
*** \details Implementation file for visualstudio.h.
**/


#ifdef    _WIN32

/** Identifier for visualstudio.cpp. **/
#define   VISUALSTUDIO_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "visualstudio.h"
#ifdef    DEBUG_VISUALSTUDIO_CPP
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_VISUALSTUDIO_CPP */
#include  "debuglog.h"

#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>


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

int asprintf(char **ppString,char const *pFormat,...)
{
  int Count;
  va_list List;

  DEBUGLOG_Printf3("asprintf(%p,%p(%s))",ppString,pFormat,pFormat);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (ppString==NULL) || (pFormat==NULL) )
    Count=-1;
  else
  {
    va_start(List,pFormat);
    Count=vasprintf(ppString,pFormat,List);
    va_end(List);
  }

  DEBUGLOG_LogOut();
  return(Count);
}

int vasprintf(char **ppString,char const *pFormat,va_list pList)
{
  int Count;
  int Length;


  DEBUGLOG_Printf4("asprintf(%p,%p(%s),%p)",ppString,pFormat,pFormat,pList);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  Count=-1;
  if ( (ppString!=NULL) && (pFormat!=NULL) && (pList!=NULL) )
  {
    Length=_vscprintf(pFormat,pList);
    if (Length!=-1)
    {
      Length++;   /* '\0' terminator. */
      *ppString=(char *)malloc(Length);
      if ((*ppString)!=NULL)
      {
        Count=vsnprintf(*ppString,Count,pFormat,pList);
        if (Count==-1)
        {
          free(*ppString);
          *ppString=NULL;
        }
      }
    }
  }
  else
    *ppString=NULL;

  DEBUGLOG_LogOut();
  return(Count);
}

#undef    VISUALSTUDIO_CPP

#endif    /* _WIN32 */
