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
*** \file utility.c
*** \brief utility.h implementation.
*** \details Implementation file for utility.h.
**/


/** Identifier for utility.c. **/
#define   UTILITY_C


/****
*****
***** INCLUDES
*****
****/

#include  "utility.h"
#ifdef    DEBUG_UTILITY_C
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_UTILITY_C */
#include  "debuglog.h"
#include  "sysdefs.h"
#include  "visualstudio.h"

#include  <stdlib.h>
#include  <stdio.h>


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

ERRORCODE_T AbsolutizeAndSimplifyPathname(
    const char *pPathname,const char *pBaseDirectory,char **ppResolved)
{
  ERRORCODE_T ErrorCode;
  char *pLongPathname;


  DEBUGLOG_Printf5("AbsolutizeAndSimplifyPathname(%p(%s),%p(%s),%p)",
      pPathname,pPathname,pBaseDirectory,pBaseDirectory,ppResolved);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pPathname==NULL) || (ppResolved==NULL) )
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    /* Check if the relative pathname is actually absolute. */
    if (*pPathname==DIRECTORY_SEPARATOR_CHAR)
    {
      /* Relative pathname is actually an absolute pathname. Only
          canonicalize the "relative" pathname. */
      *ppResolved=canonicalize_file_name(pPathname);
      if (*ppResolved==NULL)
        ErrorCode=ERRORCODE_SYSTEMFAILURE;
      else
        ErrorCode=ERRORCODE_SUCCESS;
    }
    else
    {
      /* Got a relative pathname. Make sure base is absolute. */
      if (pBaseDirectory==NULL)
          ErrorCode=ERRORCODE_NULLPARAMETER;
      else
      {
        /* Make sure the base pathname is absolute. */
        if (*pBaseDirectory!=DIRECTORY_SEPARATOR_CHAR)
          ErrorCode=ERRORCODE_INVALIDDATA;
        else
        {
          /* Combine directory and relative path. */
          if (asprintf(&pLongPathname,"%s/%s",pBaseDirectory,pPathname)==-1)
          {
            *ppResolved=NULL;
            ErrorCode=ERRORCODE_SYSTEMFAILURE;
          }
          else
          {
            *ppResolved=canonicalize_file_name(pLongPathname);
            free((char*)pLongPathname);
            ErrorCode=ERRORCODE_SUCCESS;
          }
        }
      }
    }
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}


#undef    UTILITY_C
