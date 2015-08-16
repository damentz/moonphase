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
*** \file checksum.c
*** \brief checksum.h implementation.
*** \details Implementation file for checksum.h.
**/


/** Identifier for checksum.c. **/
#define   CHECKSUM_C


/****
*****
***** INCLUDES
*****
****/

#ifdef    USE_MHASH

#include  "checksum.h"
#ifdef    DEBUG_CHECKSUM_C
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_CHECKSUM_C */
#include  "debuglog.h"
#include  "sysdefs.h"

#include  <sys/stat.h>

#ifdef    USE_MHASH
#include  <mhash.h>
#endif    /* USE_MHASH */


/****
*****
***** DEFINES
*****
****/

/**
*** \brief Checksum buffer size.
*** \details Size of the file data buffer used to calculate checksum.
**/
#define   CHECKSUM_READBUFFER_SIZE    (1024)

/**
*** \hideinitializer
*** \brief Check checksum type validity.
*** \details Checks the validity of the checksum type.
*** \param ct Checksum type.
*** \retval 0 Index is valid.
*** \retval !0 Index is not valid.
**/
#define   CHECKSUMTYPE_ISVALID(ct) \
              ( ((ct)==CHECKSUMTYPE_CRC32) || ((ct)==CHECKSUMTYPE_MD5) )


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

ERRORCODE_T Checksum_Calculate(
    const char *pPathname,CHECKSUMTYPE_E Type,char **ppChecksum)
{
  ERRORCODE_T ErrorCode;
  ERRORCODE_T TempErrorCode;
  unsigned int MHASHType;
  struct stat FileStats;
  MHASH HashData;
  FILE *pFile;
  unsigned int Count;
  unsigned int ReadSize;
  char pReadBuffer[CHECKSUM_READBUFFER_SIZE];
  BOOLEAN_T ChecksumDoneFlag;
  unsigned char *pHash;


  DEBUGLOG_Printf4("Checksum_Calculate(%p(%s),%u,%p)",
      pPathname,pPathname,Type,ppChecksum);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pPathname==NULL) || (ppChecksum==NULL) )
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else if (CHECKSUMTYPE_ISVALID(Type)==0)
    ErrorCode=ERRORCODE_INVALIDPARAMETER;
  else
  {
    *ppChecksum=NULL;
#ifdef    USE_MHASH
    /* Convert from CHECKSUM_ value to MHASH value. */
    ErrorCode=ERRORCODE_SUCCESS;
    switch(Type)
    {
      case CHECKSUMTYPE_CRC32:
        MHASHType=MHASH_CRC32;
        break;
      case CHECKSUMTYPE_MD5:
        MHASHType=MHASH_MD5;
        break;
      default:
        ErrorCode=ERRORCODE_INVALIDPARAMETER;
        break;
    }

    if (ErrorCode>0)
    {
      /* Initialize the hash. */
      HashData=mhash_init(MHASHType);
      if (HashData==MHASH_FAILED)
        ErrorCode=ERRORCODE_LIBRARYFAILURE;
      else
      {
        /* Get the file size. */
        if (stat(pPathname,&FileStats)==-1)
          ErrorCode=ERRORCODE_SYSTEMFAILURE;
        else
        {
          pHash=NULL;

          /* Open the file. */
          pFile=fopen(pPathname,"rb");
          if (pFile==NULL)
            ErrorCode=ERRORCODE_SYSTEMFAILURE;
          else
          {
            /* Read the file in chunks, computing the hash on each chunk. */
            ErrorCode=ERRORCODE_SUCCESS;
            Count=FileStats.st_size;
            ChecksumDoneFlag=BOOLEAN_FALSE;
            while( (ferror(pFile)==0) && (Count!=0) )
            {
              if (Count>=CHECKSUM_READBUFFER_SIZE)
                ReadSize=CHECKSUM_READBUFFER_SIZE;
              else
                ReadSize=Count;
              Count-=ReadSize;

              if (fread(pReadBuffer,ReadSize,1,pFile)!=1)
              {
                ErrorCode=ERRORCODE_SYSTEMFAILURE;
                break;
              }

              if (mhash(HashData,pReadBuffer,ReadSize)!=MUTILS_FALSE)
              {
                ErrorCode=ERRORCODE_LIBRARYFAILURE;
                break;
              }
            }

            /* If we've reached the end of the file with no errors, the checksum
                should be valid, regardless of any subsequent errors. */
            if ( (ferror(pFile)==0) && (ErrorCode>0) )
              ChecksumDoneFlag=BOOLEAN_TRUE;

            TempErrorCode=ERRORCODE_SUCCESS;
            if (fclose(pFile)!=0)
              TempErrorCode=ERRORCODE_SYSTEMFAILURE;
            ERRORCODE_ConditionalCopyError(TempErrorCode,ErrorCode);

            if (ChecksumDoneFlag!=BOOLEAN_FALSE)
            {
              /* Get the hash value. */
              pHash=mhash_end(HashData);
              if (pHash==NULL)
                ErrorCode=ERRORCODE_LIBRARYFAILURE;
              else
              {
                /* Convert the hash value to a string to be returned. */
                *ppChecksum=malloc(2*mhash_get_block_size(MHASHType)+1);
                if (*ppChecksum==NULL)
                  ErrorCode=ERRORCODE_SYSTEMFAILURE;
                else
                  for(Count=0;Count<mhash_get_block_size(MHASHType);Count++)
                    sprintf((char*)&((*ppChecksum)[2*Count]),"%.2x",pHash[Count]);
                free(pHash);
              }
            }
          }
        }
      }
    }
#endif    /* USE_MHASH */
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}


#endif    /* USE_MHASH */

#undef    CHECKSUM_C
