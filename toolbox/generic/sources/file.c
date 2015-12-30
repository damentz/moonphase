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
*** \file file.c
*** \brief file.h implementation.
*** \details Implementation file for file.h.
**/


/** Identifier for file.c. **/
#define   FILE_C


/****
*****
***** INCLUDES
*****
****/

#include  "file.h"
#ifdef    DEBUG_FILE_C
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_FILE_C */
#include  "debuglog.h"
#include  "utility.h"
#include  "messagelog.h"
#include  "visualstudio.h"

#include  <stdlib.h>
#include  <sys/stat.h>
#include  <stdio.h>
#include  <stdarg.h>
#include  <string.h>


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

static STRUCTURE_PROTOTYPE_INITIALIZEMEMBERS(File,FILE_T);
static STRUCTURE_PROTOTYPE_UNINITIALIZEMEMBERS(File,FILE_T);
/**
*** \brief Write file text.
*** \details Writes text to a file.
*** \param pFile Pointer to the file structure.
*** \param pMode fopen() style mode string.
*** \param pText Pointer to text to write to the file.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
static ERRORCODE_T File_WriteText(
    FILE_T *pFile,char const *pMode,char const *pText);

static STRUCTURE_PROTOTYPE_INITIALIZEMEMBERS(TextFile,TEXTFILE_T);
static STRUCTURE_PROTOTYPE_UNINITIALIZEMEMBERS(TextFile,TEXTFILE_T);


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

static ERRORCODE_T File_WriteText(
    FILE_T *pFile,char const *pMode,char const *pText)
{
  ERRORCODE_T ErrorCode;
  FILE *pSysFile;


  DEBUGLOG_Printf5(
      "File_WriteText(%p,%p(%s),%p(%s))",pFile,pMode,pMode,pText,pText);
  DEBUGLOG_LogIn();

  ErrorCode=ERRORCODE_SUCCESS;

  /* Parameter checking. */
  if ( (pFile==NULL) || (pMode==NULL) || (pText==NULL) )
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    /* Make sure there is something for the pathname. */
    if (pFile->pPathname==NULL)
      ErrorCode=ERRORCODE_INVALIDDATA;
    else
    {
      /* Open the file. */
      pSysFile=fopen(pFile->pPathname,pMode);
      if (pSysFile==NULL)
        ErrorCode=ERRORCODE_SYSTEMFAILURE;
      else
      {
        /* Write the file. */
        if (fputs(pText,pSysFile)==EOF)
          ErrorCode=ERRORCODE_SYSTEMFAILURE;

        /* Close the file. */
        if (fclose(pSysFile)!=0)
          if (ErrorCode>=0)
            ErrorCode=ERRORCODE_SYSTEMFAILURE;
      }
    }
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

STRUCTURE_FUNCTION_INITIALIZE(File,FILE_T);

STRUCTURE_FUNCTION_UNINITIALIZE(File,FILE_T);

static STRUCTURE_PROTOTYPE_INITIALIZEMEMBERS(File,FILE_T)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf1("File_InitializeMembers(%p)",pStructure);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pStructure==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
    ErrorCode=ERRORCODE_SUCCESS;

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

