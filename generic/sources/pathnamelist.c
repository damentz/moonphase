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
*** \file pathnamelist.c
*** \brief pathnamelist.h implementation.
*** \details Implementation file for pathnamelist.h.
**/


/** Identifier for pathnamelist.c. **/
#define   PATHNAMELIST_C


/****
*****
***** INCLUDES
*****
****/

#include  "pathnamelist.h"
#ifdef    DEBUG_PATHNAMELIST_C
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_PATHNAMELIST_C */
#include  "debuglog.h"
#include  "messagelog.h"
#include  "structure.h"
#include  "utility.h"


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

/**
*** \brief Compare pathnames.
*** \details Compares two pathnames, and returns a value indicating which
***   pathname should be before the other in the list.
*** \param pP1 Pointer to pathname #1.
*** \param pP2 Pointer to pathname #2.
*** \retval >0 Pathname #1 should be placed before pathname #2.
*** \retval =0 Pathname #1 and pathname #2 are the same.
*** \retval <0 Pathname #2 should be placed before pathname #1.
**/
static int SortAlphabetically(char const *pP1,char const *pP2);
/**
*** \brief Absolutizes/simplifies a pathname.
*** \details This function does two things. Firstly, if the first parameter is a
***   relative pathname, this function will convert the pathnames to an absolute
***   pathname using the second parameter as a base directory. Secondly, it
***   will expands symbolic links and resolves references to "/.", "/..",
***   and extra "/".
*** \param ppPathname Absolute (leading "/") or relative (no leading "/")
***   pathname.
*** \param pBaseDirectory If the first parameter is relative, this parameter is
***   used as the base directory. If the first parameter is absolute, this
***   parameter is ignored.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
static ERRORCODE_T Pathname_AbsolutizeAndSimplifyPathname(
    char **ppPathname,char *pBaseDirectory);
/**
*** \brief Frees a pathname.
*** \details Deallocates the memory used by the pathname in the singly linked
***   list.
*** \param ppPathname Pointer to the pathname pointer.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
static ERRORCODE_T Pathname_Free(char **ppPathname);

static SLLIST_PROTOTYPE_ALLOCATELINK(PathnameList,PATHNAMELIST);
static SLLIST_PROTOTYPE_DELETE(PathnameListPrivate,PATHNAMELIST,char *);
/**
*** \brief Deallocate a link.
*** \details Clears the memory used by singly list link entry and then
***   deallocates it.
*** \param ppLink Pointer to storage for the link pointer.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
static ERRORCODE_T PathnameListPrivate_DeallocateLink(
    PATHNAMELISTLINK_T **ppLink);


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

static int SortAlphabetically(char const *pP1,char const *pP2)
{
  int Return;


  DEBUGLOG_Printf4("SortAlphabetically(%p(%s),%p(%s)).",pP1,pP1,pP2,pP2);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pP1==NULL) || (pP2==NULL) )
    Return=0;
  else
    Return=strcmp(pP1,pP2);

  DEBUGLOG_LogOut();
  return(Return);
}

static ERRORCODE_T Pathname_AbsolutizeAndSimplifyPathname(
    char **ppPathname,char *pBaseDirectory)
{
  ERRORCODE_T ErrorCode;
  char *pNewPathname;


  DEBUGLOG_Printf3("Pathname_AbsolutizeAndSimplifyPathname(%p,%p(%s)).",
      ppPathname,pBaseDirectory,pBaseDirectory);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (ppPathname==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    ErrorCode=AbsolutizeAndSimplifyPathname(
        *ppPathname,pBaseDirectory,&pNewPathname);
    if (ErrorCode>0)
    {
      free(*ppPathname);
      *ppPathname=pNewPathname;
    }
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

static ERRORCODE_T Pathname_Free(char **ppPathname)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf1("Pathname_Free(%p).",ppPathname);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (ppPathname==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    free(*ppPathname);
    *ppPathname=NULL;
    ErrorCode=ERRORCODE_SUCCESS;
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

static SLLIST_FUNCTION_ALLOCATELINK(PathnameList,PATHNAMELIST);

SLLIST_FUNCTION_APPENDLINK(PathnameList,PATHNAMELIST,char *);

SLLIST_FUNCTION_BEGIN(PathnameList,PATHNAMELIST);

SLLIST_FUNCTION_CREATE(PathnameList,PATHNAMELIST);

static SLLIST_FUNCTION_DEALLOCATELINK(PathnameList,PATHNAMELIST);

SLLIST_FUNCTION_DELETE(PathnameListPrivate,PATHNAMELIST,char *);

static SLLIST_FUNCTION_DELETELINK(PathnameList,PATHNAMELIST,char *);

SLLIST_FUNCTION_DESTROY(PathnameList,PATHNAMELIST);

SLLIST_FUNCTION_END(PathnameList,PATHNAMELIST);

SLLIST_FUNCTION_GETLINKCOUNT(PathnameList,PATHNAMELIST);

SLLIST_FUNCTION_INITIALIZE(PathnameList,PATHNAMELIST);

SLLIST_FUNCTION_NEXT(PathnameList,PATHNAMELIST);

SLLIST_FUNCTION_SORTLINKS(PathnameList,PATHNAMELIST,char *);

SLLIST_FUNCTION_UNINITIALIZE(PathnameList,PATHNAMELIST);

SLLISTCONST_FUNCTION_BEGIN(PathnameList,PATHNAMELIST);

SLLISTCONST_FUNCTION_END(PathnameList,PATHNAMELIST);

SLLISTCONST_FUNCTION_NEXT(PathnameList,PATHNAMELIST);

ERRORCODE_T PathnameList_AbsolutizeAndSimplifyPathname(
    PATHNAMELIST_T *pPathnameList,char *pBaseDirectory)
{
  ERRORCODE_T ErrorCode;
  PATHNAMELISTITERATOR_T *pIt;


  DEBUGLOG_Printf3("PathnameList_AbsolutizeAndSimplifyPathname(%p,%p(%s))",
      pPathnameList,pBaseDirectory,pBaseDirectory);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pPathnameList==NULL) || (pBaseDirectory==NULL) )
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    ErrorCode=ERRORCODE_SUCCESS;
    PATHNAMELIST_For(pIt,*pPathnameList)
    {
      ErrorCode=
          Pathname_AbsolutizeAndSimplifyPathname(&pIt->Data,pBaseDirectory);
      if (ErrorCode<0)
        break;
    }
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T PathnameList_Delete(PATHNAMELIST_T *pList)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf1("PathnameList_Delete(%p).",pList);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pList==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
    ErrorCode=PathnameListPrivate_Delete(pList,Pathname_Free);

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T PathnameList_RemoveDuplicates(PATHNAMELIST_T *pList)
{
  ERRORCODE_T ErrorCode;
  ERRORCODE_T TempErrorCode;
  PATHNAMELISTITERATOR_T *pIt1;
  PATHNAMELISTITERATOR_T *pIt2;


  DEBUGLOG_Printf1("PathnameList_RemoveDuplicates(%p).",pList);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pList==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    ErrorCode=PathnameList_SortLinks(pList,SortAlphabetically);
    if (ErrorCode>0)
    {
      pIt1=PathnameList_Begin(pList);
      pIt2=NULL;  /* Silence lint. */
      while(pIt1!=NULL)
      {
        goto PLRD_InnerLoop;

        while( (pIt2!=NULL) && (ErrorCode>0) )
        {
          /* No match, break out of loop. */
          if (strcmp(pIt1->Data,pIt2->Data)!=0)
            break;

          /* Free the pathname string. */
          ErrorCode=Pathname_Free(&pIt2->Data);

          /* Free the sll entry. */
          TempErrorCode=PathnameList_DeleteLink(pList,pIt2);
          ERRORCODE_ConditionalCopyError(ErrorCode,TempErrorCode);
          if (ErrorCode<0)
            break;

PLRD_InnerLoop:
          pIt2=PathnameList_Next(pIt1);
        }

        pIt1=pIt2;
      }
    }
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

static ERRORCODE_T PathnameListPrivate_DeallocateLink(
    PATHNAMELISTLINK_T **ppLink)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf1("PathnameListPrivate_DeallocateLink(%p).",ppLink);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (ppLink==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
    ErrorCode=PathnameList_DeallocateLink(ppLink);

  DEBUGLOG_LogOut();
  return(ErrorCode);
}


#undef    PATHNAMELIST_C
