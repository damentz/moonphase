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
*** \file moondata.h
*** \brief Moon data computations and information.
*** \details Recompuates the moon data as neeeded, and provides access to the
***   data.
**/


#ifndef   MOONDATA_H
#define   MOONDATA_H


/****
*****
***** INCLUDES
*****
****/

#include  "calcephem.h"
#include  "structure.h"
#include  "datetime.h"

#include  <time.h>


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
*** \brief
*** \details
**/
typedef struct structMOONDATA
{
  /**
  *** \brief
  *** \details
  **/
  CTrans CTransData;

  /**
  *** \brief Yesterdays moon rise time.
  *** \details The time the moon rise yesterday.
  **/
  double YesterdaysRise;

  /**
  *** \brief Yesterdays moon set time.
  *** \details The time the moon set yesterday.
  **/
  double YesterdaysSet;

  /**
  *** \brief Todays moon rise time.
  *** \details The time the moon rose/will rise today.
  **/
  double TodaysRise;

  /**
  *** \brief Todays moon set time.
  *** \details The time the moon set/will set today.
  **/
  double TodaysSet;

  /**
  *** \brief Tomorrows moon rise time.
  *** \details The time the moon will rise tomorrow.
  **/
  double TomorrowsRise;

  /**
  *** \brief Tomorrows moon set time.
  *** \details The time the moon set/will set tomorrow.
  **/
  double TomorrowsSet;
} MOONDATA_T;


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

STRUCTURE_PROTOTYPE_INITIALIZE(MoonData,MOONDATA_T);
STRUCTURE_PROTOTYPE_UNINITIALIZE(MoonData,MOONDATA_T);
float MoonData_GetMoonPhasePercent(MOONDATA_T const *pMoon);
/**
*** \brief
*** \details
*** \param pMoonData Pointer to the moon data.
*** \param UTC Current time in UTC.
**/
void MoonData_Recalculate(MOONDATA_T *pMoonData,time_t UTC);

#ifdef  __cplusplus
}
#endif  /* __cplusplus */


#endif    /* MOONDATA_H */