static STRUCTURE_PROTOTYPE_UNINITIALIZEMEMBERS(File,FILE_T)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf1("File_UninitializeMembers(%p)",pStructure);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pStructure==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    if (pStructure->pPathname!=NULL)
    {
      free(pStructure->pPathname);
      pStructure->pPathname=NULL;
    }
    ErrorCode=ERRORCODE_SUCCESS;
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T File_AbsolutizeAndSimplifyPathname(
    FILE_T *pFile,char const *pBaseDirectory)
{
  ERRORCODE_T ErrorCode;
  char *pAbsolutePathname;


  DEBUGLOG_Printf3("File_AbsolutizeAndSimplifyPathname(%p,%p(%s))",
      pFile,pBaseDirectory,pBaseDirectory);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pFile->pPathname==NULL) || (pBaseDirectory==NULL) )
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    ErrorCode=AbsolutizeAndSimplifyPathname(
        pFile->pPathname,pBaseDirectory,&pAbsolutePathname);
    if (ErrorCode==ERRORCODE_FALSE)
    {
      /* Free any absolute pathname, don't mess with original. */
      if (pAbsolutePathname!=NULL)
        free(pAbsolutePathname);
    }
    else if (ErrorCode>ERRORCODE_FALSE)
    {
      /* Free original, use new. */
      free(pFile->pPathname);
      pFile->pPathname=pAbsolutePathname;
    }
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T File_AppendText(FILE_T *pFile,char *pText)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf3("File_AppendText(%p,%p(%s))",pFile,pText,pText);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pFile==NULL) || (pText==NULL) )
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
    ErrorCode=File_WriteText(pFile,"ab",pText);

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T File_Copy(FILE_T const *pFile,FILE_T *pCopy)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf2("File_Copy(%p,%p)",pFile,pCopy);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pFile==NULL) || (pCopy==NULL) )
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    ErrorCode=File_Initialize(pCopy);
    if (ErrorCode>0)
    {
      pCopy->pPathname=strdup(pFile->pPathname);
      if (pCopy->pPathname==NULL)
        ErrorCode=ERRORCODE_SYSTEMFAILURE;
    }
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T File_GetPathnamePointer(
    FILE_T const *pFile,char const **ppPathname)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf2("File_GetPathnamePointer(%p,%p)",pFile,ppPathname);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pFile==NULL) || (ppPathname==NULL) )
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    /* Return the pathname. */
    *ppPathname=pFile->pPathname;
    if ((*ppPathname)==NULL)
      ErrorCode=ERRORCODE_FALSE;
    else
      ErrorCode=ERRORCODE_TRUE;
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T File_ReadText(FILE_T *pFile,char **ppText)
{
  ERRORCODE_T ErrorCode;
  struct stat Stats;
  size_t FileSize;
  FILE *pSysFile;


  DEBUGLOG_Printf2("File_ReadText(%p,%p)",pFile,ppText);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pFile==NULL) || (ppText==NULL) )
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    /* Make sure there is something for the pathname. */
    if (pFile->pPathname==NULL)
      ErrorCode=ERRORCODE_INVALIDDATA;
    else
    {
      /* Get the file stats. */
      if (stat(pFile->pPathname,&Stats)==-1)
        ErrorCode=ERRORCODE_SYSTEMFAILURE;
      else
      {
        FileSize=(size_t)Stats.st_size;

        /* Allocate a buffer for the file text. */
        *ppText=(char*)malloc((FileSize+1)*sizeof(**ppText));
        if (*ppText==NULL)
          ErrorCode=ERRORCODE_SYSTEMFAILURE;
        else
        {
          memset((char*)*ppText,0,(FileSize+1)*sizeof(**ppText));

          /* Open the file. */
          pSysFile=fopen(pFile->pPathname,"rb");
          if (pSysFile==NULL)
            ErrorCode=ERRORCODE_SYSTEMFAILURE;
          else
          {
            /* Read the file. */
            if (fread((char*)*ppText,sizeof(**ppText),FileSize,pSysFile)!=
                FileSize)
              ErrorCode=ERRORCODE_SYSTEMFAILURE;
            else
              ErrorCode=ERRORCODE_SUCCESS;

            /* Close the file. */
            if (fclose(pSysFile)!=0)
              if (ErrorCode>=0)
                ErrorCode=ERRORCODE_SYSTEMFAILURE;
          }

          /* Free any allocated memory on error. */
          if (ErrorCode<0)
          {
            if (*ppText!=NULL)
            {
              free((void*)*ppText);
              *ppText=NULL;
            }
          }
        }
      }
    }
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T File_ReplaceText(FILE_T *pFile,char *pText)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf3("File_ReplaceText(%p,%p(%s))",pFile,pText,pText);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pFile==NULL) || (pText==NULL) )
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
    ErrorCode=File_WriteText(pFile,"wb",pText);

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T File_SetPathname(FILE_T *pFile,char const *pPathname)
{
  ERRORCODE_T ErrorCode;
  char *pStrDup;


  DEBUGLOG_Printf3("File_SetPathname(%p,%p(%s))",pFile,pPathname,pPathname);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pFile==NULL) || (pPathname==NULL) )
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    /* Copy the pathname. */
    pStrDup=strdup(pPathname);
    if (pStrDup==NULL)
      ErrorCode=ERRORCODE_SYSTEMFAILURE;
    else
    {
      /* Free any old pathname. */
      if (pFile->pPathname!=NULL)
        free((char*)pFile->pPathname);

      /* Set the pathname. */
      pFile->pPathname=pStrDup;

      ErrorCode=ERRORCODE_SUCCESS;
    }
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

