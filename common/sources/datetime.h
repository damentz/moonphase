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
*** \file datetime.h
*** \brief Print date/time.
*** \details Converts a date/time according to a string in accordance to
***   various options.
**/


#ifndef   DATETIME_H
#define   DATETIME_H


/****
*****
***** INCLUDES
*****
****/

#include  "errorcode.h"
#include  "sysdefs.h"

#include  <time.h>


/****
*****
***** DEFINES
*****
****/

/**
*** \brief Date/time flags.
*** \details What and how to print various options.
**/
typedef enum enumDATETIMEFLAGS
{
  /**
  *** \brief Print in 24 hour format.
  *** \details Print the hour in 24 hour format.
  **/
  DATETIMEFLAG_24HOURFORMAT=1,
  /**
  *** \brief Print 4 digit year.
  *** \details Print the year using 4 digits instead of 2.
  **/
  DATETIMEFLAG_4DIGITYEAR=2,
  /**
  *** \brief Print the long format day of week.
  *** \details Print the day of the week in a long format (not abbreviated).
  **/
  DATETIMEFLAG_LONGDAYOFWEEKFORMAT=4,
  /**
  *** \brief Print the long format month.
  *** \details Print the month in a long format (not abbreviated).
  **/
  DATETIMEFLAG_LONGMONTHFORMAT=8,
  /**
  *** \brief Print the day of the week.
  *** \details Print the day of the week (abbreviated).
  **/
  DATETIMEFLAG_SHOWDAYOFWEEK=16,
  /**
  *** \brief Print seconds.
  *** \details Print the number of seconds.
  **/
  DATETIMEFLAG_SHOWSECONDS=32
} DATETIMEFLAGS_F;


/****
*****
***** DATA TYPES
*****
****/

/**
*** \brief Date/time options.
*** \details What and how to print various options.
**/
typedef struct structDATETIMEOPTIONS
{
  /**
  *** \brief Date style index.
  *** \details The index used to determine the format string used to print the
  ***   date/time.
  **/
  int DateStyleIndex;
  /**
  *** \brief Print flags.
  *** \details Flags controlling what and how to print a date/time.
  **/
  int Flags;    /* Compiler doesn't like DATETIMEFLAGS_T in C++. */
} DATETIMEOPTIONS_T;


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

/**
*** \brief Print date/time.
*** \details Converts a date/time according to a string in accordance to
***   various options.
*** \param DateTimeModeFlag 0 - Modify time format only\n
***   !0 - Modify date and time formats.
*** \param pTime Time to use for sample text.
*** \param pDTFormat Basic date format (day, month, year).
*** \param pOptions Options use to modify the format.
*** \param ppDateTime Resulting text.
*** \returns
**/
ERRORCODE_T DateTime_Print(
    BOOLEAN_T DateTimeModeFlag,struct tm const *pTime,
    char const *pDTFormat,DATETIMEOPTIONS_T const *pOptions,
    char **ppDateTime);

#ifdef  __cplusplus
}
#endif  /* __cplusplus */


#endif    /* DATETIME_H */
