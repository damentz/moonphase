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
*** \file TODO.c
*** \brief TODO.c implementation.
*** \details Implementation file for TODO.c.
**/


/** Identifier for TODO.c. **/
#define   TODO_C


/****
*****
***** INCLUDES
*****
****/

#include  "information.h"
#ifdef    DEBUG_TODO_C
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_TODO_C */
#include  "debuglog.h"
#include  "messagelog.h"
#include  "visualstudio.h"

#include  <stdlib.h>
#include  <math.h>
#include  <stdio.h>


/****
*****
***** DEFINES
*****
****/

/**
*** \brief Earth radius.
*** \details The radius of the earth (in miles).
**/
#define   EARTH_RADIUS    (3959.0)

/**
*** \brief Number of array elements.
*** \details Returns the number of elements in an array.
*** \warning The array must be declared as an array (with the [] syntax) for
***   this to work.
**/
#define   ARRAY_ELEMENTCOUNT(a) \
    /* Array should never get large enough to overflow a signed integer. */ \
    (int)(sizeof(a)/sizeof(*a))

#define   DOUBLE2STRUCTTM(db,tm) \
              (tm).tm_hour=(int)(db); \
              (tm).tm_min=(int)(60*((db)-(tm).tm_hour)); \
              (tm).tm_sec=(int)(3600*((db)-((tm).tm_hour+(tm).tm_min/60.0)));

#define   UNITTYPE2UNITPOINTERANDSIZE(ut,up,us) \
              (up)=NULL; \
              (us)=0; \
              switch(ut) \
              { \
                case UNITTYPE_NONE: \
                case UNITTYPE_DATETIME: \
                case UNITTYPE_TIME: \
                default: \
                  break; \
                case UNITTYPE_AGE: \
                  (up)=f_pAgeUnits; \
                  (us)=ARRAY_ELEMENTCOUNT(f_pAgeUnits); \
                  break; \
                case UNITTYPE_ANGLE: \
                  (up)=f_pAngleUnits; \
                  (us)=ARRAY_ELEMENTCOUNT(f_pAngleUnits); \
                  break; \
                case UNITTYPE_ARC: \
                  (up)=f_pArcUnits; \
                  (us)=ARRAY_ELEMENTCOUNT(f_pArcUnits); \
                  break; \
                case UNITTYPE_DISTANCE: \
                  (up)=f_pDistanceUnits; \
                  (us)=ARRAY_ELEMENTCOUNT(f_pDistanceUnits); \
                  break; \
                case UNITTYPE_PERCENT: \
                  (up)=f_pPercentUnits; \
                  (us)=ARRAY_ELEMENTCOUNT(f_pPercentUnits); \
                  break; \
              }

#define   UNITTYPE2FORMATPOINTERANDSIZE(ut,fl,fs) \
              (fl)=NULL; \
              (fs)=0; \
              switch(ut) \
              { \
                case UNITTYPE_NONE: \
                case UNITTYPE_AGE: \
                case UNITTYPE_ANGLE: \
                case UNITTYPE_ARC: \
                case UNITTYPE_DISTANCE: \
                case UNITTYPE_PERCENT: \
                case UNITTYPE_TIME: \
                default: \
                  break; \
                case UNITTYPE_DATETIME: \
                  (fl)=f_pDateTimeFormatList; \
                  (fs)=ARRAY_ELEMENTCOUNT(f_pDateTimeFormatList); \
                  break; \
              }


/****
*****
***** DATA TYPES
*****
****/

/**
*** \brief Unit flags.
*** \details Determines the unit type.
**/
typedef enum enumUNITFLAGS
{
  UNITFLAGS_NONE,
  UNITFLAGS_DEFAULTMETRIC=1,
  UNITFLAGS_DEFAULTIMPERIAL=2,
  UNITFLAGS_DONTSHOW=4,
  UNITFLAGS_HIDEFIRSTSPACE=8
} UNITFLAGS_F;

