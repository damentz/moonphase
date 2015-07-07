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
*** \file sysdefs.h
*** \brief System specific definitions.
*** \details Definitions that may be system specific.
**/


#ifndef   SYSDEFS_H
#define   SYSDEFS_H


/****
*****
***** INCLUDES
*****
****/


/****
*****
***** DEFINES
*****
****/

#ifndef   DIRECTORY_SEPARATOR_CHAR
/**
*** \brief Directory separator character.
*** \details Character used to separate directories.
**/
#define   DIRECTORY_SEPARATOR_CHAR      '/'
#endif    /* DIRECTORY_SEPARATOR_CHAR */

#ifndef   DIRECTORY_SEPARATOR_STRING
/**
*** \brief Directory separator string.
*** \details String used to separate directories.
**/
#define   DIRECTORY_SEPARATOR_STRING    "/"
#endif    /* DIRECTORY_SEPARATOR_STRING */

#ifndef   UNUSED
/**
*** \brief Suppress unused variable warnings.
*** \details Suppresses compiler "unused variable" warnings.
**/
#define   UNUSED(v) (void)v
#endif    /* UNUSED */

/**
*** \brief Boolean false.
*** \details Value for boolean false.
**/
#define   BOOLEAN_FALSE   (0)
/**
*** \brief Boolean true.
*** \details Value for boolean true.
**/
#define   BOOLEAN_TRUE    (!BOOLEAN_FALSE)


/****
*****
***** DATA TYPES
*****
****/

/**
*** \brief Boolean type.
*** \details Boolean type for C source to be used throughout the toolbox code.
**/
typedef unsigned int BOOLEAN_T;


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

#ifdef    __cplusplus
}
#endif    /* __cplusplus */


#endif    /* SYSDEFS_H */
