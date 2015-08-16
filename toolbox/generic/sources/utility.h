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
*** \file utility.h
*** \brief Utility/miscellaneous functions.
*** \details Utility/miscellaneous system functions.
**/


#ifndef   UTILITY_H
#define   UTILITY_H


/****
*****
***** INCLUDES
*****
****/

#include  "errorcode.h"


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

#ifdef    __cplusplus
extern "C" {
#endif    /* __cplusplus */

/**
*** \brief Absolutizes/simplifies a pathname.
*** \details This function does two things. Firstly, if the first parameter is
***   a relative pathname, this function will convert it to an absolute
***   pathname using the second parameter as a base directory. Secondly, it
***   will expands symbolic links and resolves references to "/.", "/..",
***   and extra "/".
*** \param pPathname Absolute (leading "/") or relative (no leading "/")
***   pathname.
*** \param pBaseDirectory If the first parameter is relative, this parameter
***   is used as the base directory. If the first parameter is absolute,
***   this parameter is ignored.
*** \param ppResolved Pointer to storage for the absolutized/simplified
***   pathname.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
ERRORCODE_T AbsolutizeAndSimplifyPathname(
    char const *pPathname,char const *pBaseDirectory,char **ppResolved);

#ifdef  __cplusplus
}
#endif  /* __cplusplus */


#endif    /* UTILITY_H */
