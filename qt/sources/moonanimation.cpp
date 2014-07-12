/*
** This file is part of moonphase.
** Copyright (C) 2014 by Alan Wise (alanwise@users.sourceforge.net)
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
*** \file moonanimation.cpp
*** \brief moonanimation.h implementation.
*** \details Implementation file for moonanimation.h.
*** \todo Read other formats (i.e. formats with animations, etc.)
**/


/** Identifier for moonanimation.cpp. **/
#define   MOONANIMATION_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "controlpaneldialog.h"
#ifdef    DEBUG_MOONANIMATION_CPP
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_MOONANIMATION_CPP */
#include  "debuglog.h"
#include  "messagelog.h"


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

STRUCTURE_FUNCTION_INITIALIZE(MoonAnimation,MOONANIMATION_T);

STRUCTURE_PROTOTYPE_INITIALIZEMEMBERS(MoonAnimation,MOONANIMATION_T)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf1("MoonAnimation_InitializeMembers(%p)",pStructure);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pStructure==NULL)
  {
    ErrorCode=ERRORCODE_NULLPARAMETER;
    MESSAGELOG_LogError(ErrorCode);
  }
  else
  {
    pStructure->pFileName=new QString("");
    pStructure->pImages=new QList<QPixmap>;
    ErrorCode=ERRORCODE_SUCCESS;
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

STRUCTURE_FUNCTION_UNINITIALIZE(MoonAnimation,MOONANIMATION_T);

STRUCTURE_PROTOTYPE_UNINITIALIZEMEMBERS(MoonAnimation,MOONANIMATION_T)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf1("MoonAnimation_UninitializeMembers(%p)",pStructure);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pStructure==NULL)
  {
    ErrorCode=ERRORCODE_NULLPARAMETER;
    MESSAGELOG_LogError(ErrorCode);
  }
  else
  {
    if (pStructure->pImages==NULL)
    {
      MESSAGELOG_Warning("pStructure->pImages==NULL");
    }
    delete pStructure->pImages;
    if (pStructure->pFileName==NULL)
    {
      MESSAGELOG_Warning("pStructure->pFileName==NULL");
    }
    delete pStructure->pFileName;
    ErrorCode=ERRORCODE_SUCCESS;
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T MoonAnimation_GetFrame(
    MOONANIMATION_T const *pMoonAnimation,int Index,QPixmap const **ppFrame)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf3(
      "MoonAnimation_GetFrame(%p,%u,%p)",pMoonAnimation,Index,ppFrame);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pMoonAnimation==NULL) || (ppFrame==NULL) )
  {
    ErrorCode=ERRORCODE_NULLPARAMETER;
    MESSAGELOG_LogError(ErrorCode);
  }
  else if (pMoonAnimation->pImages==NULL)
  {
    ErrorCode=ERRORCODE_INVALIDDATA;
    MESSAGELOG_LogError(ErrorCode);
  }
  else if (Index>pMoonAnimation->pImages->count())
  {
    ErrorCode=ERRORCODE_INVALIDPARAMETER;
    MESSAGELOG_LogError(ErrorCode);
  }
  else
  {
    *ppFrame=&((*(pMoonAnimation->pImages))[Index]);
    ErrorCode=ERRORCODE_SUCCESS;
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T MoonAnimation_GetFrameCount(MOONANIMATION_T const *pMoonAnimation)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf1("MoonAnimation_GetFrameCount(%p)",pMoonAnimation);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pMoonAnimation==NULL)
  {
    ErrorCode=ERRORCODE_NULLPARAMETER;
    MESSAGELOG_LogError(ErrorCode);
  }
  else if (pMoonAnimation->pImages==NULL)
  {
    ErrorCode=ERRORCODE_INVALIDDATA;
    MESSAGELOG_LogError(ErrorCode);
  }
  else
    ErrorCode=pMoonAnimation->pImages->count();

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T MoonAnimation_ReadFile(
    MOONANIMATION_T *pMoonAnimation,char const *pPathName)
{
  ERRORCODE_T ErrorCode;
  QPixmap Image;
  int FrameCount;
  int DX;
  int DY;
  int Size;
  int Frame;


  DEBUGLOG_Printf3(
      "MoonAnimation_ReadFile(%p,%p(%s))",pMoonAnimation,pPathName,pPathName);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pMoonAnimation==NULL) || (pPathName==NULL) )
  {
    ErrorCode=ERRORCODE_NULLPARAMETER;
    MESSAGELOG_LogError(ErrorCode);
  }
  else if (QString(pPathName)==pMoonAnimation->pFileName)
  {
    MESSAGELOG_Warning("Trying to reload same file.");  // TODO
    ErrorCode=ERRORCODE_TRUE;
  }
  else
  {
    *(pMoonAnimation->pFileName)="";
    pMoonAnimation->pImages->clear();
    ErrorCode=ERRORCODE_FALSE;
    /*QPixmap*/ Image.load(pPathName);
    FrameCount=0;
    if (Image.isNull()==0)
    {
      /* How are the frames arranged? */
      if (Image.width()>=Image.height())
      {
        /* Horizontally. Make sure the width is a multiple of the height. */
        if (Image.width()%Image.height()==0)
        {
          FrameCount=Image.width()/Image.height();
          DX=Image.height();
          DY=0;
          Size=Image.height();
        }
      }
      else
      {
        /* Vertically. Make sure the height is a multiple of the width. */
        if (Image.height()%Image.width()==0)
        {
          FrameCount=Image.height()/Image.width();
          DX=0;
          DY=Image.width();
          Size=Image.width();
        }
      }

      /* Valid image? */
      if (FrameCount>0)
      {
        /* Split the image into frames. */
        for(Frame=0;Frame<FrameCount;Frame++)
          pMoonAnimation->pImages->append(
              Image.copy(Frame*DX,Frame*DY,Size,Size));
        *(pMoonAnimation->pFileName)=QString(pPathName);
        ErrorCode=ERRORCODE_TRUE;
      }
    }
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}


#undef    MOONANIMATION_CPP
