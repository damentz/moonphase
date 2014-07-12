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
*** \file moonanimation.h
*** \brief Reads an image and separates it into frames.
*** \details Reads an image which contains a series of frames, and separates
***   the each frame into an individual image.
**/


#ifndef   MOONANIMATION_H
#define   MOONANIMATION_H


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
*** \brief Moon animation structure.
*** \details Structure for moon animation.
**/
typedef struct structMOONANIMATION
{
  /**
  *** \brief Image path name.
  *** \details Path name to image.
  **/
  QString *pFileName;
  /**
  *** \brief Image frames.
  *** \details List of frames in the image.
  **/
  QList<QPixmap> *pImages;
} MOONANIMATION_T;


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

STRUCTURE_PROTOTYPE_INITIALIZE(MoonAnimation,MOONANIMATION_T);
STRUCTURE_PROTOTYPE_INITIALIZEMEMBERS(MoonAnimation,MOONANIMATION_T);
STRUCTURE_PROTOTYPE_UNINITIALIZE(MoonAnimation,MOONANIMATION_T);
STRUCTURE_PROTOTYPE_UNINITIALIZEMEMBERS(MoonAnimation,MOONANIMATION_T);
/**
*** \brief Returns the image path name.
*** \details Returns the path name of the image.
*** \param pMoonAnimation Pointer to moon animation structure.
*** \param Index Frame index.
*** \param ppFrame Storage for frame data pointer.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
ERRORCODE_T MoonAnimation_GetPathName(
    MOONANIMATION_T const *pMoonAnimation,QString *pPathName);
/**
*** \brief Returns a frame.
*** \details Returns a frame from the image.
*** \param pMoonAnimation Pointer to moon animation structure.
*** \param Index Frame index.
*** \param ppFrame Storage for frame data pointer.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
ERRORCODE_T MoonAnimation_GetFrame(
    MOONANIMATION_T const *pMoonAnimation,int Index,QPixmap const **ppFrame);
/**
*** \brief Returns the frame count.
*** \details Returns the number of frames in the image.
*** \param pMoonAnimation Pointer to moon animation structure.
*** \retval >0 Success.
*** \retval <0 Failure.
**/
ERRORCODE_T MoonAnimation_GetFrameCount(MOONANIMATION_T const *pMoonAnimation);
/**
*** \brief Reads image and separates it into frames.
*** \details Reads an image which contains a series of frames, and separates
***   the each frame into an individual image.
*** \param pMoonAnimation Pointer to moon animation structure.
*** \param pPathname Animation path name.
*** \retval >0 Success.
*** \retval =0 Unable to read file.
*** \retval <0 Failure.
**/
ERRORCODE_T MoonAnimation_ReadFile(
    MOONANIMATION_T *pMoonAnimation,char const *pPathname);

#ifdef  __cplusplus
}
#endif  /* __cplusplus */


#endif    /* MOONANIMATION_H */
