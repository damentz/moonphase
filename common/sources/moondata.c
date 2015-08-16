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
*** \file moondata.c
*** \brief moondata.h implementation.
*** \details Implementation file for moondata.h.
**/


/** Identifier for moondata.c. **/
#define   MOONDATA_C


/****
*****
***** INCLUDES
*****
****/

#include  "moondata.h"
#include  "sysdefs.h"
#include  <math.h>
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


/****
*****
***** PROTOTYPES
*****
****/

static STRUCTURE_PROTOTYPE_INITIALIZEMEMBERS(MoonData,MOONDATA_T);
static STRUCTURE_PROTOTYPE_UNINITIALIZEMEMBERS(MoonData,MOONDATA_T);


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

STRUCTURE_FUNCTION_INITIALIZE(MoonData,MOONDATA_T)

static STRUCTURE_PROTOTYPE_INITIALIZEMEMBERS(MoonData,MOONDATA_T)
{
  ERRORCODE_T ErrorCode;
  UNUSED(pStructure);


  DEBUGLOG_Printf1("MoonData_InitializeMembers(%p)",pStructure);
  DEBUGLOG_LogIn();

  ErrorCode=ERRORCODE_SUCCESS;

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

STRUCTURE_FUNCTION_UNINITIALIZE(MoonData,MOONDATA_T)

static STRUCTURE_PROTOTYPE_UNINITIALIZEMEMBERS(MoonData,MOONDATA_T)
{
  ERRORCODE_T ErrorCode;
  UNUSED(pStructure);


  DEBUGLOG_Printf1("MoonData_UninitializeMembers(%p)",pStructure);
  DEBUGLOG_LogIn();

  ErrorCode=ERRORCODE_SUCCESS;

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

float MoonData_GetMoonPhasePercent(MOONDATA_T const *pMoon)
{
  float Percent;


  DEBUGLOG_Printf1("MoonData_GetMoonPhasePercent(%p)",pMoon);
  DEBUGLOG_LogIn();

  Percent=(float)(100.0*pMoon->CTransData.MoonPhase);

  DEBUGLOG_LogOut();
  return(Percent);
}

void MoonData_Recalculate(MOONDATA_T *pMoon)
{
  time_t UTC;
  struct tm *pUTC;
  double Time;
  long /*time_t*/ Date;


  DEBUGLOG_Printf1("MoonData_Recalculate(%p)",pMoon);
  DEBUGLOG_LogIn();

  /* Get the current time (in seconds). */
  UTC=time(NULL);

  /* Break it apart (day, month, etc.). */
  pUTC=gmtime(&UTC);

  /* Convert time to hours. */
  Time=pUTC->tm_hour+pUTC->tm_min/60.0+pUTC->tm_sec/3600.0;

  /* Covert date to CalcEphem format (YYYYMMDD).*/
  Date=10000*(pUTC->tm_year+1900)+100*(pUTC->tm_mon+1)+pUTC->tm_mday;

  /* Update moon data. */
  CalcEphem(Date,Time,&pMoon->CTransData);

  DEBUGLOG_LogOut();
  return;
}


#undef    MOONDATA_C
