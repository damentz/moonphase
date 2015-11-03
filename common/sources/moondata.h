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

typedef struct structMOONDATA
{
  CTrans CTransData;
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
void MoonData_Recalculate(MOONDATA_T *pMoon,time_t UTC);

#ifdef  __cplusplus
}
#endif  /* __cplusplus */


#endif    /* MOONDATA_H */
