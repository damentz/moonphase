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
*** \file file.h
*** \brief Read/write files.
*** \details Read from and write to files.
**/


#ifndef   FILE_H
#define   FILE_H


/****
*****
***** INCLUDES
*****
****/

#include  "structure.h"


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
*** \brief File data.
*** \details Basic file data.
**/
typedef struct structFILE
{
  /**
  *** \brief File pathname pointer.
  *** \details Pointer to the pathname of file.
  **/
  char *pPathname;
  /**
  *** \brief Error code storage.
  *** \details Storage for any error code.
  **/
  int Errno;
} FILE_T;

/**
*** \brief Text file data.
*** \details File containing only text.
**/
typedef struct structTEXTFILE
{
  /**
  *** \brief File data.
  *** \details Data for the file.
  **/
  FILE_T File;
  /**
  *** \brief File text.
  *** \details Text read from/to be written to the file.
  **/
  char *pText;
} TEXTFILE_T;


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

STRUCTURE_PROTOTYPE_INITIALIZE(File,FILE_T);
STRUCTURE_PROTOTYPE_UNINITIALIZE(File,FILE_T);
/**
*** \brief Absolutizes and simplifies the pathname.
*** \details This function does two things. Firstly, if the file name is a
***   relative pathname, this function will convert it to an absolute pathname
***   using the second parameter as a base directory. Secondly, it will
***   expands symbolic links and resolves references to "/.", "/..", and
***   extra "/".
*** \param pFile Pointer to the file structure.
*** \param pBaseDirectory The absolute (leading "/") base directory if the
***   file pathname is relative (no leading "/").
*** \retval >0 Success.
*** \retval <0 Failure.
**/
ERRORCODE_T File_AbsolutizeAndSimplifyPathname(
    FILE_T *pFile,char const *pBaseDirectory);
/**
*** \brief Append text.
*** \details Appends text to a file in the file system.
*** \param pFile Pointer to the file structure.
*** \param pText Pointer to text to append.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
ERRORCODE_T File_AppendText(FILE_T *pFile,char *pText);
/**
*** \brief Copy file structure.
*** \details Copies the file structure.
*** \param pFile Pointer to the file structure.
*** \param pCopy Pointer to storage for the copied file structure.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
ERRORCODE_T File_Copy(FILE_T const *pFile,FILE_T *pCopy);
/**
*** \brief Returns file pathname pointer.
*** \details Returns a pointer to the file pathname.
*** \param pFile Pointer to the file structure.
*** \param ppPathname Pointer to storage for the pointer to the pathname.
*** \retval >0 Success.
*** \retval <0 Failure.
*** \returns *ppPathname Pointer to storage for the pathname.
**/
ERRORCODE_T File_GetPathnamePointer(
    FILE_T const *pFile,char const **ppPathname);
/**
*** \brief Read text.
*** \details Reads text from the file.
*** \param pFile Pointer to the file structure.
*** \param ppText Pointer to storage for the text pointer.
*** \retval >0 Success.
*** \retval <0 Failure.
*** \returns *ppText Pointer to storage for the file contents pointer.
**/
ERRORCODE_T File_ReadText(FILE_T *pFile,char **ppText);
/**
*** \brief Overwrite text.
*** \details Overwrites text to a file in the file system.
*** \param pFile Pointer to the file structure.
*** \param pText Pointer to text to overwrite.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
ERRORCODE_T File_ReplaceText(FILE_T *pFile,char *pText);
/**
*** \brief Set pathname.
*** \details Sets the pathname of the file.
*** \param pFile Pointer to the file structure.
*** \param pPathname Pointer to the pathname.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
ERRORCODE_T File_SetPathname(FILE_T *pFile,char const *pPathname);

STRUCTURE_PROTOTYPE_INITIALIZE(TextFile,TEXTFILE_T);
STRUCTURE_PROTOTYPE_UNINITIALIZE(TextFile,TEXTFILE_T);
/**
*** \brief Return file text.
*** \details Returns a pointer to the text contained in the file.
*** \param pTextFile Pointer to the text file structure.
*** \param ppText Pointer to storage for the text pointer.
*** \retval >0 Success.
*** \retval <0 Failure.
*** \returns *ppText Pointer to storage for the file contents pointer.
**/
ERRORCODE_T TextFile_GetTextPointer(
    TEXTFILE_T const *pTextFile,char const **ppText);
/**
*** \brief Read text.
*** Reads the text in the file into memory.
*** \param pTextFile Pointer to the text file structure.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
ERRORCODE_T TextFile_Read(TEXTFILE_T *pTextFile);
/**
*** \brief Set the text file pathname.
*** \details Sets the pathname of the file.
*** \param pTextFile Pointer to the text file structure.
*** \param pPathname Pointer to the pathname.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
ERRORCODE_T TextFile_SetPathname(TEXTFILE_T *pTextFile,char const *pPathname);
/**
*** \brief Append text.
*** \details Appends text to the file.
*** \param pTextFile Pointer to the text file structure.
*** \param pFormat printf() format style string.
*** \param ... Additional parameters.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
ERRORCODE_T TextFile_Printf(TEXTFILE_T *pTextFile,char *pFormat,...);
/**
*** \brief Write text.
*** \details Writes the text in memory to the file.
*** \param pTextFile Pointer to the text file structure.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
ERRORCODE_T TextFile_Write(TEXTFILE_T *pTextFile);

#ifdef  __cplusplus
}
#endif  /* __cplusplus */


#endif    /* FILE_H */
