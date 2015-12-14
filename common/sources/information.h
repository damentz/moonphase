/*
** This file is part of moonphase.
** Copyright (C) 2014-2015 by Alan Wise (alanwise@users.sourceforge.net)
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
*** \file TODO.h
*** \brief TODO
*** \details TODO
**/


#ifndef   TODO_H
#define   TODO_H


/****
*****
***** INCLUDES
*****
****/

#include  "datetime.h"
#include  "moondata.h"


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

typedef struct structMOONDATAPRINTOPTIONS
{
  DATETIMEOPTIONS_T DateTimeOptions;
} MOONDATAPRINTOPTIONS_T;

/**
*** \brief Edit mode.
*** \details The edit mode of the dialog box. This determines which options
***   can be edited by the user.
**/
typedef enum enumEDITMODE
{
  /**
  *** \brief Invalid edit mode.
  *** \brief In this mode, no dialog box will be displayed.
  **/
  EDITMODE_INVALID=-1,
  /**
  *** \brief Display edit mode.
  *** \details In this mode, the user can only edit display options
  ***   (colors, font, etc.).
  **/
  EDITMODE_DISPLAY=0,
  /**
  *** \brief Units edit mode.
  *** \details In this mode, in addition to the display options, the user
  ***   also can select the units of measurement.
  **/
  EDITMODE_UNITS,
  /**
  *** \brief Time edit mode.
  *** \details In this mode, in addition to the display options, the user
  ***   also can edit how the time is displayed.
  **/
  EDITMODE_TIME,
  /**
  *** \brief Date/time edit mode.
  *** \details In this mode, in addition to the display options, the user
  ***   also can edit how the date and time are displayed.
  **/
  EDITMODE_DATETIME
} EDITMODE_T;


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

ERRORCODE_T Information_GetDefaultUnitFormatIndex(
    int InfoTypeIndex,BOOLEAN_T ImperialFlag,int *pIndex);
ERRORCODE_T Information_GetEditMode(int InfoItemIndex,EDITMODE_T *pMode);
ERRORCODE_T Information_GetFormat(
    int InfoItemIndex,int UnitFormatIndex,char **ppFormat);
ERRORCODE_T Information_GetLabel(int Index,char const **ppLabel);
ERRORCODE_T Information_GetUnitFormatDescription(
    int InfoItemIndex,int UnitFormatIndex,char **ppDescription);
ERRORCODE_T Information_Print(
    MOONDATA_T const *pMoonData,int InfoTypeIndex,int UnitsFormatIndex,
    MOONDATAPRINTOPTIONS_T const *pOptions,char **ppResult);

#ifdef  __cplusplus
}
#endif  /* __cplusplus */


#endif    /* TODO_H */
