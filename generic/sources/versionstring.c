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
*** \file versionstring.c
*** \brief versionstring.h implementation file.
*** \details Implementation file for versionstring.h.
**/


/** Identifier for versionstring.cpp. **/
#define   VERSIONSTRING_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "versionstring.h"
#ifdef    DEBUG_VERSIONSTRING_CPP
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_VERSIONSTRING_CPP */
#include  "debuglog.h"

#include  <string.h>
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

int VersionString_Compare(
    VERSIONSTRING_T const *pLHS,VERSIONSTRING_T const *pRHS)
{
  int Index;
  int Return;


  DEBUGLOG_Printf4("VersionString_Compare(%p(%s),%p(%s))",pLHS,pLHS,pRHS,pRHS);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pLHS==NULL)
  {
    if (pRHS==NULL)
      Return=0;
    else
      Return=-1;
  }
  else if (pRHS==NULL)
    Return=1;
  else
  {
    for(Index=0;Index<DIGITS_MAXIMUMCOUNT;Index++)
    {
      Return=pLHS->Digits[Index]-pRHS->Digits[Index];
      if (Return!=0)
        break;
    }
  }

  DEBUGLOG_LogOut();
  return(Return);
}

ERRORCODE_T VersionString_Set(
    VERSIONSTRING_T *pVersionString,char const *pString)
{
  ERRORCODE_T ErrorCode;
  int Index;
  char const *pPtr;
  char *pEndPtr;


  DEBUGLOG_Printf3(
      "VersionString_Set(%p,%p(%s))",pVersionString,pString,pString);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pString==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    /* Initialize storage. */
    memset(pVersionString,0,sizeof(*pVersionString));

    /* Compare each digit. */
    ErrorCode=ERRORCODE_INVALIDDATA;
    pPtr=pString;
    for(Index=0;Index<DIGITS_MAXIMUMCOUNT;Index++)
    {
      pVersionString->Digits[Index]=(short)strtol(pPtr,&pEndPtr,10);
      if (*pEndPtr=='\0')
      {
        ErrorCode=ERRORCODE_SUCCESS;
        break;
      }
      pPtr=pEndPtr+1;
    }
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}


#undef    VERSIONSTRING_CPP
