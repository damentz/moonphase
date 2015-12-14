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
#ifdef    DEBUG_MOONDATA_C
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_MOONDATA_C */
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

extern double Glon;
extern double TimeZone;


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
void MoonData_Recalculate(MOONDATA_T *pMoonData,time_t UTC)
{
  struct tm *pUTC;
  int UTCHour;
  struct tm *pLocalTime;
  double Time;
  long Date;
  struct tm AdjustedTime;
  time_t NormalizedTime;


  DEBUGLOG_Printf1("MoonData_Recalculate(%p)",pMoonData);
  DEBUGLOG_LogIn();

  /* Get the UTC time. */
  pUTC=gmtime(&UTC);

  /* Convert time to hours. */
  Time=pUTC->tm_hour+pUTC->tm_min/60.0+pUTC->tm_sec/3600.0;

  /* Covert date to CalcEphem format (YYYYMMDD).*/
  Date=10000*(pUTC->tm_year+1900)+100*(pUTC->tm_mon+1)+pUTC->tm_mday;

  /* Get the local time. */
  UTCHour=pUTC->tm_hour;    // pUTC and pLocalTime use same buffer.
  pLocalTime=localtime(&UTC);

  /* Update moon data. */
  Glon=pMoonData->CTransData.Glon;
  TimeZone=UTCHour-pLocalTime->tm_hour; /* tm_gmtoff not supported in Windows */
  CalcEphem(Date,Time,&pMoonData->CTransData);

  /* Update yesterdays rise/set times. */
  memset(&AdjustedTime,0,sizeof(AdjustedTime));
  AdjustedTime.tm_year=pMoonData->CTransData.year-1900;
  AdjustedTime.tm_mon=pMoonData->CTransData.month-1;
  AdjustedTime.tm_mday=pMoonData->CTransData.day-1;   // Yesterday.
  AdjustedTime.tm_isdst=-1;   // Figure it out.
  NormalizedTime=mktime(&AdjustedTime);
  pUTC=gmtime(&NormalizedTime);
  MoonRise(pUTC->tm_year+1900,pUTC->tm_mon+1,pUTC->tm_mday,0,
    &pMoonData->YesterdaysRise,&pMoonData->YesterdaysSet);

  /* Update todays rise/set times. */
  AdjustedTime.tm_mday++;
  NormalizedTime=mktime(&AdjustedTime);
  pUTC=gmtime(&NormalizedTime);
  MoonRise(pUTC->tm_year+1900,pUTC->tm_mon+1,pUTC->tm_mday,0,
    &pMoonData->TodaysRise,&pMoonData->TodaysSet);

  /* Update tomorrows rise/set times. */
  AdjustedTime.tm_mday++;
  NormalizedTime=mktime(&AdjustedTime);
  pUTC=gmtime(&NormalizedTime);
  MoonRise(pUTC->tm_year+1900,pUTC->tm_mon+1,pUTC->tm_mday,0,
    &pMoonData->TomorrowsRise,&pMoonData->TomorrowsSet);

  DEBUGLOG_LogOut();
  return;
}


#undef    MOONDATA_C
