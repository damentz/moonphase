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
*** \file checksum.h
*** \brief Calculate file checksums.
*** \details Calculate checksums on files.
**/

#ifndef   CHECKSUM_H
#define   CHECKSUM_H


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

/**
*** \brief Checksum types.
*** \details Types of checksums.
**/
typedef enum enumCHECKSUMTYPE
{
  CHECKSUMTYPE_CRC32=0,
  CHECKSUMTYPE_MD5=1,
} CHECKSUMTYPE_E;


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

/**
*** \brief Checksum a file.
*** \details Calculates the checksum for a file.
*** \param pPathname Pointer to pathname.
*** \param Type Checksum type.
*** \param ppChecksum Pointer to storage for the checksum pointer.
*** \retval >0 Success.
*** \retval <0 Failure.
*** \returns *ppChecksum Pointer the specified file checksum.
**/
ERRORCODE_T Checksum_Calculate(
    const char *pPathname,CHECKSUMTYPE_E Type,char **ppChecksum);

#ifdef    __cplusplus
}
#endif    /* __cplusplus */


#endif    /* CHECKSUM_H */