/**
*** \brief Unit data.
*** \details Defines various data about a measurement unit.
**/
typedef struct structUNITDATA
{
  /**
  *** \brief Short name.
  *** \details Short name (abbreviation) for the unit.
  **/
  wchar_t const *pShortName;
  /**
  *** \brief Long name.
  *** \details Long name for the unit.
  **/
  char const *pLongName;
  /**
  *** \brief Scale factor.
  *** \details Scale factor used to convert between internal units and user
  ***   units.
  **/
  double Scale;
  /**
  *** \brief Precision.
  *** \details How many digits to print after the decimal point.
  **/
  int Precision;
  /**
  *** \brief Unit flags.
  *** \details Default unit flags (metric, imperial, none).
  **/
  UNITFLAGS_F UnitFlags;
} UNITDATA_T;

typedef enum enumUNITTYPE
{
  UNITTYPE_NONE,
  UNITTYPE_AGE,
  UNITTYPE_ANGLE,
  UNITTYPE_ARC,
  UNITTYPE_DATETIME,
  UNITTYPE_DISTANCE,
  UNITTYPE_PERCENT,
  UNITTYPE_TIME
} UNITTYPE_E;

/**
*** \brief TODO Moon data item.
*** \details TODO Defines a label, possible unit list and a print function for each
***   item in the data list.
**/
typedef struct structINFORMATIONDATA
{
  /**
  *** \brief Data label.
  *** \details Label for the displayed data.
  **/
  char const *pLabel;
  /**
  *** \brief Unit type.
  *** \details Type of unit that this item can use to display information.
  **/
  UNITTYPE_E UnitType;
  EDITMODE_T EditMode;
} INFORMATIONDATA_T;

typedef struct structDATETIMEDATA
{
  char const *pName;
  char const *pFormat;
} DATETIMEDATA_T;


/****
*****
***** PROTOTYPES
*****
****/

static int PrintArcHMS(double DTime,int Precision,char **ppText);


/****
*****
***** DATA
*****
****/

/**
*** \brief Age units.
*** \details Units used by data items that are ages.
**/
static const UNITDATA_T f_pAgeUnits[]=
{
  { L"days","Days",1.0,1,
      (UNITFLAGS_F)(UNITFLAGS_DEFAULTMETRIC|UNITFLAGS_DEFAULTIMPERIAL) }
};

/**
*** \brief Angle units.
*** \details Units used by data items that are angles.
**/
static const UNITDATA_T f_pAngleUnits[]=
{
  { L"\u00B0","Degrees",1.0,2,
      (UNITFLAGS_F)(UNITFLAGS_DEFAULTMETRIC|
      UNITFLAGS_DEFAULTIMPERIAL|UNITFLAGS_HIDEFIRSTSPACE) },
  { L"\u33AD","Radians",M_PI/180.0,5,
      (UNITFLAGS_F)(UNITFLAGS_NONE|UNITFLAGS_HIDEFIRSTSPACE) }
};

/**
*** \brief
*** \details
**/
static const UNITDATA_T f_pArcUnits[]=
{
  { L"\u00B0","Degrees",1.0,2,UNITFLAGS_NONE },
  { L"hms","Hours, minutes, seconds",1.0,2,
      (UNITFLAGS_F)(UNITFLAGS_DEFAULTMETRIC|UNITFLAGS_DEFAULTIMPERIAL|
      UNITFLAGS_DONTSHOW) }
};

/**
*** \brief Distance units.
*** \details Units used by data items that are distances.
**/
static const UNITDATA_T f_pDistanceUnits[]=
{
  { L"'","Feet",5280.0,0,UNITFLAGS_NONE },
  { L"m","Meters",1609.344,0,UNITFLAGS_NONE },
  { L"km","Kilometers",1.609344,0,UNITFLAGS_DEFAULTMETRIC },
  { L"mi","Miles",1.0,0,UNITFLAGS_DEFAULTIMPERIAL },
  { L"au","Astronomical units",1.0758e-8,5,UNITFLAGS_NONE }
};

/**
*** \brief Percent units.
*** \details Units used by data items that are percents.
**/
static const UNITDATA_T f_pPercentUnits[]=
{
  { L"%","Percent",1.0,1,(UNITFLAGS_F)(UNITFLAGS_DEFAULTMETRIC|
      UNITFLAGS_DEFAULTIMPERIAL|UNITFLAGS_HIDEFIRSTSPACE) }
};

