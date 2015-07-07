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
*** \file pathnamelist.h
*** \brief Manage/manipulate lists of pathnames.
*** \details Provides the ability to create, manage, and manipulate lists
***   of pathnames.
**/


#ifndef   PATHNAMELIST_H
#define   PATHNAMELIST_H


/****
*****
***** INCLUDES
*****
****/

#include  "sllist.h"


/****
*****
***** DEFINES
*****
****/

/**
*** \hideinitializer
*** \brief PATHNAMELIST_T for loop template.
*** \details Template to create a for loop for a PATHNAMELIST_T.
*** \param it Iterator pointer.
*** \param ll Linked list.
**/
#define   PATHNAMELIST_For(it,ll) \
              for((it)=PathnameList_Begin(&(ll)); \
                  (it)!=PathnameList_End(&(ll)); \
                  (it)=PathnameList_Next((it)))
/**
*** \hideinitializer
*** \brief PATHNAMELISTCONST_T for loop template.
*** \details Template to create a for loop for a const PATHNAMELIST_T.
*** \param it Iterator pointer.
*** \param ll Linked list.
**/
#define   PATHNAMELISTCONST_For(it,ll) \
              for((it)=PathnameListConst_Begin(&(ll)); \
                  (it)!=PathnameListConst_End(&(ll)); \
                  (it)=PathnameListConst_Next((it)))


/****
*****
***** DATA TYPES
*****
****/

SLLIST_TYPES(PathnameList,PATHNAMELIST,char *);


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
***** PROTOTYPES
*****
****/

#ifdef  __cplusplus
extern "C" {
#endif  /* __cplusplus */

SLLIST_PROTOTYPE_APPENDLINK(PathnameList,PATHNAMELIST,char *);
SLLIST_PROTOTYPE_BEGIN(PathnameList,PATHNAMELIST);
SLLIST_PROTOTYPE_CREATE(PathnameList,PATHNAMELIST);
SLLIST_PROTOTYPE_DESTROY(PathnameList,PATHNAMELIST);
SLLIST_PROTOTYPE_END(PathnameList,PATHNAMELIST);
SLLIST_PROTOTYPE_GETLINKCOUNT(PathnameList,PATHNAMELIST);
SLLIST_PROTOTYPE_INITIALIZE(PathnameList,PATHNAMELIST);
SLLIST_PROTOTYPE_NEXT(PathnameList,PATHNAMELIST);
SLLIST_PROTOTYPE_SORTLINKS(PathnameList,PATHNAMELIST,char *);
SLLIST_PROTOTYPE_UNINITIALIZE(PathnameList,PATHNAMELIST);
SLLISTCONST_PROTOTYPE_BEGIN(PathnameList,PATHNAMELIST);
SLLISTCONST_PROTOTYPE_END(PathnameList,PATHNAMELIST);
SLLISTCONST_PROTOTYPE_NEXT(PathnameList,PATHNAMELIST);
/**
*** \brief Absolutizes/simplifies the pathname list.
*** \details This function does two things. Firstly, if the first parameter is
***   a relative pathname, this function will convert all pathnames to absolute
***   pathnames using the second parameter as a base directory. Secondly, it
***   will expands symbolic links and resolves references to "/.", "/..",
***   and extra "/".
*** \param pList Pointer to the pathname structure.
*** \param pBaseDirectory If the first parameter is relative, this parameter is
***   used as the base directory. If the first parameter is absolute, this
***   parameter is ignored.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
ERRORCODE_T PathnameList_AbsolutizeAndSimplifyPathname(
    PATHNAMELIST_T *pList,char *pBaseDirectory);
/**
*** \brief Delete the links in a singly linked list.
*** \details Deletes all of the links in a singly linked list.
*** \param pList Pointer to the singly linked list structure.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
ERRORCODE_T PathnameList_Delete(PATHNAMELIST_T *pList);
/**
*** \brief Removes duplicates.
*** \details Removes any duplicate pathnames in the singly linked list.
*** \param pList Pointer to the singly linked list structure.
*** \retval >0 Success.
*** \retval <0 Failure.
*** \note The resulting list is sorted alphabetically ascending (A-Z).
**/
ERRORCODE_T PathnameList_RemoveDuplicates(PATHNAMELIST_T *pList);

#ifdef  __cplusplus
}
#endif  /* __cplusplus */


#endif    /* PATHNAMELIST_H */