STRUCTURE_FUNCTION_INITIALIZE(TextFile,TEXTFILE_T);

STRUCTURE_FUNCTION_UNINITIALIZE(TextFile,TEXTFILE_T);

static STRUCTURE_PROTOTYPE_INITIALIZEMEMBERS(TextFile,TEXTFILE_T)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf1("TextFile_InitializeMembers(%p)",pStructure);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pStructure==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    ErrorCode=File_Initialize(&pStructure->File);
    pStructure->pText=NULL;
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

static STRUCTURE_PROTOTYPE_UNINITIALIZEMEMBERS(TextFile,TEXTFILE_T)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf1("TextFile_UninitializeMembers(%p)",pStructure);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pStructure==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    if (pStructure->pText!=NULL)
    {
      free(pStructure->pText);
      pStructure->pText=NULL;
    }
    ErrorCode=File_Uninitialize(&pStructure->File);
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T TextFile_GetTextPointer(
    TEXTFILE_T const *pTextFile,char const **ppText)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf2("TextFile_GetTextPointer(%p,%p)",pTextFile,ppText);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pTextFile==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    *ppText=pTextFile->pText;
    if ((*ppText)==NULL)
      ErrorCode=ERRORCODE_FALSE;
    else
      ErrorCode=ERRORCODE_TRUE;
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T TextFile_Printf(TEXTFILE_T *pTextFile,char *pFormat,...)
{
  ERRORCODE_T ErrorCode;
  va_list ArgList;
  char *pVasprintf;
  char *pMerged;
  int Result;


  DEBUGLOG_Printf3("TextFile_Printf(%p,%p(%s))",pTextFile,pFormat,pFormat);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pTextFile==NULL) || (pFormat==NULL) )
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    va_start(ArgList,pFormat);
    Result=vasprintf(&pVasprintf,pFormat,ArgList);
    va_end(ArgList);
    if (Result<0)
      ErrorCode=ERRORCODE_SYSTEMFAILURE;
    else
    {
      if (pTextFile->pText==NULL)
        Result=asprintf(&pMerged,"%s",pVasprintf);
      else
        Result=asprintf(&pMerged,"%s%s",pTextFile->pText,pVasprintf);
      if (Result<0)
        ErrorCode=ERRORCODE_SYSTEMFAILURE;
      else
        ErrorCode=ERRORCODE_SUCCESS;

      if (pVasprintf!=NULL)
        free(pVasprintf);
      if (pTextFile->pText!=NULL)
        free(pTextFile->pText);
      /* if Result < 0 (asprintf failed),
          pMerged is undefined, so don't do anything in that case. */
      if (Result>=0)
        pTextFile->pText=pMerged;
    }
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T TextFile_Read(TEXTFILE_T *pTextFile)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf1("TextFile_Read(%p,%p)",pTextFile);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pTextFile==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
  {
    /* Free any old data. */
    if (pTextFile->pText!=NULL)
    {
      free(pTextFile->pText);
      pTextFile->pText=NULL;
    }

    /* Read the file. */
    ErrorCode=File_ReadText(&pTextFile->File,&pTextFile->pText);
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T TextFile_SetPathname(TEXTFILE_T *pTextFile,char const *pPathname)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf3("TextFile_SetPathname(%p,%p(%s))",
      pTextFile,pPathname,pPathname);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pTextFile==NULL) || (pPathname==NULL) )
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
    ErrorCode=File_SetPathname(&pTextFile->File,pPathname);

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T TextFile_Write(TEXTFILE_T *pTextFile)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf1("TextFile_Write(%p,%p)",pTextFile);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pTextFile==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else
    ErrorCode=File_ReplaceText(&pTextFile->File,pTextFile->pText);

  DEBUGLOG_LogOut();
  return(ErrorCode);
}


#undef    FILE_C