static const INFORMATIONDATA_T f_pInformation[]=
{
#define   INFOTYPE_AGE                (0)
  { "Age",UNITTYPE_AGE,EDITMODE_UNITS },
#define   INFOTYPE_ALTITUDE           (1)
  { "Altitude",UNITTYPE_ANGLE,EDITMODE_UNITS },
#define   INFOTYPE_AZIMUTH            (2)
  { "Azimuth",UNITTYPE_ANGLE,EDITMODE_UNITS },
#define   INFOTYPE_DECLINATION        (3)
  { "Declination",UNITTYPE_ARC,EDITMODE_UNITS },
#define   INFOTYPE_DISTANCEFROMEARTH  (4)
  { "Distance from earth",UNITTYPE_DISTANCE,EDITMODE_UNITS },
#define   INFOTYPE_ILLUMINATION       (5)
  { "Illumination (%)",UNITTYPE_PERCENT,EDITMODE_UNITS },
#define   INFOTYPE_LOCALTIME          (6)
  { "Local time",UNITTYPE_DATETIME,EDITMODE_DATETIME },
#define   INFOTYPE_PHASEPERCENT       (7)
  { "Phase (%)",UNITTYPE_PERCENT,EDITMODE_UNITS },
#define   INFOTYPE_PHASETEXT          (8)
  { "Phase (text)",UNITTYPE_NONE,EDITMODE_DISPLAY },
#define   INFOTYPE_RIGHTASCENTION     (9)
  { "Right ascention",UNITTYPE_ARC,EDITMODE_UNITS },
#define   INFOTYPE_TODAYSRISE         (10)
  { "Todays rise",UNITTYPE_TIME,EDITMODE_TIME },
#define   INFOTYPE_TODAYSSET          (11)
  { "Todays set",UNITTYPE_TIME,EDITMODE_TIME },
#define   INFOTYPE_TOMORROWSRISE      (12)
  { "Tomorrows rise",UNITTYPE_TIME,EDITMODE_TIME },
#define   INFOTYPE_TOMORROWSSET       (13)
  { "Tomorrows set",UNITTYPE_TIME,EDITMODE_TIME },
#define   INFOTYPE_UNIVERSALTIME      (14)
  { "Universal time",UNITTYPE_DATETIME,EDITMODE_DATETIME },
#define   INFOTYPE_VISIBLE            (15)
  { "Visible",UNITTYPE_NONE,EDITMODE_DISPLAY },
#define   INFOTYPE_YESTERDAYSRISE     (16)
  { "Yesterdays rise",UNITTYPE_TIME,EDITMODE_TIME },
#define   INFOTYPE_YESTERDAYSSET      (17)
  { "Yesterdays set",UNITTYPE_TIME,EDITMODE_TIME },
};

DATETIMEDATA_T const f_pDateTimeFormatList[]=
{
  { "M. d, y","%b. %d, %y" },
  { "m/d/y","%m/%d/%y" },
  { "d/m/y","%d/%m/%y" },
};

/**
*** \brief
*** \details
**/
static const struct
{
  short Min;
  short Max;
  char const *pName;
} f_pPhaseNameData[]=
{
  {  0,  1,"New Moon" },
  {  1, 25,"Waxing Crescent" },
  { 25, 27,"First Quarter" },
  { 27, 49,"Waxing Gibbous" },
  { 49, 51,"Full Moon" },
  { 51, 74,"Waning Gibbous" },
  { 74, 76,"Last Quarter" },
  { 76, 99,"Waning Crescent" },
  { 99,100,"New Moon" },
};


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

static ERRORCODE_T PrintArcHMS(double DTime,int Precision,char **ppText)
{
  ERRORCODE_T ErrorCode;
  int H,M;
  double S;
  char const *pFormatString="-%dh %dm %.*fs";


  DEBUGLOG_Printf3("PrintArcHMS(%d,%d,%p)",DTime,Precision,ppText);
  DEBUGLOG_LogIn();

  /* Break the time into H, M, S. */
  DTime/=15.0;
  H=(int)DTime;
  M=(int)(60*(DTime-H));
  S=(int)(60*(60*DTime-60*H-M));

  /* Print. */
  if (DTime>=0)
    pFormatString++;

  if (asprintf(ppText,pFormatString,abs(H),abs(M),Precision,fabs(S))==-1)
    ErrorCode=ERRORCODE_SYSTEMFAILURE;
  else
    ErrorCode=ERRORCODE_SUCCESS;

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T Information_GetDefaultUnitFormatIndex(
    int InfoTypeIndex,BOOLEAN_T ImperialFlag,int *pIndex)
{
  ERRORCODE_T ErrorCode;
  UNITDATA_T const *pUnitList;
  int UnitListSize;
  DATETIMEDATA_T const *pFormatList;
  int FormatListSize;
  int DefaultUnitFlag;
  int Index;

  UNUSED(FormatListSize);

  DEBUGLOG_Printf3(
      "GetDefaultUnitFormatIndex(%d,%u,%p)",InfoTypeIndex,ImperialFlag,pIndex);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pIndex==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else if ( (InfoTypeIndex<0) ||
      (InfoTypeIndex>=ARRAY_ELEMENTCOUNT(f_pInformation)) )
  {
    *pIndex=-1;
    ErrorCode=ERRORCODE_INVALIDPARAMETER;
  }
  else
  {
    UNITTYPE2UNITPOINTERANDSIZE(
        f_pInformation[InfoTypeIndex].UnitType,pUnitList,UnitListSize);
    UNITTYPE2FORMATPOINTERANDSIZE(
        f_pInformation[InfoTypeIndex].UnitType,pFormatList,FormatListSize);

    /* Default. */
    *pIndex=-1;
    ErrorCode=ERRORCODE_INVALIDPARAMETER;

    /* Unit list. */
    if (pUnitList!=NULL)
    {
      /* Set up the default mask. */
      if (ImperialFlag==0)
        DefaultUnitFlag=UNITFLAGS_DEFAULTMETRIC;
      else
        DefaultUnitFlag=UNITFLAGS_DEFAULTIMPERIAL;

      /* Loop through the list, looking for a matching default. */
      for(Index=0;Index<UnitListSize;Index++)
      {
        if ( (pUnitList[Index].UnitFlags&DefaultUnitFlag)!=0 )
        {
          *pIndex=Index;
          ErrorCode=ERRORCODE_SUCCESS;
          break;
        }
      }
    }
    /* Format list. */
    else if (pFormatList!=NULL)
    {
      *pIndex=0;
      ErrorCode=ERRORCODE_SUCCESS;
    }
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T Information_GetEditMode(int InfoItemIndex,EDITMODE_T *pMode)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf2("Information_GetEditMode(%d,%p)",InfoItemIndex,pMode);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pMode==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else if ( (InfoItemIndex<0) ||
      (InfoItemIndex>=ARRAY_ELEMENTCOUNT(f_pInformation)) )
  {
    *pMode=EDITMODE_INVALID;
    ErrorCode=ERRORCODE_INVALIDPARAMETER;
  }
  else
  {
    *pMode=f_pInformation[InfoItemIndex].EditMode;
    ErrorCode=ERRORCODE_SUCCESS;
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T Information_GetFormat(
    int InfoItemIndex,int UnitFormatIndex,char **ppFormat)
{
  ERRORCODE_T ErrorCode;
  DATETIMEDATA_T const *pFormatList;
  int FormatListSize;


  DEBUGLOG_Printf3(
      "Information_GetFormat(%d,%d,%p)",InfoItemIndex,UnitFormatIndex,ppFormat);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (ppFormat==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else if ( (InfoItemIndex<0) &&
      (InfoItemIndex>=ARRAY_ELEMENTCOUNT(f_pInformation)) )
  {
    *ppFormat=NULL;
    ErrorCode=ERRORCODE_INVALIDPARAMETER;
  }
  else
  {
    ErrorCode=ERRORCODE_INVALIDPARAMETER;

    UNITTYPE2FORMATPOINTERANDSIZE(
        f_pInformation[InfoItemIndex].UnitType,pFormatList,FormatListSize);
    if (pFormatList!=NULL)
    {
      if ( (UnitFormatIndex<0) || (UnitFormatIndex>=FormatListSize) )
        *ppFormat=NULL;
      else
      {
        *ppFormat=strdup(pFormatList[UnitFormatIndex].pFormat);
        ErrorCode=ERRORCODE_SUCCESS;
      }
    }
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T Information_GetLabel(int InfoItemIndex,char const **ppLabel)
{
  ERRORCODE_T ErrorCode;


  DEBUGLOG_Printf2("Information_GetLabel(%d,%p)",InfoItemIndex,ppLabel);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (ppLabel==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else if ( (InfoItemIndex<0) ||
      (InfoItemIndex>=ARRAY_ELEMENTCOUNT(f_pInformation)) )
  {
    *ppLabel=NULL;
    ErrorCode=ERRORCODE_INVALIDPARAMETER;
  }
  else
  {
    *ppLabel=f_pInformation[InfoItemIndex].pLabel;
    ErrorCode=ERRORCODE_SUCCESS;
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}

ERRORCODE_T Information_GetUnitFormatDescription(
    int InfoItemIndex,int UnitFormatIndex,char **ppDescription)
{
  ERRORCODE_T ErrorCode;
  UNITDATA_T const *pUnitList;
  int UnitListSize;
  DATETIMEDATA_T const *pFormatList;
  int FormatListSize;
#define   GUFDS_BUFFER_SIZE   (1024)
  char pBuffer[GUFDS_BUFFER_SIZE];


  DEBUGLOG_Printf3("Information_GetUnitFormatDescription(%d,%d,%p)",
      InfoItemIndex,UnitFormatIndex,ppDescription);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (ppDescription==NULL)
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else if ( (InfoItemIndex<0) &&
      (InfoItemIndex>=ARRAY_ELEMENTCOUNT(f_pInformation)) )
  {
    *ppDescription=NULL;
    ErrorCode=ERRORCODE_INVALIDPARAMETER;
  }
  else
  {
    *ppDescription=NULL;
    ErrorCode=ERRORCODE_INVALIDPARAMETER;

    UNITTYPE2UNITPOINTERANDSIZE(
        f_pInformation[InfoItemIndex].UnitType,pUnitList,UnitListSize);
    UNITTYPE2FORMATPOINTERANDSIZE(
        f_pInformation[InfoItemIndex].UnitType,pFormatList,FormatListSize);
    if (pUnitList!=NULL)
    {
      if ( (UnitFormatIndex>=0) && (UnitFormatIndex<UnitListSize) )
      {
        ErrorCode=ERRORCODE_SYSTEMFAILURE;
        if (wcstombs(pBuffer,pUnitList[UnitFormatIndex].pShortName,
            GUFDS_BUFFER_SIZE)!=(size_t)-1)
          if (asprintf(ppDescription,"%s (%s)",pBuffer,
              pUnitList[UnitFormatIndex].pLongName)!=-1)
            ErrorCode=ERRORCODE_SUCCESS;
      }
    }
    else if (pFormatList!=NULL)
    {
      if ( (UnitFormatIndex>=0) && (UnitFormatIndex<FormatListSize) )
      {
        *ppDescription=strdup(pFormatList[UnitFormatIndex].pName);
        if (*ppDescription==NULL)
          ErrorCode=ERRORCODE_SYSTEMFAILURE;
        else
          ErrorCode=ERRORCODE_SUCCESS;
      }
    }
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}







ERRORCODE_T Information_Print(
    MOONDATA_T const *pMoonData,int InfoTypeIndex,int UnitFormatIndex,
    MOONDATAPRINTOPTIONS_T const *pOptions,char **ppResult)
{
  ERRORCODE_T ErrorCode;
  UNITDATA_T const *pUnitList;
  int UnitListSize;
  DATETIMEDATA_T const *pFormatList;
  int FormatListSize;
//  int UnitFormatIndex;
  char *pText;
//  /* TEMP */ int Precision=2;
//  /* TEMP */ double ScaleFactor=1.0;
  wchar_t const *pUnitFormat;
#define   P_BUFFER_SIZE   (1024)
  char pBuffer[P_BUFFER_SIZE];
//  BOOLEAN_T HideFirstSpaceFlag;
//  BOOLEAN_T DontShowFlag;
  UNITFLAGS_F UnitFlags;
  char *pSeparator;


  DEBUGLOG_Printf5("Print(%p,%d,%d,%p,%p)",
      pMoonData,InfoTypeIndex,UnitFormatIndex,pOptions,ppResult);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (pMoonData==NULL) || (pOptions==NULL) || (ppResult==NULL) ||
      (ppResult==NULL) )
    ErrorCode=ERRORCODE_NULLPARAMETER;
  else if ( (InfoTypeIndex<0) ||
      (InfoTypeIndex>=ARRAY_ELEMENTCOUNT(f_pInformation)) )
  {
    *ppResult=NULL;
    ErrorCode=ERRORCODE_INVALIDPARAMETER;
  }
  else
  {
    ErrorCode=ERRORCODE_SUCCESS;
    pText=NULL;

    /* Get the unit/format table pointers and sizes. */
    UNITTYPE2UNITPOINTERANDSIZE(
        f_pInformation[InfoTypeIndex].UnitType,pUnitList,UnitListSize);
    UNITTYPE2FORMATPOINTERANDSIZE(
        f_pInformation[InfoTypeIndex].UnitType,pFormatList,FormatListSize);

    /* Bounds check the unit/format index. */
    if ( ((pUnitList!=NULL) &&
        ((UnitFormatIndex<0) || (UnitFormatIndex>=UnitListSize))) ||
        ((pFormatList!=NULL) &&
        ((UnitFormatIndex<0) || (UnitFormatIndex>=FormatListSize))) )
      ErrorCode=ERRORCODE_INVALIDPARAMETER;

    if (ErrorCode==ERRORCODE_SUCCESS)
    {
      /* No. */
      switch(InfoTypeIndex)
      {
        case INFOTYPE_AGE:
          if (asprintf(&pText,"%.*f",pUnitList[UnitFormatIndex].Precision,
              pMoonData->CTransData.MoonAge)==-1)
            ErrorCode=ERRORCODE_SYSTEMFAILURE;
          pUnitFormat=pUnitList[UnitFormatIndex].pShortName;
          UnitFlags=pUnitList[UnitFormatIndex].UnitFlags;
          break;
        case INFOTYPE_ALTITUDE:
          if (asprintf(&pText,"%.*f",pUnitList[UnitFormatIndex].Precision,
              pMoonData->CTransData.h_moon*pUnitList[UnitFormatIndex].Scale)
              ==-1)
            ErrorCode=ERRORCODE_SYSTEMFAILURE;
          pUnitFormat=pUnitList[UnitFormatIndex].pShortName;
          UnitFlags=pUnitList[UnitFormatIndex].UnitFlags;
          break;
        case INFOTYPE_AZIMUTH:
          if (asprintf(&pText,"%.*f",pUnitList[UnitFormatIndex].Precision,
              pMoonData->CTransData.A_moon*pUnitList[UnitFormatIndex].Scale)
              ==-1)
            ErrorCode=ERRORCODE_SYSTEMFAILURE;
          pUnitFormat=pUnitList[UnitFormatIndex].pShortName;
          UnitFlags=pUnitList[UnitFormatIndex].UnitFlags;
          break;
        case INFOTYPE_DECLINATION:
          {
            double Dec;


            Dec=pMoonData->CTransData.DEC_moon;
            if (UnitFormatIndex==0)
            {
              if (asprintf(&pText,"%.*f",
                  pUnitList[UnitFormatIndex].Precision,Dec)==-1)
                ErrorCode=ERRORCODE_SYSTEMFAILURE;
            }
            else
              ErrorCode=
                  PrintArcHMS(Dec,pUnitList[UnitFormatIndex].Precision,&pText);
            pUnitFormat=pUnitList[UnitFormatIndex].pShortName;
            UnitFlags=pUnitList[UnitFormatIndex].UnitFlags;
            break;
          }
        case INFOTYPE_DISTANCEFROMEARTH:
          if (asprintf(&pText,"%.*f",pUnitList[UnitFormatIndex].Precision,
              pMoonData->CTransData.EarthMoonDistance*EARTH_RADIUS*
              pUnitList[UnitFormatIndex].Scale)==-1)
            ErrorCode=ERRORCODE_SYSTEMFAILURE;
          pUnitFormat=pUnitList[UnitFormatIndex].pShortName;
          UnitFlags=pUnitList[UnitFormatIndex].UnitFlags;
          break;
        case INFOTYPE_ILLUMINATION:
          if (asprintf(&pText,"%.*f",pUnitList[UnitFormatIndex].Precision,
              100*0.5*(1.0-cos(pMoonData->CTransData.MoonPhase*2*M_PI)))==-1)
            ErrorCode=ERRORCODE_SYSTEMFAILURE;
          pUnitFormat=pUnitList[UnitFormatIndex].pShortName;
          UnitFlags=pUnitList[UnitFormatIndex].UnitFlags;
          break;
        case INFOTYPE_LOCALTIME:
          {
            time_t TimeT;


            time(&TimeT);
            ErrorCode=DateTime_Print(!0,localtime(&TimeT),
                pFormatList[UnitFormatIndex].pFormat,
                &pOptions->DateTimeOptions,&pText);
            UnitFlags=UNITFLAGS_DONTSHOW;
          }
          break;
        case INFOTYPE_PHASEPERCENT:
          if (asprintf(&pText,"%.*f",pUnitList[UnitFormatIndex].Precision,
              MoonData_GetMoonPhasePercent(pMoonData))==-1)
            ErrorCode=ERRORCODE_SYSTEMFAILURE;
          pUnitFormat=pUnitList[UnitFormatIndex].pShortName;
          UnitFlags=pUnitList[UnitFormatIndex].UnitFlags;
          break;
        case INFOTYPE_PHASETEXT:
          {
            short Percent;
            int Index;


            ErrorCode=ERRORCODE_INVALIDDATA;
            Percent=(short)(MoonData_GetMoonPhasePercent(pMoonData)+.5);
            for(Index=0;Index<ARRAY_ELEMENTCOUNT(f_pPhaseNameData);Index++)
              if ( (Percent>=f_pPhaseNameData[Index].Min)
                  && (Percent<f_pPhaseNameData[Index].Max) )
              {
                pText=strdup(f_pPhaseNameData[Index].pName);
                ErrorCode=ERRORCODE_SUCCESS;
                break;
              }
            UnitFlags=UNITFLAGS_DONTSHOW;
          }
          break;
        case INFOTYPE_RIGHTASCENTION:
          {
            double RA;


            RA=pMoonData->CTransData.RA_moon;
            if (UnitFormatIndex==0)
            {
              if (asprintf(&pText,"%.*f",
                  pUnitList[UnitFormatIndex].Precision,RA)==-1)
                ErrorCode=ERRORCODE_SYSTEMFAILURE;
            }
            else
              ErrorCode=
                  PrintArcHMS(RA,pUnitList[UnitFormatIndex].Precision,&pText);
            pUnitFormat=pUnitList[UnitFormatIndex].pShortName;
            UnitFlags=pUnitList[UnitFormatIndex].UnitFlags;
            break;
          }
        case INFOTYPE_TODAYSRISE:
          {
            struct tm Time;


            memset(&Time,0,sizeof(Time));
            DOUBLE2STRUCTTM(pMoonData->TodaysRise,Time);
            if (pMoonData->TodaysRise==-999)
            {
                pText=strdup("None");
                if (pText==NULL)
                  ErrorCode=ERRORCODE_OUTOFMEMORY;
                else
                  ErrorCode=ERRORCODE_SUCCESS;
            }
            else
              ErrorCode=
                  DateTime_Print(0,&Time,NULL,&pOptions->DateTimeOptions,&pText);
            UnitFlags=UNITFLAGS_DONTSHOW;
          }
          break;
        case INFOTYPE_TODAYSSET:
          {
            struct tm Time;


            memset(&Time,0,sizeof(Time));
            DOUBLE2STRUCTTM(pMoonData->TodaysSet,Time);
            if (pMoonData->TodaysSet==-999)
            {
                pText=strdup("None");
                if (pText==NULL)
                  ErrorCode=ERRORCODE_OUTOFMEMORY;
                else
                  ErrorCode=ERRORCODE_SUCCESS;
            }
            else
              ErrorCode=
                  DateTime_Print(0,&Time,NULL,&pOptions->DateTimeOptions,&pText);
            UnitFlags=UNITFLAGS_DONTSHOW;
          }
          break;
        case INFOTYPE_TOMORROWSRISE:
          {
            struct tm Time;


            memset(&Time,0,sizeof(Time));
            DOUBLE2STRUCTTM(pMoonData->TomorrowsRise,Time);
            if (pMoonData->TomorrowsRise==-999)
            {
                pText=strdup("None");
                if (pText==NULL)
                  ErrorCode=ERRORCODE_OUTOFMEMORY;
                else
                  ErrorCode=ERRORCODE_SUCCESS;
            }
            else
              ErrorCode=
                  DateTime_Print(0,&Time,NULL,&pOptions->DateTimeOptions,&pText);
            UnitFlags=UNITFLAGS_DONTSHOW;
          }
          break;
        case INFOTYPE_TOMORROWSSET:
          {
            struct tm Time;


            memset(&Time,0,sizeof(Time));
            DOUBLE2STRUCTTM(pMoonData->TomorrowsSet,Time);
            if (pMoonData->TomorrowsSet==-999)
            {
                pText=strdup("None");
                if (pText==NULL)
                  ErrorCode=ERRORCODE_OUTOFMEMORY;
                else
                  ErrorCode=ERRORCODE_SUCCESS;
            }
            else
              ErrorCode=
                  DateTime_Print(0,&Time,NULL,&pOptions->DateTimeOptions,&pText);
            UnitFlags=UNITFLAGS_DONTSHOW;
          }
          break;
        case INFOTYPE_UNIVERSALTIME:
          {
            time_t TimeT;


            time(&TimeT);
            ErrorCode=DateTime_Print(!0,gmtime(&TimeT),
                pFormatList[UnitFormatIndex].pFormat,
                &pOptions->DateTimeOptions,&pText);
            UnitFlags=UNITFLAGS_DONTSHOW;
          }
          break;
        case INFOTYPE_VISIBLE:
          if (pMoonData->CTransData.Visible==0)
            pText=strdup("No");
          else
            pText=strdup("Yes");
          if (pText==NULL)
            ErrorCode=ERRORCODE_SYSTEMFAILURE;
          UnitFlags=UNITFLAGS_DONTSHOW;
          break;
        case INFOTYPE_YESTERDAYSRISE:
          {
            struct tm Time;


            memset(&Time,0,sizeof(Time));
            DOUBLE2STRUCTTM(pMoonData->YesterdaysRise,Time);
            if (pMoonData->YesterdaysRise==-999)
            {
                pText=strdup("None");
                if (pText==NULL)
                  ErrorCode=ERRORCODE_OUTOFMEMORY;
                else
                  ErrorCode=ERRORCODE_SUCCESS;
            }
            else
              ErrorCode=
                  DateTime_Print(0,&Time,NULL,&pOptions->DateTimeOptions,&pText);
            UnitFlags=UNITFLAGS_DONTSHOW;
          }
          break;
        case INFOTYPE_YESTERDAYSSET:
          {
            struct tm Time;


            memset(&Time,0,sizeof(Time));
            DOUBLE2STRUCTTM(pMoonData->YesterdaysSet,Time);
            if (pMoonData->YesterdaysSet==-999)
            {
                pText=strdup("None");
                if (pText==NULL)
                  ErrorCode=ERRORCODE_OUTOFMEMORY;
                else
                  ErrorCode=ERRORCODE_SUCCESS;
            }
            else
              ErrorCode=
                  DateTime_Print(0,&Time,NULL,&pOptions->DateTimeOptions,&pText);
            UnitFlags=UNITFLAGS_DONTSHOW;
          }
          break;
        default:
          ErrorCode=ERRORCODE_INVALIDPARAMETER;
          break;
      }

      if (ErrorCode==ERRORCODE_SUCCESS)
      {
        if ( (UnitFlags&UNITFLAGS_DONTSHOW)!=0 )
          pUnitFormat=L"";
        if(wcstombs(pBuffer,pUnitFormat,P_BUFFER_SIZE)==(size_t)-1)
          ErrorCode=ERRORCODE_SYSTEMFAILURE;
        else
        {
          if ( (UnitFlags&(UNITFLAGS_DONTSHOW|UNITFLAGS_HIDEFIRSTSPACE))!=0 )
            pSeparator="";
          else
            pSeparator=" ";
          if (asprintf(ppResult,"%s : %s%s%s",
              f_pInformation[InfoTypeIndex].pLabel,
              pText,pSeparator,pBuffer)==-1)
            ErrorCode=ERRORCODE_SYSTEMFAILURE;
        }
        if (pText!=NULL)
          free(pText);
      }
    }
  }

  DEBUGLOG_LogOut();
  return(ErrorCode);
}


#undef    TODO_C
