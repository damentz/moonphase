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
*** \file controlpaneldialog.cpp
*** \brief controlpaneldialog.h implementation.
*** \details Implementation file for controlpaneldialog.h.
**/


/** Identifier for controlpaneldialog.cpp. **/
#define   CONTROLPANELDIALOG_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "controlpaneldialog.h"
#ifdef    DEBUG_CONTROLPANELDIALOG_CPP
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_CONTROLPANELDIALOG_CPP */
#include  "debuglog.h"
#include  "messagelog.h"

#include  "config.h"
#include  "licenseagreement.h"
#include  "informationpaneldialog.h"
#include  "informationoptionsdialog.h"

#include  <QSettings>
#include  <QDesktopWidget>
#include  <QMenu>
#include  <QTimer>
#include  <QNetworkAccessManager>
#include  <QMessageBox>
#include  <QPainter>
#include  <QNetworkRequest>
#include  <QNetworkReply>
#include  <math.h>


/****
*****
***** DEFINES
*****
****/

/**
*** \brief Allow multiple instances flag key.
*** \details Key to access allow multiple instances flag in configuration file.
**/
#define   PREFERENCES_ALLOWMULTIPLEINSTANCESFLAG    "AllowMultipleInstancesFlag"

/**
*** \brief Animation pathname key.
*** \details Key to access animation pathname in configuration file.
**/
#define   PREFERENCES_ANIMATIONPATHNAME             "AnimationPathname"

/**
*** \brief Background color key.
*** \details Key to access background color in configuration file.
**/
#define   PREFERENCES_BACKGROUNDCOLOR               "BackgroundColor"

/**
*** \brief Confirm discard changes flag key.
*** \details Key to access confirm discard changes flag in configuration file.
**/
#define   PREFERENCES_CONFIRMDISCARDCHANGESFLAG     "ConfirmDiscardChangesFlag"

/**
*** \brief Confirm quit flag key.
*** \details Key to access confirm quit flag in configuration file.
**/
#define   PREFERENCES_CONFIRMQUITFLAG               "ConfirmQuitFlag"

/**
*** \brief Default to metric units key.
*** \details Key to access default to metric flag in configuration file.
**/
#define   PREFERENCES_DEFAULTTOMETRICUNITSFLAG      "DefaultToMetricUnitsFlag"

/**
*** \brief Use opaque background flag key.
*** \details Key to access use opaque background flag in configuration file.
**/
#define   PREFERENCES_USEOPAQUEBACKGROUNDFLAG       "UseOpaqueBackgroundFlag"

/**
*** \brief Remind once per session flag key.
*** \details Key to access remind once per session flag in configuration file.
**/
#define   PREFERENCES_REMINDONCEPERSESSIONFLAG      "RemindOncePerSessionFlag"

/**
*** \brief Still running reminder flag key.
*** \details Key to access still running reminder flag in configuration file.
**/
#define   PREFERENCES_STILLRUNNINGREMINDERFLAG      "StillRunningReminderFlag"

/**
*** \brief Update interval key.
*** \details Key to access update interval in configuration file.
**/
#define   PREFERENCES_UPDATEINTERVAL                "UpdateInterval"

/**
*** \brief Animation update rate.
*** \details Time between animation updates.
**/
#define   ANIMATIONTIMER_RATE     (200)           /* in milliseconds */

/**
*** \brief Icon update rate.
*** \details Time between checks for any icon updates.
**/
#define   UPDATETIMER_RATE        (60*60*1000)    /* 1 hour, in milliseconds */

/**
*** \brief Information panel update rate.
*** \details Time between checks for information panel updates.
**/
#define   INFORMATIONPANELTIMER_RATE  (1000)      /* 1 second, in milliseconds */

/**
*** \brief Binary subdirectory.
*** \details Subdirectory containing the executable.
**/
#define   DIRECTORY_BINARY  "/bin"

/**
*** \brief Image subdirectory.
*** \details Subdirectory containing the moonphase images.
**/
#define   DIRECTORY_IMAGES  "/share/"MOONPHASEQT_EXECUTABLENAME

/**
*** \brief Default animation.
*** \details Filename of the default animation.
**/
#define   FILENAME_IMAGE    "moon_56frames.png"

/**
*** \brief Read animation warning.
*** \details Displays a message box informing the user that there was an error
***   reading the moon animation file.
**/
#define   READANIMATIONWARNING(p) \
    QMessageBox::warning(p,tr(MOONPHASEQT_DISPLAYNAME), \
        tr("Unable to read moon animation file. Please select a new file."));

/**
*** \brief Information item role.
*** \details Role to use to store the information item associated with the list
***   widget item.
**/
#define   ROLE_INFORMATIONTYPE    (Qt::UserRole)

/**
*** \brief Convert QVariant into INFORMATIONITEM_C.
*** \details Retrieves a QVariant pointer from the list widget item and converts
***   it into an INFORMATIONITEM_C pointer.
**/
#define   LWI2II(lwi)   \
              (lwi)->data(ROLE_INFORMATIONTYPE).value<INFORMATIONITEM_C*>()

/**
*** \brief Number of array elements.
*** \details Returns the number of elements in an array.
**/
#define   ARRAY_ELEMENTCOUNT(a)   (sizeof(a)/sizeof(*a))

/**
*** \brief Earth radius.
*** \details The radius of the earth (in miles).
**/
#define   EARTH_RADIUS    (3959.0)


/****
*****
***** DATA TYPES
*****
****/

/**
*** \brief Change/save/load settings.
*** \details Allows changing, saving, and loading of settings.
**/
class CONTROLPANELDIALOG_C::SETTINGS_C : protected QSettings
{
  public:
    /**
    *** \brief Constructor.
    *** \details Constructor.
    **/
    SETTINGS_C(void);

    /**
    *** \brief Destructor.
    *** \details Destructor.
    **/
    ~SETTINGS_C(void);

    /**
    *** \brief Comparison operator (==).
    *** \details Comparison operator (==).
    *** \param RHS Object on right hand side of operator.
    *** \retval 0 Objects are not equivalent.
    *** \retval !0 Objects are equivalent.
    **/
    bool operator==(SETTINGS_C const &RHS) const;

    /**
    *** \brief Comparison operator (!=).
    *** \details Comparison operator (!=).
    *** \param RHS Object on right hand side of operator.
    *** \retval 0 Objects are equivalent.
    *** \retval !0 Objects are not equivalent.
    **/
    bool operator!=(SETTINGS_C const &RHS) const;

    /**
    *** \brief Load settings.
    *** \details Reads the settings from the configuration file.
    **/
    void Load(void);

    /**
    *** \brief Save settings.
    *** \details Writes the settings to the configuration file.
    **/
    void Save(void);

    /**
    *** \brief Returns the allow multiple instance flag.
    *** \details Returns the allow multiple instance flag.
    *** \retval 0 Allow only one instance.
    *** \retval !0 Allow multiple instances.
    **/
    bool GetAllowMultipleInstancesFlag(void) const;

    /**
    *** \brief Returns the animation pathname.
    *** \details Returns the pathname of the animation image.
    *** \returns Pathname of the animation image.
    **/
    QString GetAnimationPathname(void) const;

    /**
    *** \brief Returns the background color.
    *** \details Returns the color of the background.
    *** \returns Color of the background.
    **/
    QColor GetBackgroundColor(void) const;

    /**
    *** \brief Returns the confirm discard flag.
    *** \details Returns the confirm discarding of changes flag.
    *** \retval 0 Discard changes without confirming.
    *** \retval !0 Prompt for confirmation.
    **/
    bool GetConfirmDiscardFlag(void) const;

    /**
    *** \brief Returns the confirm quit flag.
    *** \details Returns the confirm quit flag.
    *** \retval 0 Quit without confirming.
    *** \retval !0 Prompt for confirmation.
    **/
    bool GetConfirmQuitFlag(void) const;

    /**
    *** \brief Returns the default to metric units flag.
    *** \details Returns the default to metric units flag.
    *** \retval 0 - Default to imperial units.
    *** \retval !0 - Default to metric units.
    **/
    bool GetDefaultToMetricUnitsFlag(void) const;

    /**
    *** \brief Returns the remind once per session flag.
    *** \details Returns the still running reminder once per session flag.
    *** \retval 0 Remind every time.
    *** \retval !0 Remind only once per session.
    **/
    bool GetRemindOncePerSessionFlag(void) const;

    /**
    *** \brief Returns the still running reminder flag.
    *** \details Returns the still running reminder flag.
    *** \retval 0 No reminder on close.
    *** \retval !0 Remind on every close.
    **/
    bool GetStillRunningReminderFlag(void) const;

    /**
    *** \brief Returns the update interval.
    *** \details Returns the interval between icon updates.
    *** \returns Interval (in hours).
    **/
    unsigned int GetUpdateInterval(void) const;

    /**
    *** \brief Returns the use opaque background flag.
    *** \details Returns the use opaque background flag.
    *** \retval 0 Draw transparent background.
    *** \retval !0 Draw background using a color.
    **/
    bool GetUseOpaqueBackgroundFlag(void) const;

    /**
    *** \brief Sets the allow multiple instances flag.
    *** \details Sets the allow multiple instances flag.
    *** \param AllowMultipleInstancesFlag 0=Allow only one instance,\n
    ***   !0=Allow multiple instances.
    **/
    void SetAllowMultipleInstancesFlag(bool AllowMultipleInstancesFlag);

    /**
    *** \brief Sets the animation pathname.
    *** \details Sets the pathname of the animation image.
    *** \param Pathname Pathname of the animation image.
    **/
    void SetAnimationPathname(QString Pathname);

    /**
    *** \brief Sets the background color.
    *** \details Sets the color of the background.
    *** \param Color Color of the background.
    **/
    void SetBackgroundColor(QColor Color);

    /**
    *** \brief Sets the confirm discard flag.
    *** \details Sets the confirm discarding of changes flag.
    *** \param ConfirmDiscardFlag 0=Discard changes without confirming,\n
    ***   !0=Prompt for confirmation.
    **/
    void SetConfirmDiscardFlag(bool ConfirmDiscardFlag);

    /**
    *** \brief Sets the confirm quit flag.
    *** \details Sets the confirm quit flag.
    *** \param ConfirmQuitFlag 0=Quit without confirming,\n
    ***   !0=Prompt for confirmation.
    **/
    void SetConfirmQuitFlag(bool ConfirmQuitFlag);

    /**
    *** \brief Sets the default to metric units flag.
    *** \details Sets the default to metric units flag.
    *** \param DefaultToMetricUnitsFlag 0=Default to imperial units,\n
    ***   !0=Default to metric units.
    **/
    void SetDefaultToMetricUnitsFlag(bool DefaultToMetricUnitsFlag);

    /**
    *** \brief Sets the remind once per session flag.
    *** \details Sets the still running reminder once per session flag.
    *** \param OnceFlag 0=Remind every time,\n!0 Remind only once per session.
    **/
    void SetRemindOncePerSessionFlag(bool OnceFlag);

    /**
    *** \brief Sets the still running reminder flag.
    *** \details Sets the still running reminder flag.
    *** \param ReminderFlag 0=No reminder on close,\n!0=Remind on every close.
    **/
    void SetStillRunningReminderFlag(bool ReminderFlag);

    /**
    *** \brief Sets the update interval.
    *** \details Sets the interval between icon updates.
    *** \param Interval Interval (in hours).
    **/
    void SetUpdateInterval(unsigned int Interval);

    /**
    *** \brief Sets the use opaque background flag.
    *** \details Sets the use opaque background flag.
    *** \param UseFlag 0=Draw transparent background,\n
    ***   !0=Draw background using a color.
    **/
    void SetUseOpaqueBackgroundFlag(bool UseFlag);

  private:
    /**
    *** \brief Sets the allow multiple instances flag.
    *** \details Sets the allow multiple instances flag.
    **/
    bool m_AllowMultipleInstancesFlag;

    /**
    *** \brief Animation pathname.
    *** \details Pathname of the animation image.
    **/
    QString m_AnimationPathname;

    /**
    *** \brief Background color.
    *** \details Color of the background.
    **/
    QColor m_BackgroundColor;

    /**
    *** \brief Confirm discard flag.
    *** \details Confirm discarding of changes flag.
    **/
    bool m_ConfirmDiscardFlag;

    /**
    *** \brief Confirm quit flag.
    *** \details Confirm quit flag.
    **/
    bool m_ConfirmQuitFlag;

    /**
    *** \brief Default to metric units flag.
    *** \details Default to metric units flag.
    **/
    bool m_DefaultToMetricUnitsFlag;

    /**
    *** \brief Remind once per session flag.
    *** \details Still running reminder once per session flag.
    **/
    bool m_RemindOncePerSessionFlag;

    /**
    *** \brief Still running reminder flag.
    *** \details Still running reminder flag.
    **/
    bool m_StillRunningReminderFlag;

    /**
    *** \brief Update interval.
    *** \details Interval between icon updates.
    **/
    unsigned int m_UpdateInterval;

    /**
    *** \brief Use opaque background flag.
    *** \details Use opaque background flag.
    **/
    bool m_UseOpaqueBackgroundFlag;
};

/**
*** \brief Unit flags.
*** \details Determines the unit type.
**/
typedef enum enumUNITFLAGS
{
  NONE=0,
  DEFAULTMETRIC=1,
  DEFAULTIMPERIAL=2,
} UNITFLAGS_F;

/**
*** \brief Unit data.
*** \details Defines various data about a measurement unit.
**/
typedef struct structUNIT
{
  /**
  *** \brief Short name.
  *** \details Short name (abbreviation) for the unit.
  **/
  QString ShortName;
  /**
  *** \brief Long name.
  *** \details Long name for the unit.
  **/
  QString LongName;
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
} UNIT_T;

/**
*** \brief Moon data item.
*** \details Defines a label, possible unit list and a print function for each
***   item in the data list.
**/
typedef struct structDATAITEM
{
  /**
  *** \brief Data label.
  *** \details Label for the displayed data.
  **/
  QString Label;
  /**
  *** \brief Unit list.
  *** \details List of units that this item can use to display.
  **/
  UNIT_T const *pUnitList;
  /**
  *** \brief Print data function.
  *** \details Function used to print the data.
  **/
  QString (*PrintDataFunction)(MOONDATA_T *pMoonData,double Scale,int Precision);
} DATAITEM_T;

/**
*** \brief Moon data and options.
*** \details Moon data and options for each line in the information panel.
**/
class INFORMATIONITEM_C
{
  public:
    /**
    *** \brief Constructor.
    *** \details Constructor.
    **/
    INFORMATIONITEM_C(void);

    /**
    *** \brief Destructor.
    *** \details Destructor.
    **/
    ~INFORMATIONITEM_C(void);

    /**
    *** \brief Return data index.
    *** \details Returns the index into the data table.
    *** \returns Index into the data table.
    **/
    int GetDataIndex(void);

    /**
    *** \brief Return item options.
    *** \details Returns the options for this item.
    *** \returns Options for this line.
    **/
    OPTIONS_C * GetOptions(void);

    /**
    *** \brief Return unit index.
    *** \details Returns the index into the unit table.
    *** \returns Index into the unit table.
    **/
    int GetUnitIndex(void);

    /**
    *** \brief Set data index.
    *** \details Sets the index into the data table.
    *** \param Index Index into the data table.
    **/
    void SetDataIndex(int Index);

    /**
    *** \brief Set item options.
    *** \details Sets the options for this item.
    *** \param Options Line Options.
    **/
    void SetOptions(OPTIONS_C const &Options);

    /**
    *** \brief Set unit index.
    *** \details Sets the index into the unit table.
    *** \param Index into the unit table.
    **/
    void SetUnitIndex(int Index);

  private:
    /**
    *** \brief Data index.
    *** \details The index into the data table.
    **/
    int m_DataIndex;

    /**
    *** \brief Item options.
    *** \details Options for this item.
    **/
    OPTIONS_C m_Options;
};

/**
*** \brief Make INFORMATIONITEM_C known to QMetaType.
*** \details Make INFORMATIONITEM_C known to QMetaType.
**/
Q_DECLARE_METATYPE(INFORMATIONITEM_C*);


/****
*****
***** PROTOTYPES
*****
****/

/**
*** \brief Test function.
*** \details Test function, will be removed.
*** \param pMoonData Param #1.
*** \param Scale Param #2.
*** \param Precision Param #3.
*** \returns Return.
**/
static QString PrintAngle0(MOONDATA_T *pMoonData,double Scale,int Precision);

/**
*** \brief Test function.
*** \details Test function, will be removed.
*** \param pMoonData Param #1.
*** \param Scale Param #2.
*** \param Precision Param #3.
*** \returns Return.
**/
static QString PrintAngle1(MOONDATA_T *pMoonData,double Scale,int Precision);

/**
*** \brief Test function.
*** \details Test function, will be removed.
*** \param pMoonData Param #1.
*** \param Scale Param #2.
*** \param Precision Param #3.
*** \returns Return.
**/
static QString PrintAngle2(MOONDATA_T *pMoonData,double Scale,int Precision);

/**
*** \brief Test function.
*** \details Test function, will be removed.
*** \param pMoonData Param #1.
*** \param Scale Param #2.
*** \param Precision Param #3.
*** \returns Return.
**/
static QString PrintDistance0(MOONDATA_T *pMoonData,double Scale,int Precision);

/**
*** \brief Test function.
*** \details Test function, will be removed.
*** \param pMoonData Param #1.
*** \param Scale Param #2.
*** \param Precision Param #3.
*** \returns Return.
**/
static QString PrintDistance1(MOONDATA_T *pMoonData,double Scale,int Precision);

/**
*** \brief Test function.
*** \details Test function, will be removed.
*** \param pMoonData Param #1.
*** \param Scale Param #2.
*** \param Precision Param #3.
*** \returns Return.
**/
static QString PrintDistance2(MOONDATA_T *pMoonData,double Scale,int Precision);


/****
*****
***** DATA
*****
****/

/**
*** \brief Angle units.
*** \details Units used by data items that are angles.
**/
static const UNIT_T f_pAngleUnits[]=
{
  { QString::fromUtf8("\u00B0"),QObject::tr("Degrees"),
      1.0,2,(UNITFLAGS_F)(DEFAULTMETRIC|DEFAULTIMPERIAL) },
  { QString::fromUtf8("\u33AD"),QObject::tr("Radians"),
      M_PI/180.0,5,NONE },
  { QString() }
};

/**
*** \brief Distance units.
*** \details Units used by data items that are distances.
**/
static const UNIT_T f_pDistanceUnits[]=
{
  { QObject::tr("m"),QObject::tr("Meters"),1609.344,0,NONE },
  { QObject::tr("'"),QObject::tr("Feet"),5280.0,0,NONE },
  { QObject::tr("km"),QObject::tr("Kilometers"),1.609344,2,DEFAULTMETRIC },
  { QObject::tr("mi"),QObject::tr("Miles"),1.0,2,DEFAULTIMPERIAL },
  { QObject::tr("au"),QObject::tr("Astronomical units"),1.0758e-8,3,NONE },
  { QString() }
};

/**
*** \brief Time units.
*** \details Units used by data items that are times.
**/
static const UNIT_T f_pTimeUnits[]=
{
  { QObject::tr("days"),QObject::tr("Days"),
      1.0,0,(UNITFLAGS_F)(DEFAULTMETRIC|DEFAULTIMPERIAL) },
  { QString() }
};

/**
*** \brief Test structure.
*** \details Test structure, will be modified.
**/
static const DATAITEM_T f_pInformation[]=
{
  { QObject::tr("Angle0"),f_pAngleUnits,PrintAngle0 },
  { QObject::tr("Angle1"),f_pAngleUnits,PrintAngle1 },
  { QObject::tr("Angle2"),f_pAngleUnits,PrintAngle2 },
  { QObject::tr("Distance0"),f_pDistanceUnits,PrintDistance0 },
  { QObject::tr("Distance1"),f_pDistanceUnits,PrintDistance1 },
  { QObject::tr("Distance2"),f_pDistanceUnits,PrintDistance2 }
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

CONTROLPANELDIALOG_C::SETTINGS_C::SETTINGS_C(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::SETTINGS_C::SETTINGS_C()");
  DEBUGLOG_LogIn();

  m_AllowMultipleInstancesFlag=false;
  m_AnimationPathname="";
  m_BackgroundColor=QColor(0,0,0);
  m_ConfirmDiscardFlag=true;
  m_ConfirmQuitFlag=true;
  m_DefaultToMetricUnitsFlag=true;
  m_RemindOncePerSessionFlag=true;
  m_StillRunningReminderFlag=true;
  m_UpdateInterval=4;
  m_UseOpaqueBackgroundFlag=false;

  DEBUGLOG_LogOut();
  return;
}

CONTROLPANELDIALOG_C::SETTINGS_C::~SETTINGS_C(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::SETTINGS_C::~SETTINGS_C()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return;
}

bool CONTROLPANELDIALOG_C::SETTINGS_C::operator==(SETTINGS_C const &RHS) const
{
  bool EqualFlag;


  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::SETTINGS_C::operator==(%p)",&RHS);
  DEBUGLOG_LogIn();

  EqualFlag=(QString::localeAwareCompare(
      m_AnimationPathname,RHS.m_AnimationPathname)==0) &&
      (m_AllowMultipleInstancesFlag==RHS.m_AllowMultipleInstancesFlag) &&
      (m_BackgroundColor==RHS.m_BackgroundColor) &&
      (m_ConfirmDiscardFlag==RHS.m_ConfirmDiscardFlag) &&
      (m_ConfirmQuitFlag==RHS.m_ConfirmQuitFlag) &&
      (m_DefaultToMetricUnitsFlag==RHS.m_DefaultToMetricUnitsFlag) &&
      (m_RemindOncePerSessionFlag==RHS.m_RemindOncePerSessionFlag) &&
      (m_StillRunningReminderFlag==RHS.m_StillRunningReminderFlag) &&
      (m_UpdateInterval==RHS.m_UpdateInterval) &&
      (m_UseOpaqueBackgroundFlag==RHS.m_UseOpaqueBackgroundFlag);

  DEBUGLOG_LogOut();
  return(EqualFlag);
}

bool CONTROLPANELDIALOG_C::SETTINGS_C::operator!=(SETTINGS_C const &RHS) const
{
  bool EqualFlag;


  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::SETTINGS_C::operator==(%p)",&RHS);
  DEBUGLOG_LogIn();

  EqualFlag=!((*this)==RHS);

  DEBUGLOG_LogOut();
  return(EqualFlag);
}

void CONTROLPANELDIALOG_C::SETTINGS_C::Load(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::SETTINGS_C::Load()");
  DEBUGLOG_LogIn();

  m_AllowMultipleInstancesFlag=
      value(PREFERENCES_ALLOWMULTIPLEINSTANCESFLAG,m_AllowMultipleInstancesFlag)
      .toBool();
  m_AnimationPathname=
      value(PREFERENCES_ANIMATIONPATHNAME,m_AnimationPathname).toString();
  m_BackgroundColor=
      value(PREFERENCES_BACKGROUNDCOLOR,m_BackgroundColor).value<QColor>();
  m_ConfirmDiscardFlag=value(
      PREFERENCES_CONFIRMDISCARDCHANGESFLAG,m_ConfirmDiscardFlag).toBool();
  m_ConfirmQuitFlag=
      value(PREFERENCES_CONFIRMQUITFLAG,m_ConfirmQuitFlag).toBool();
  m_DefaultToMetricUnitsFlag=
      value(PREFERENCES_DEFAULTTOMETRICUNITSFLAG,m_DefaultToMetricUnitsFlag).toBool();
  m_UseOpaqueBackgroundFlag=value(PREFERENCES_USEOPAQUEBACKGROUNDFLAG,
      m_UseOpaqueBackgroundFlag).toBool();
  m_RemindOncePerSessionFlag=value(PREFERENCES_REMINDONCEPERSESSIONFLAG,
      m_RemindOncePerSessionFlag).toBool();
  m_StillRunningReminderFlag=value(
      PREFERENCES_STILLRUNNINGREMINDERFLAG,m_StillRunningReminderFlag).toBool();
  m_UpdateInterval=value(PREFERENCES_UPDATEINTERVAL,m_UpdateInterval).toUInt();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::SETTINGS_C::Save(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::SETTINGS_C::Save()");
  DEBUGLOG_LogIn();

  setValue(PREFERENCES_ALLOWMULTIPLEINSTANCESFLAG,m_AllowMultipleInstancesFlag);
  setValue(PREFERENCES_ANIMATIONPATHNAME,m_AnimationPathname);
  setValue(PREFERENCES_BACKGROUNDCOLOR,m_BackgroundColor);
  setValue(PREFERENCES_CONFIRMDISCARDCHANGESFLAG,m_ConfirmDiscardFlag);
  setValue(PREFERENCES_CONFIRMQUITFLAG,m_ConfirmQuitFlag);
  setValue(PREFERENCES_DEFAULTTOMETRICUNITSFLAG,m_DefaultToMetricUnitsFlag);
  setValue(PREFERENCES_USEOPAQUEBACKGROUNDFLAG,m_UseOpaqueBackgroundFlag);
  setValue(PREFERENCES_REMINDONCEPERSESSIONFLAG,m_RemindOncePerSessionFlag);
  setValue(PREFERENCES_STILLRUNNINGREMINDERFLAG,m_StillRunningReminderFlag);
  setValue(PREFERENCES_UPDATEINTERVAL,m_UpdateInterval);

  DEBUGLOG_LogOut();
  return;
}

bool CONTROLPANELDIALOG_C::SETTINGS_C::GetAllowMultipleInstancesFlag(void) const
{
  DEBUGLOG_Printf0(
      "CONTROLPANELDIALOG_C::SETTINGS_C::GetAllowMultipleInstancesFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_AllowMultipleInstancesFlag);
}

QString CONTROLPANELDIALOG_C::SETTINGS_C::GetAnimationPathname(void) const
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::SETTINGS_C::GetAnimationPathname()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_AnimationPathname);
}

QColor CONTROLPANELDIALOG_C::SETTINGS_C::GetBackgroundColor(void) const
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::SETTINGS_C::GetBackgroundColor()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_BackgroundColor);
}

bool CONTROLPANELDIALOG_C::SETTINGS_C::GetConfirmDiscardFlag(void) const
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::SETTINGS_C::GetConfirmDiscardFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_ConfirmDiscardFlag);
}

bool CONTROLPANELDIALOG_C::SETTINGS_C::GetConfirmQuitFlag(void) const
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::SETTINGS_C::GetConfirmQuitFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_ConfirmQuitFlag);
}

bool CONTROLPANELDIALOG_C::SETTINGS_C::GetDefaultToMetricUnitsFlag(void) const
{
  DEBUGLOG_Printf0(
      "CONTROLPANELDIALOG_C::SETTINGS_C::GetDefaultToMetricUnitsFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_DefaultToMetricUnitsFlag);
}

bool CONTROLPANELDIALOG_C::SETTINGS_C::GetRemindOncePerSessionFlag(void) const
{
  DEBUGLOG_Printf0(
      "CONTROLPANELDIALOG_C::SETTINGS_C::GetRemindOncePerSessionFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_RemindOncePerSessionFlag);
}

bool CONTROLPANELDIALOG_C::SETTINGS_C::GetStillRunningReminderFlag(void) const
{
  DEBUGLOG_Printf0(
      "CONTROLPANELDIALOG_C::SETTINGS_C::GetStillRunningReminderFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_StillRunningReminderFlag);
}

unsigned int CONTROLPANELDIALOG_C::SETTINGS_C::GetUpdateInterval(void) const
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::SETTINGS_C::GetUpdateInterval()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_UpdateInterval);
}

bool CONTROLPANELDIALOG_C::SETTINGS_C::GetUseOpaqueBackgroundFlag(void) const
{
  DEBUGLOG_Printf0(
      "CONTROLPANELDIALOG_C::SETTINGS_C::GetUseOpaqueBackgroundFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_UseOpaqueBackgroundFlag);
}

void CONTROLPANELDIALOG_C::SETTINGS_C::
    SetAllowMultipleInstancesFlag(bool const AllowMultipleInstancesFlag)
{
  DEBUGLOG_Printf1(
      "CONTROLPANELDIALOG_C::SETTINGS_C::SetAllowMultipleInstancesFlag(%u)",
      AllowMultipleInstancesFlag);
  DEBUGLOG_LogIn();

  m_AllowMultipleInstancesFlag=AllowMultipleInstancesFlag;

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::SETTINGS_C::
    SetAnimationPathname(QString const Pathname)
{
  DEBUGLOG_Printf2(
      "CONTROLPANELDIALOG_C::SETTINGS_C::SetAnimationPathname(%p(%s))",
      &Pathname,qPrintable(Pathname));
  DEBUGLOG_LogIn();

  m_AnimationPathname=Pathname;

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::SETTINGS_C::
    SetBackgroundColor(QColor const BackgroundColor)
{
  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::SETTINGS_C::SetBackgroundColor(%u)",
      BackgroundColor.value());
  DEBUGLOG_LogIn();

  m_BackgroundColor=BackgroundColor;

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::SETTINGS_C::
    SetConfirmDiscardFlag(bool const ConfirmDiscardFlag)
{
  DEBUGLOG_Printf1(
      "CONTROLPANELDIALOG_C::SETTINGS_C::SetConfirmDiscardFlag(%u)",
      ConfirmDiscardFlag);
  DEBUGLOG_LogIn();

  m_ConfirmDiscardFlag=ConfirmDiscardFlag;

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::SETTINGS_C::
    SetConfirmQuitFlag(bool const ConfirmQuitFlag)
{
  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::SETTINGS_C::SetConfirmQuitFlag(%u)",
      ConfirmQuitFlag);
  DEBUGLOG_LogIn();

  m_ConfirmQuitFlag=ConfirmQuitFlag;

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::SETTINGS_C::
    SetDefaultToMetricUnitsFlag(bool const DefaultToMetricUnitsFlag)
{
  DEBUGLOG_Printf1(
      "CONTROLPANELDIALOG_C::SETTINGS_C::SetDefaultToMetricUnitsFlag(%u)",
      DefaultToMetricUnitsFlag);
  DEBUGLOG_LogIn();

  m_DefaultToMetricUnitsFlag=DefaultToMetricUnitsFlag;

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::SETTINGS_C::
    SetRemindOncePerSessionFlag(bool const OnceFlag)
{
  DEBUGLOG_Printf1(
      "CONTROLPANELDIALOG_C::SETTINGS_C::SetRemindOncePerSessionFlag(%u)",
      OnceFlag);
  DEBUGLOG_LogIn();

  m_RemindOncePerSessionFlag=OnceFlag;

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::SETTINGS_C::
    SetStillRunningReminderFlag(bool const ReminderFlag)
{
  DEBUGLOG_Printf1(
      "CONTROLPANELDIALOG_C::SETTINGS_C::SetStillRunningReminderFlag(%u)",
      ReminderFlag);
  DEBUGLOG_LogIn();

  m_StillRunningReminderFlag=ReminderFlag;

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::SETTINGS_C::
    SetUpdateInterval(unsigned int const Interval)
{
  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::SETTINGS_C::SetUpdateInterval(%u)",
      Interval);
  DEBUGLOG_LogIn();

  m_UpdateInterval=Interval;

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::SETTINGS_C::
    SetUseOpaqueBackgroundFlag(bool const UseFlag)
{
  DEBUGLOG_Printf1(
      "CONTROLPANELDIALOG_C::SETTINGS_C::SetUseOpaqueBackgroundFlag(%u)",
      UseFlag);
  DEBUGLOG_LogIn();

  m_UseOpaqueBackgroundFlag=UseFlag;

  DEBUGLOG_LogOut();
  return;
}

INFORMATIONITEM_C::INFORMATIONITEM_C(void)
{
  DEBUGLOG_Printf0("INFORMATIONITEM_C::INFORMATIONITEM_C()");
  DEBUGLOG_LogIn();

  m_DataIndex=0;

  DEBUGLOG_LogOut();
  return;
}

INFORMATIONITEM_C::~INFORMATIONITEM_C(void)
{
  DEBUGLOG_Printf0("INFORMATIONITEM_C::~INFORMATIONITEM_C()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return;
}

int INFORMATIONITEM_C::GetDataIndex(void)
{
  DEBUGLOG_Printf0("INFORMATIONITEM_C::GetDataIndex()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_DataIndex);
}

OPTIONS_C * INFORMATIONITEM_C::GetOptions(void)
{
  OPTIONS_C *pOptions;


  DEBUGLOG_Printf0("INFORMATIONITEM_C::GetOptions()");
  DEBUGLOG_LogIn();

  pOptions=new OPTIONS_C(m_Options);

  DEBUGLOG_LogOut();
  return(pOptions);
}

int INFORMATIONITEM_C::GetUnitIndex(void)
{
  DEBUGLOG_Printf0("INFORMATIONITEM_C::GetUnitIndex()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_Options.GetUnitIndex());
}

void INFORMATIONITEM_C::SetDataIndex(int Index)
{
  DEBUGLOG_Printf1("INFORMATIONITEM_C::SetDataIndex(%d)",Index);
  DEBUGLOG_LogIn();

  m_DataIndex=Index;

  DEBUGLOG_LogOut();
  return;
}

void INFORMATIONITEM_C::SetOptions(OPTIONS_C const &Options)
{
  DEBUGLOG_Printf1("INFORMATIONITEM_C::SetOptions(%p)",&Options);
  DEBUGLOG_LogIn();

  m_Options=Options;

  DEBUGLOG_LogOut();
  return;
}

void INFORMATIONITEM_C::SetUnitIndex(int Index)
{
  DEBUGLOG_Printf1("INFORMATIONITEM_C::SetUnitIndex(%d)",Index);
  DEBUGLOG_LogIn();

  m_Options.SetUnitIndex(Index);

  DEBUGLOG_LogOut();
  return;
}

#ifdef    DEBUG
TESTWIDGET_C::TESTWIDGET_C(QWidget *pParent) : QWidget(pParent)
{
  DEBUGLOG_Printf1("TESTWIDGET_C::TESTWIDGET_C(%p)",pParent);
  DEBUGLOG_LogIn();

  /* Set up the user interface. */
  setupUi(this);

  DEBUGLOG_LogOut();
  return;
}

TESTWIDGET_C::~TESTWIDGET_C(void)
{
  DEBUGLOG_Printf0("TESTWIDGET_C::~TESTWIDGET_C()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return;
}
#endif    /* DEBUG */

CONTROLPANELDIALOG_C::CONTROLPANELDIALOG_C(QWidget *pParent) : QDialog(pParent)
{
  ERRORCODE_T ErrorCode;
  QString BaseDirectory;
  QFileInfo FileInfo;
  bool FoundFlag;


  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::CONTROLPANELDIALOG_C(%p)",pParent);
  DEBUGLOG_LogIn();

  m_pTrayIconMenu=NULL;
  m_pTrayIcon=NULL;
  m_pInformationPanelDialog=NULL;
  m_pAnimationTimer=NULL;
  m_pUpdateTimer=NULL;
  m_pInformationPanelTimer=NULL;
  m_pSettings=NULL;
  m_pNetworkAccess=NULL;
  m_PreviewPercentCounter=0;
  m_UpdateIntervalCounter=0;
  m_CloseReminderIssued=false;
  m_StartUpFlag=true;
  m_FirstUpdateFlag=true;
  m_NextUpdateCheck=QDate::currentDate();


  /* Set up the user interface. */
  setupUi(this);

  /* Set window title. */
  setWindowTitle(windowTitle()+tr(" - ")+tr(MOONPHASEQT_DISPLAYNAME));

  /* Add minimize button. */
  setWindowFlags(Qt::Window);

  /* Because of above call, window starts in odd places. Center it instead. */
  move(QPoint(
    (QApplication::desktop()->width()-frameGeometry().width())/2,
    (QApplication::desktop()->height()-frameGeometry().height())/2));

  /* Disable help (temporarily). */
  m_pButtonBox->button(QDialogButtonBox::Help)->setEnabled(false);

  /* Create and set up the tray icon context menu. */
  m_pTrayIconMenu=new QMenu(this);
  m_pTrayIconMenu->addAction(m_pShowControlPanelAction);
  m_pTrayIconMenu->addSeparator();
  m_pTrayIconMenu->addAction(m_pShowInformationPanelAction);
  m_pTrayIconMenu->addSeparator();
  m_pTrayIconMenu->addAction(m_pQuitAction);

  /* Create and set up the tray icon. */
  m_pTrayIcon=new QSystemTrayIcon(this);
  m_pTrayIcon->setContextMenu(m_pTrayIconMenu);
  connect(m_pTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
      this,SLOT(ControlPanelActivatedSlot(QSystemTrayIcon::ActivationReason)));

  /* Connect the quit action to the quit slot. */
  connect(m_pQuitAction,SIGNAL(triggered()),this,SLOT(QuitSlot()));

  /* Create the information panel dialog. */
  m_pInformationPanelDialog=new INFORMATIONPANELDIALOG_C(this);

  /* Create the settings. */
  m_pSettings=new SETTINGS_C();

  /* Create, set up, and start the update timer. */
  m_pUpdateTimer=new QTimer(this);
  connect(m_pUpdateTimer,SIGNAL(timeout()),
      this,SLOT(UpdateTimerTriggeredSlot()));
  m_pUpdateTimer->start(UPDATETIMER_RATE);

  /* Create and set up the animation timer. */
  m_pAnimationTimer=new QTimer(this);
  connect(m_pAnimationTimer,SIGNAL(timeout()),
      this,SLOT(AnimationTimerTriggeredSlot()));

  /* Create and set up the information panel timer. */
  m_pInformationPanelTimer=new QTimer(this);
  connect(m_pInformationPanelTimer,SIGNAL(timeout()),
      this,SLOT(InformationPanelTimerTriggeredSlot()));

  m_pNetworkAccess=new QNetworkAccessManager;
  connect(m_pNetworkAccess,SIGNAL(finished(QNetworkReply*)),
      this,SLOT(CurrentVersionDownloadCompleteSlot(QNetworkReply*)));

  /* Initialize member variables. */
  ErrorCode=MoonData_Initialize(&m_MoonData);
  MESSAGELOG_LogError(ErrorCode);
  if (ErrorCode>0)
  {
    ErrorCode=MoonAnimation_Initialize(&m_MoonTrayImages);
    MESSAGELOG_LogError(ErrorCode);
    if (ErrorCode>0)
    {
      ErrorCode=MoonAnimation_Initialize(&m_MoonPreviewImages);
      MESSAGELOG_LogError(ErrorCode);
      if (ErrorCode<0)
        MoonAnimation_Uninitialize(&m_MoonTrayImages);
    }
    if (ErrorCode<0)
      MoonData_Uninitialize(&m_MoonData);
  }
  if (ErrorCode<0)
    throw(ErrorCode);

  /* Read configuration. */
  m_pSettings->Load();

  /* The animation pathname hasn't been set. Let's try to find the default. */
  if (m_pSettings->GetAnimationPathname()=="")
  {
    /* Under Unix, the executable is in a base directory + "/bin".
        Under Windows, the executable is in the base directory. */
    BaseDirectory=QCoreApplication::applicationDirPath();

    /* Strip off any "/bin". */
    if (BaseDirectory.endsWith(DIRECTORY_BINARY,Qt::CaseInsensitive)==true)
      BaseDirectory.chop(strlen(DIRECTORY_BINARY));

    /* Check the base directory. Should work on Windows, not Unix. */
    FoundFlag=0;
    FileInfo.setFile(BaseDirectory,FILENAME_IMAGE);
    FoundFlag=FileInfo.exists();
    if (FoundFlag==false)
    {
      /* Check the "images" directory. Should work on Unix, not Windows. */
      FileInfo.setFile(BaseDirectory+QString(DIRECTORY_IMAGES),FILENAME_IMAGE);
      FoundFlag=FileInfo.exists();
    }

    /* Found something, set it. */
    if (FoundFlag==true)
      m_pSettings->SetAnimationPathname(FileInfo.filePath());

    /* Save the defaults to the config file. */
    m_pSettings->Save();
  }

  /* Initialize tabs. */
  InitializePreferencesTab();   // Preview animation loaded here.
  InitializeAboutTab();
  CreateAndInitializeTestTab();

  /* Attempt to load the animation. */
  ErrorCode=MoonAnimation_ReadFile(
      &m_MoonTrayImages,qPrintable(m_pSettings->GetAnimationPathname()));
  MESSAGELOG_LogError(ErrorCode);

  ForceUpdate();
  SetVisible(ErrorCode<0);

  /* Force Apply button to update. */
  PreferencesChangedSlot();

  /* Show the tray icon. */
  m_pTrayIcon->show();

  /* Any error here is because of an invalid animation file. Show the control
      panel, and display a messsage. */
  if (ErrorCode<0)
  {
    ControlPanelActivatedSlot(QSystemTrayIcon::DoubleClick);
    READANIMATIONWARNING(this);
    ErrorCode=ERRORCODE_SUCCESS;  /* "Error" handled. */
  }

  /* Populate the information list widget. */
  for(unsigned int Index=0;Index<ARRAY_ELEMENTCOUNT(f_pInformation);Index++)
    m_pDataListWidget->addItem(f_pInformation[Index].Label);

  /* Resize the control panel to minimum size. */
  resize(minimumSizeHint());

  m_StartUpFlag=false;

  /* TEMP */
  m_MoonData.CTransData.Glat=33.817485;
  m_pLatitudeSpinBox->setValue(m_MoonData.CTransData.Glat);
  m_MoonData.CTransData.Glon=-118.348914;
  m_pLongitudeSpinBox->setValue(m_MoonData.CTransData.Glon);
  /* TEMP */

  DEBUGLOG_LogOut();
  return;
}

CONTROLPANELDIALOG_C::~CONTROLPANELDIALOG_C(void)
{
  ERRORCODE_T ErrorCode;
#ifndef   ENABLE_MESSAGELOG
  Q_UNUSED(ErrorCode);
#endif    /* ENABLE_MESSAGELOG */


  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::~CONTROLPANELDIALOG_C()");
  DEBUGLOG_LogIn();

  if (m_pNetworkAccess==NULL)
  {
    MESSAGELOG_Warning("m_pNetworkAccess==NULL");
  }
  delete m_pNetworkAccess;
  if (m_pSettings==NULL)
  {
    MESSAGELOG_Warning("m_pSettings==NULL");
  }
  delete m_pSettings;
  if (m_pAnimationTimer==NULL)
  {
    MESSAGELOG_Warning("m_pAnimationTimer==NULL");
  }
  delete m_pAnimationTimer;
  if (m_pUpdateTimer==NULL)
  {
    MESSAGELOG_Warning("m_pUpdateTimer==NULL");
  }
  delete m_pUpdateTimer;
  if (m_pTrayIcon==NULL)
  {
    MESSAGELOG_Warning("m_pTrayIcon==NULL");
  }
  delete m_pTrayIcon;
  if (m_pTrayIconMenu==NULL)
  {
    MESSAGELOG_Warning("m_pTrayIconMenu==NULL");
  }
  delete m_pTrayIconMenu;
  ErrorCode=MoonAnimation_Uninitialize(&m_MoonPreviewImages);
  MESSAGELOG_LogError(ErrorCode);
  ErrorCode=MoonAnimation_Uninitialize(&m_MoonTrayImages);
  MESSAGELOG_LogError(ErrorCode);
  ErrorCode=MoonData_Uninitialize(&m_MoonData);
  MESSAGELOG_LogError(ErrorCode);

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::CheckSavePreferences(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::CheckSavePreferences()");
  DEBUGLOG_LogIn();

  /* If the Apply button is enabled, there are changes to the preferences. */
  if ( (m_pButtonBox->button(QDialogButtonBox::Apply)->isEnabled()==true) &&
      (m_pSettings->GetConfirmDiscardFlag()==true) )
  {
    if (QMessageBox::question(this,MOONPHASEQT_DISPLAYNAME,
        tr("Your preferences have changed. Do you want to save them?"),
        QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes)==QMessageBox::Yes)
    {
      /* Fake an Apply button click. */
      ButtonBoxButtonClickedSlot(m_pButtonBox->button(QDialogButtonBox::Apply));
    }
  }

  /* Whether saved or discarded, reload them from the configuration file. */
  LoadSettings();
  PreferencesChangedSlot();   // Force a dialog update.

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::closeEvent(QCloseEvent *pEvent)
{
  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::closeEvent(%p)",pEvent);
  DEBUGLOG_LogIn();

  /* Check if preferences have been changed.
      If so, ask if user wants to save them, and if yes, save them. */
  CheckSavePreferences();

  /* DialogVisible && ReminderFlag && (!OnceFlag || (OnceFlag && !First)) */
  if ( (isVisible()==true) &&
      (m_pSettings->GetStillRunningReminderFlag()==true) &&
      ((m_pSettings->GetRemindOncePerSessionFlag()==false) ||
      ((m_pSettings->GetRemindOncePerSessionFlag()==true) &&
      (m_CloseReminderIssued==false))) )
  {
    QMessageBox::information(this,MOONPHASEQT_DISPLAYNAME,
        tr("This program will continue to run in the system tray. To stop it, "
        "right click the system tray icon and select <b>Quit</b>."));
    if (m_pSettings->GetRemindOncePerSessionFlag()==true)
      m_CloseReminderIssued=true;
  }
  SetVisible(false);
  pEvent->ignore();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::CreateAndInitializeTestTab(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::CreateAndInitializeTestTab()");
  DEBUGLOG_LogIn();

#ifdef    DEBUG
  m_pTestWidget=new TESTWIDGET_C(this);
  m_pTabWidget->addTab(m_pTestWidget,QIcon(":/WidgetIcons/TestIcon"),"&Test");
  m_pTestWidget->m_pDateTimeEdit->setDateTime(QDateTime::currentDateTime());
  connect(m_pTestWidget->m_pDateTimeEdit,SIGNAL(dateTimeChanged(QDateTime)),
      this,SLOT(DateTimeChanged(QDateTime)));
#endif    /* DEBUG */

  DEBUGLOG_LogOut();
  return;
}

QPixmap CONTROLPANELDIALOG_C::DrawFrame(MOONANIMATION_T *pMoonAnimation,
    unsigned int Percent,bool UseBackgroundColorFlag,QColor BackgroundColor)
{
  ERRORCODE_T ErrorCode;
  unsigned int Index;
  unsigned int FrameCount;
  QPixmap const *pConstPixmap;
  QPixmap Pixmap;


  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::GetFrame(%u)",Percent);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pMoonAnimation==NULL)
  {
    ErrorCode=ERRORCODE_NULLPARAMETER;
    MESSAGELOG_LogError(ErrorCode);
  }
  else if (Percent>100)
  {
    ErrorCode=ERRORCODE_INVALIDPARAMETER;
    MESSAGELOG_LogError(ErrorCode);
  }
  else
  {
    ErrorCode=MoonAnimation_GetFrameCount(pMoonAnimation);
    MESSAGELOG_LogError(ErrorCode);
    if (ErrorCode>0)
    {
      /* ErrorCode has a frame count > 0. */
      FrameCount=ErrorCode;
      Index=(((Percent/100.001)*FrameCount)+.5);
      if (Index>=FrameCount)
        Index-=FrameCount;
      ErrorCode=MoonAnimation_GetFrame(pMoonAnimation,Index,&pConstPixmap);
      MESSAGELOG_LogError(ErrorCode);
      if (ErrorCode>0)
        Pixmap=*pConstPixmap;
    }
  }
  if (ErrorCode<=0)
  {
    Pixmap.load(":/ErrorIcon");
    ErrorCode=ERRORCODE_SUCCESS;
  }
  if (UseBackgroundColorFlag==true)
  {
    QImage Background(Pixmap.width(),Pixmap.height(),QImage::Format_ARGB32);
    Background.fill(BackgroundColor);
    QPainter Painter(&Background);
    Painter.drawPixmap(0,0,Pixmap);
    Painter.end();
    Pixmap=QPixmap::fromImage(Background);
  }

  DEBUGLOG_LogOut();
  return(Pixmap);
}

void CONTROLPANELDIALOG_C::ForceUpdate(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::ForceUpdate()");
  DEBUGLOG_LogIn();

  m_UpdateIntervalCounter=UINT_MAX-1;
  UpdateTimerTriggeredSlot();

  DEBUGLOG_LogOut();
  return;
}

bool CONTROLPANELDIALOG_C::GetAllowMultipleInstancesFlag(void)
{
  SETTINGS_C Settings;


  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::GetAllowMultipleInstancesFlag()");
  DEBUGLOG_LogIn();

  /* Always read from the config file. */
  Settings.Load();

  DEBUGLOG_LogOut();
  return(Settings.GetAllowMultipleInstancesFlag());
}

void CONTROLPANELDIALOG_C::InitializeAboutTab(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::InitializeAboutTab()");
  DEBUGLOG_LogIn();

  /* Set the data in the various widgets. */
  m_pProgramNameLabel->setText(MOONPHASEQT_DISPLAYNAME);
  m_pExecutableNameVersionLabel->setText(MOONPHASEQT_EXECUTABLENAME
      " (Version "MOONPHASEQT_VERSION")");
  m_pProgramInformationEdit->setText(MOONPHASEQT_DESCRIPTION"\n");
  m_pProgramInformationEdit->append(MOONPHASEQT_COPYRIGHTNOTICE"\n");
#ifdef    _WIN32
  {
    QString Buffer;

    Buffer=QString(tr("Statically linked with Qt (Version "))
        +qVersion()+QString(tr(")\n"));
    m_pProgramInformationEdit->append(Buffer);
  }
#endif    /* _WIN32 */
  m_pProgramInformationEdit->append("<a href=\""MOONPHASEQT_WEBSITE"\">"
      MOONPHASEQT_DISPLAYNAME" Web Site</a>\n");

  m_pLicenseAgreementEdit->setPlainText(f_pLicenseAgreement);

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::InitializePreferencesTab(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::InitializePreferencesTab()");
  DEBUGLOG_LogIn();

  LoadSettings();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::LoadSettings(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::LoadSettings()");
  DEBUGLOG_LogIn();

  /* Load from the config file. */
  m_pSettings->Load();

  /* Set the widget data. */
  m_pUpdateIntervalSpinBox->setValue(m_pSettings->GetUpdateInterval());
  m_pAnimationFilenameChooser->setText(m_pSettings->GetAnimationPathname());
  m_pUseOpaqueBackgroundGroupBox->setChecked(
      m_pSettings->GetUseOpaqueBackgroundFlag());
  m_pBackgroundColorButton->setCurrentColor(m_pSettings->GetBackgroundColor());
  m_pStillRunningReminder->setChecked(
      m_pSettings->GetStillRunningReminderFlag());
  m_pRemindOncePerSessionCheckBox->setChecked(
      m_pSettings->GetRemindOncePerSessionFlag());
  m_pConfirmDiscardCheckBox->setChecked(m_pSettings->GetConfirmDiscardFlag());
  m_pConfirmQuitCheckBox->setChecked(m_pSettings->GetConfirmQuitFlag());
  m_pMetricUnitsRadioButton->setChecked(m_pSettings->GetDefaultToMetricUnitsFlag());
  m_pImperialUnitsRadioButton->setChecked(!m_pSettings->GetDefaultToMetricUnitsFlag());
  m_pAllowMultipleInstancesCheckBox->setChecked(
      m_pSettings->GetAllowMultipleInstancesFlag());

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::MoveItem(int Direction)
{
  QListWidgetItem *pSelectedItem;
  int Row;
  QListWidgetItem *pItem;


  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::MoveItem(%d)",Direction);
  DEBUGLOG_LogIn();

  /* Check the direction. */
  if ( (Direction!=1) && (Direction!=-1) )
  {
    MESSAGELOG_Error("Invalid parameter.");
  }
  else
  {
    /* Get the current item. */
    pSelectedItem=m_pDisplayListWidget->selectedItems()[0];
    if (pSelectedItem==NULL)
    {
      MESSAGELOG_Error("NULL selected item pointer.");
    }
    else
    {
      /* Extract it, then re-insert it using the delta. */
      Row=m_pDisplayListWidget->row(pSelectedItem);
      pItem=m_pDisplayListWidget->takeItem(Row);
      if (pItem==NULL)
      {
        MESSAGELOG_Error("NULL item pointer.");
      }
      else
      {
        m_pDisplayListWidget->insertItem(Row+Direction,pItem);
        m_pDisplayListWidget->setCurrentItem(pItem);
      }

      /* Update the display. */
      InformationPanelTimerTriggeredSlot();
      UpdateControls();
    }
  }

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::ReadPreferences(SETTINGS_C *pSettings)
{
  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::ReadPreferences(%p)",pSettings);
  DEBUGLOG_LogIn();

  /* Get the widget data. */
  pSettings->SetUpdateInterval(m_pUpdateIntervalSpinBox->value());
  pSettings->SetAnimationPathname(m_pAnimationFilenameChooser->text());
  pSettings->SetUseOpaqueBackgroundFlag(
      m_pUseOpaqueBackgroundGroupBox->isChecked());
  pSettings->SetBackgroundColor(m_pBackgroundColorButton->currentColor());
  pSettings->SetStillRunningReminderFlag(m_pStillRunningReminder->isChecked());
  pSettings->SetRemindOncePerSessionFlag(
      m_pRemindOncePerSessionCheckBox->isChecked());
  pSettings->SetConfirmDiscardFlag(m_pConfirmDiscardCheckBox->isChecked());
  pSettings->SetConfirmQuitFlag(m_pConfirmQuitCheckBox->isChecked());
  pSettings->SetDefaultToMetricUnitsFlag(m_pMetricUnitsRadioButton->isChecked());
  pSettings->SetAllowMultipleInstancesFlag(
      m_pAllowMultipleInstancesCheckBox->isChecked());

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::RecalculateMoonData(time_t Time)
{
  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::RecalculateMoonData(%1)",time);
  DEBUGLOG_LogIn();

  /* Recalculate the astronomical data. */
  MoonData_Recalculate(&m_MoonData,Time);

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::SaveSettings(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::SaveSettings()");
  DEBUGLOG_LogIn();

  /* Read the widgets. */
  ReadPreferences(m_pSettings);

  /* Save to the config file. */
  m_pSettings->Save();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::SetVisible(bool VisibleFlag)
{
  bool IsVisibleFlag;


  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::SetVisible(%u)",VisibleFlag);
  DEBUGLOG_LogIn();

  IsVisibleFlag=isVisible();
  QDialog::setVisible(VisibleFlag);
  if (VisibleFlag==true)
  {
    /* Don't reset counter or start timer if the dialog is already visible. */
    if (IsVisibleFlag==false)
    {
      m_PreviewPercentCounter=0;
      m_pAnimationTimer->start(ANIMATIONTIMER_RATE);
    }
    else
    {
      raise();
      activateWindow();
    }
  }
  else
    m_pAnimationTimer->stop();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::UpdateControls(void)
{
  bool EnableAddFlag;
  bool EnableRemoveFlag;
  bool EnableUpFlag;
  bool EnableDownFlag;
  bool EnableOptionsFlag;
  QListWidgetItem *pLWItem;
  INFORMATIONITEM_C *pIItem;


  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::UpdateControls()");
  DEBUGLOG_LogIn();

  EnableAddFlag=false;
  EnableRemoveFlag=false;
  EnableUpFlag=false;
  EnableDownFlag=false;
  EnableOptionsFlag=false;

  if (m_pDataListWidget->selectedItems().count()!=0)
    EnableAddFlag=true;

  if (m_pDisplayListWidget->selectedItems().count()!=0)
    EnableRemoveFlag=true;

  if (m_pDisplayListWidget->selectedItems().count()!=0)
  {
    pLWItem=m_pDisplayListWidget->selectedItems()[0];
    if (pLWItem==NULL)
    {
      MESSAGELOG_Error("NULL selected item pointer.");
    }
    else
    {
      if (m_pDisplayListWidget->row(pLWItem)!=0)
        EnableUpFlag=true;

      if ((m_pDisplayListWidget->row(pLWItem)+1)!=
            m_pDisplayListWidget->count())
        EnableDownFlag=true;

      if (m_pDisplayListWidget->selectedItems().count()!=0)
      {
        pIItem=LWI2II(pLWItem);
        if (pIItem==NULL)
        {
          MESSAGELOG_Error("NULL information item pointer.");
        }
        else if (f_pInformation[pIItem->GetDataIndex()].pUnitList[0].ShortName
            !=QString())
        EnableOptionsFlag=true;
      }
    }
  }

  m_pAddDisplayItemToolButton->setEnabled(EnableAddFlag);
  m_pRemoveDisplayItemToolButton->setEnabled(EnableRemoveFlag);
  m_pMoveUpDisplayItemToolButton->setEnabled(EnableUpFlag);
  m_pMoveDownDisplayItemToolButton->setEnabled(EnableDownFlag);
  m_pOptionsDisplayItemToolButton->setEnabled(EnableOptionsFlag);

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::AddDataItemButtonClickedSlot(void)
{
  QListWidgetItem *pSelectedItem;
  INFORMATIONITEM_C *pIItem;
  int SelectedIndex;
  QListWidgetItem *pLWItem;
  UNITFLAGS_F DefaultUnit;
  int UnitIndex;
  UNIT_T const *pUnitList;


  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::AddDataItemButtonClickedSlot()");
  DEBUGLOG_LogIn();

  foreach(pSelectedItem,m_pDataListWidget->selectedItems())
  {
    /* Add a row at the end of the display list widget. */
    SelectedIndex=m_pDataListWidget->row(pSelectedItem);
    m_pDisplayListWidget->addItem(f_pInformation[SelectedIndex].Label);

    /* Get the new list widget item. */
    pLWItem=m_pDisplayListWidget->item(m_pDisplayListWidget->count()-1);
    if (pLWItem==NULL)
    {
      MESSAGELOG_Error("NULL list widget item pointer.");
    }
    else
    {
      /* Create a new information item. */
      pIItem=new INFORMATIONITEM_C;

      /* Save the information item in the list widget item data. */
      pLWItem->setData(ROLE_INFORMATIONTYPE,QVariant::fromValue(pIItem));

      /* The index into the information table is the same as the row index. */
      pIItem->SetDataIndex(SelectedIndex);

      /* Determine which default unit has the user has selected (but possibly
          not "Applied"). */
      if (m_pMetricUnitsRadioButton->isChecked()==true)
        DefaultUnit=DEFAULTMETRIC;
      else
        DefaultUnit=DEFAULTIMPERIAL;

      /* Default. */
      UnitIndex=0;

      /* Does the information item have units? */
      pUnitList=f_pInformation[SelectedIndex].pUnitList;
      if (pUnitList!=NULL)
      {
        /* Yes. */

        /* Loop through the list, looking for a matching default. */
        for(int Index=0;pUnitList[Index].ShortName!=QString();Index++)
        {
          if ( (pUnitList[Index].UnitFlags&DefaultUnit)!=0 )
          {
            UnitIndex=Index;
            break;
          }
        }
      }
      pIItem->SetUnitIndex(UnitIndex);
    }
  }

  /* Update the line count in the information panel. */
  m_pInformationPanelDialog->SetLineCount(m_pDisplayListWidget->count());

  /* Update the display. */
  InformationPanelTimerTriggeredSlot();
  UpdateControls();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::AnimationPathnameChangedSlot(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::AnimationPathnameChangedSlot()");
  DEBUGLOG_LogIn();

  /* Try to load the file. */
  if ( (MoonAnimation_ReadFile(
      &m_MoonPreviewImages,qPrintable(m_pAnimationFilenameChooser->text()))<0) &&
      (m_StartUpFlag==false) )
    READANIMATIONWARNING(this);
  PreferencesChangedSlot();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::AnimationTimerTriggeredSlot(void)
{
  QString PercentString;
  QPixmap Pixmap;


  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::AnimationTimerTriggeredSlot()");
  DEBUGLOG_LogIn();

  /* Update the percent label. */
  PercentString.sprintf(qPrintable(tr("%d%%")),m_PreviewPercentCounter);
  m_pPreviewPercentLabel->setText(PercentString);

  /* Update the preview image. */
  Pixmap=DrawFrame(&m_MoonPreviewImages,m_PreviewPercentCounter,
      m_pUseOpaqueBackgroundGroupBox->isChecked(),
      m_pBackgroundColorButton->currentColor());
  m_pPreviewViewLabel->setPixmap(
      Pixmap.scaled(
      m_pPreviewViewLabel->width(),m_pPreviewViewLabel->height(),
      Qt::KeepAspectRatio,Qt::SmoothTransformation));

  /* Next percent. */
  m_PreviewPercentCounter=(m_PreviewPercentCounter+1)%101;

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::ButtonBoxButtonClickedSlot(QAbstractButton *pButton)
{
  bool ForceUpdateFlag;


  DEBUGLOG_Printf1(
      "CONTROLPANELDIALOG_C::ButtonBoxButtonClickedSlot(%p)",pButton);
  DEBUGLOG_LogIn();

  switch(m_pButtonBox->standardButton(pButton))
  {
    case QDialogButtonBox::Apply:
      /* Force an update if the file name changed, the use opaque background
          flag changed, or the background color changed. */
      ForceUpdateFlag=false;
      if ( (m_pAnimationFilenameChooser->text()!=
          m_pSettings->GetAnimationPathname()) ||
          (m_pUseOpaqueBackgroundGroupBox->isChecked()!=
          m_pSettings->GetUseOpaqueBackgroundFlag()) ||
          (m_pBackgroundColorButton->currentColor()!=
          m_pSettings->GetBackgroundColor()) ||
          (m_pUpdateIntervalSpinBox->value()!=
          (int)m_pSettings->GetUpdateInterval()) )
      {
        if (m_pAnimationFilenameChooser->text()!=
            m_pSettings->GetAnimationPathname())
          /* Ignore return. If any error, the user has already been informed. */
          MoonAnimation_ReadFile(
            &m_MoonTrayImages,qPrintable(m_pAnimationFilenameChooser->text()));
        ForceUpdateFlag=true;
      }
      if (m_pRemindOncePerSessionCheckBox->isChecked()==false)
        m_CloseReminderIssued=false;
      ReadPreferences(m_pSettings);
      SaveSettings();
      PreferencesChangedSlot();     // Force a dialog update.
      if (ForceUpdateFlag==true)
        ForceUpdate();
      break;
    case QDialogButtonBox::Close:
      close();
      break;
    case QDialogButtonBox::Help:
      qDebug("Help");
      break;
    default:
      break;
  }

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::CheckButtonClickedSlot(void)
{
  QNetworkRequest Request;


  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::CheckButtonClickedSlot()");
  DEBUGLOG_LogIn();

  /* In the process of checking? */
  if (m_pCheckButton->isEnabled()==true)
  {
    /* No, start the check. */
    m_pCheckButton->setEnabled(false);
    m_pCheckLabel->setText(tr("Checking for an update!"));
    Request.setUrl(QString(
        "http://downloads.sourceforge.net/project/moonphase/current_release"));
    Request.setRawHeader("User-Agent","Mozilla Firefox");
        // QNetworkRequest seems to default to "Mozilla" for the user agent
        //   and sourceforge has implemented blocking for certain user agents.
    m_pNetworkAccess->get(Request);
  }

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::
    ControlPanelActivatedSlot(QSystemTrayIcon::ActivationReason Reason)
{
  DEBUGLOG_Printf1(
      "CONTROLPANELDIALOG_C::ControlPanelActivatedSlot(%d)",Reason);
  DEBUGLOG_LogIn();

  switch(Reason)
  {
    case QSystemTrayIcon::DoubleClick:
      SetVisible(true);
      break;
//    case QSystemTrayIcon::Trigger:
//      if (m_pInformationPanelDialog->isVisible()==false)
//        m_pInformationPanelTimer->start(INFORMATIONPANELTIMER_RATE);
//      m_pInformationPanelDialog->show();
//      m_pInformationPanelDialog->raise();
//      m_pInformationPanelDialog->activateWindow();
//      break;
    default:
      break;
  }

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::
    CurrentVersionDownloadCompleteSlot(QNetworkReply *pReply)
{
  QVariant RedirectURL;
  QNetworkRequest Request;
  QByteArray Data;
  bool SuccessFlag;
  QString ValueString;
  bool OKFlag;
  int Value;
  int Delta;


  DEBUGLOG_Printf1(
      "CONTROLPANELDIALOG_C::CurrentVersionDownloadCompleteSlot(%p)",pReply);
  DEBUGLOG_LogIn();

  /* Being redirected? */
  RedirectURL=pReply->attribute(QNetworkRequest::RedirectionTargetAttribute);
  if (RedirectURL!=QVariant())
  {
    Request.setUrl(RedirectURL.toString());
    Request.setRawHeader("User-Agent","Mozilla Firefox");
        // See previous comment about user agent.
    m_pNetworkAccess->get(Request);
  }
  else
  {
    Data=pReply->readAll();
    if (Data==QByteArray())
      m_pCheckLabel->setText(tr("Error accessing the internet!"));
    else
    {
      QString DataString(Data);

      /* Expecting the data to be in the format "[M]M.[m]m.[p]p". []=optional. */
      SuccessFlag=true;
      Delta=0;
      for(int Field=0;Field<3;Field++)
      {
        ValueString=DataString.section('.',Field,Field);
        if (ValueString.isEmpty()==true)
          SuccessFlag=false;
        Value=ValueString.toInt(&OKFlag);
        if (OKFlag==false)
          SuccessFlag=false;
        switch(Field)
        {
          case 0:
            Delta=100*(MOONPHASEQT_MAJORVERSION-Value);
            break;
          case 1:
            Delta=10*(MOONPHASEQT_MINORVERSION-Value);
            break;
          case 2:
            Delta=1*(MOONPHASEQT_PATCHVERSION-Value);
            break;
          default:
            SuccessFlag=false;
        }
        if (Delta!=0)
          break;
      }
      if (SuccessFlag==false)
        m_pCheckLabel->setText(tr("Error calculating version numbers!"));
      else if (Delta>0)
        m_pCheckLabel->setText(tr("You have a pre-release version!"));
      else if (Delta==0)
        m_pCheckLabel->setText(tr("This program is up to date!"));
      else
      {
        m_pCheckLabel->setText(tr("An update is available!"));
        if (m_FirstUpdateFlag==true)
        {
          QMessageBox UpdateMessageBox(this);

          UpdateMessageBox.setWindowTitle(MOONPHASEQT_DISPLAYNAME);
          UpdateMessageBox.setTextFormat(Qt::RichText); // Makes links clickable
          UpdateMessageBox.setText("An update to this program is available!"
              "<br><br>"
              "Visit the <a href='"MOONPHASEQT_WEBSITE"'>"
              MOONPHASEQT_DISPLAYNAME" Web Site</a>");
          UpdateMessageBox.exec();
        }
      }
    }
    m_pCheckButton->setEnabled(true);
    m_FirstUpdateFlag=false;
  }

  pReply->deleteLater();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::DataItemSelectionChangedSlot(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::DataItemSelectionChangedSlot()");
  DEBUGLOG_LogIn();

  /* Allow only one list widget to have a selected item. */
  if (m_pDataListWidget->selectedItems().count()!=0)
    m_pDisplayListWidget->clearSelection();

  UpdateControls();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::DateTimeChanged(QDateTime DateTime)
{
  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::DateTimeChanged(%1)",&DateTime);
  DEBUGLOG_LogIn();

#ifdef    DEBUG
  /* Recalculate the astronomical data. */
  RecalculateMoonData(DateTime.toTime_t());

  /* Update the tray icon. */
  UpdateTrayIcon();

  /* Reset the counter. */
  m_UpdateIntervalCounter=0;
#endif    /* DEBUG */

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::DisplayItemSelectionChangedSlot(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::DisplayItemSelectionChangedSlot()");
  DEBUGLOG_LogIn();

  /* Allow only one list widget to have a selected item. */
  if (m_pDisplayListWidget->selectedItems().count()!=0)
    m_pDataListWidget->clearSelection();

  UpdateControls();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::InformationPanelTimerTriggeredSlot(void)
{
  QListWidgetItem *pLWItem;
  QString Text;
  INFORMATIONITEM_C *pIItem;
  int InfoType;
  int UnitIndex;
  double Scale;


  DEBUGLOG_Printf0(
        "CONTROLPANELDIALOG_C::InformationPanelTimerTriggeredSlot()");
  DEBUGLOG_LogIn();

  /* Is the information panel visible? */
  if (m_pInformationPanelDialog->isVisible()==false)
  {
    /* No, stop the timer (no need to update the information panel). */
    m_pInformationPanelTimer->stop();
  }
  else
  {
    /* Need to update the information panel. */
    MoonData_Recalculate(&m_MoonData,time(NULL));

    /* Update each line. */
    for(int Index=0;Index<m_pDisplayListWidget->count();Index++)
    {
      /* Get the list widget item. */
      pLWItem=m_pDisplayListWidget->item(Index);
      if (pLWItem==NULL)
      {
        MESSAGELOG_Error("NULL list widget item pointer.");
      }
      else
      {
        /* Get the information item pointer. */
        pIItem=LWI2II(pLWItem);
        if (pIItem==NULL)
        {
          MESSAGELOG_Error("NULL information item pointer.");
        }
        else
        {
          /* Default text. */
          Text="ERROR";

          /* Get the information type. */
          InfoType=pIItem->GetDataIndex();
          if ( (InfoType<0) ||
              (InfoType>=((signed)ARRAY_ELEMENTCOUNT(f_pInformation))) )
          {
            MESSAGELOG_Error("Invalid information index.");
          }
          else
          {
            UnitIndex=pIItem->GetUnitIndex();
            if ( (UnitIndex<0) && (((unsigned)UnitIndex)>=
                ARRAY_ELEMENTCOUNT(f_pInformation[InfoType].pUnitList)) )
            {
              MESSAGELOG_Error("Invalid unit index.");
            }
            else
            {
              Scale=f_pInformation[InfoType].pUnitList[UnitIndex].Scale;

              /* Print the data. */
              Text=f_pInformation[InfoType].PrintDataFunction(&m_MoonData,Scale,
                  f_pInformation[InfoType].pUnitList[UnitIndex].Precision);

              /* Prefix the information label. */
              Text=f_pInformation[InfoType].Label+": "+Text;

              /* Append the unit (if any). */
              if (f_pInformation[InfoType].pUnitList!=NULL)
                Text+=" "+
                    f_pInformation[InfoType].pUnitList[UnitIndex].ShortName;
            }
          }

          /* Send the data to the panel. */
          m_pInformationPanelDialog->SetLine(Index,Text,pIItem->GetOptions());
        }
      }
    }
  }

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::InstanceMessageSlot(QString const &Message)
{
  DEBUGLOG_Printf2("CONTROLPANELDIALOG_C::InstanceMessageSlot(%p(%s))",
      &Message,qPrintable(Message));
  DEBUGLOG_LogIn();

  if (QString::localeAwareCompare(Message,"Activate")==0)
    ControlPanelActivatedSlot(QSystemTrayIcon::DoubleClick);

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::LatitudeChangedSlot(double Latitude)
{
  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::LatitudeChangedSlot(%f)",Latitude);
  DEBUGLOG_LogIn();

  m_MoonData.CTransData.Glat=Latitude;
  MoonData_Recalculate(&m_MoonData,time(NULL));

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::LongitudeChangedSlot(double Longitude)
{
  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::LongitudeChangedSlot(%f)",Longitude);
  DEBUGLOG_LogIn();

  m_MoonData.CTransData.Glon=Longitude;
  MoonData_Recalculate(&m_MoonData,time(NULL));

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::MoveDownDisplayItemButtonClickedSlot(void)
{
  DEBUGLOG_Printf0(
      "CONTROLPANELDIALOG_C::MoveDownDisplayItemButtonClickedSlot()");
  DEBUGLOG_LogIn();

  MoveItem(1);

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::MoveUpDisplayItemButtonClickedSlot(void)
{
  DEBUGLOG_Printf0(
      "CONTROLPANELDIALOG_C::MoveUpDisplayItemButtonClickedSlot()");
  DEBUGLOG_LogIn();

  MoveItem(-1);

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::OptionsAppliedSlot(OPTIONS_C const &Options)
{
  QListWidgetItem *pLWItem;
  INFORMATIONITEM_C *pIItem;


  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::OptionsAppliedSlot(%p)",&Options);
  DEBUGLOG_LogIn();

  pLWItem=m_pDisplayListWidget->selectedItems()[0];
  if (pLWItem==NULL)
  {
    MESSAGELOG_Error("NULL list widget item pointer");
  }
  else
  {
    pIItem=LWI2II(pLWItem);
    if (pIItem==NULL)
    {
      MESSAGELOG_Error("NULL list widget item pointer");
    }
    else
    {
      /* Copy the options. */
      pIItem->SetOptions(Options);
    }
  }

  InformationPanelTimerTriggeredSlot();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::OptionsDisplayItemButtonClickedSlot(void)
{
  QListWidgetItem *pLWItem;
  INFORMATIONITEM_C *pIItem;
  UNIT_T const * pUnit;
  INFORMATIONOPTIONSDIALOG_C OptionsDialog(this);
  QList<QString> UnitList;


  DEBUGLOG_Printf0(
      "CONTROLPANELDIALOG_C::OptionsDisplayItemButtonClickedSlot()");
  DEBUGLOG_LogIn();

  pLWItem=m_pDisplayListWidget->selectedItems()[0];
  if (pLWItem==NULL)
  {
    MESSAGELOG_Error("NULL list widget item pointer");
  }
  else
  {
    pIItem=LWI2II(pLWItem);
    if (pIItem==NULL)
    {
      MESSAGELOG_Error("NULL list widget item pointer");
    }
    else
    {
      /* Create the unit list. */
      for(pUnit=f_pInformation[pIItem->GetDataIndex()].pUnitList;
          pUnit->ShortName!=QString();pUnit++)
      {
        UnitList.append(pUnit->ShortName+" ("+pUnit->LongName+")");
      }

      /* Catch the signal from the Apply button. */
      connect(&OptionsDialog,SIGNAL(OptionsAppliedSignal(OPTIONS_C const &)),
          this,SLOT(OptionsAppliedSlot(OPTIONS_C const &)));

      /* Set the unit list in the dialog box. */
      OptionsDialog.SetUnitList(UnitList);

      /* Set the options in the dialog box. */
      OptionsDialog.SetOptions(pIItem->GetOptions());

      /* Show the dialog box. */
      if (OptionsDialog.exec()==QDialog::Accepted)
      {
        /* Accepted. */

        /* Copy the options. */
        pIItem->SetOptions(OptionsDialog.GetOptions());

        InformationPanelTimerTriggeredSlot();
      }
    }
  }

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::PreferencesChangedSlot(void)
{
  SETTINGS_C Settings;


  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::PreferencesChangedSlot()");
  DEBUGLOG_LogIn();

  /* Update a sub-option. */
  m_pRemindOncePerSessionCheckBox->setEnabled(
      m_pStillRunningReminder->isChecked()!=false);

  /* Get widget preferences. */
  ReadPreferences(&Settings);

  /* Update Apply button. */
  m_pButtonBox->button(QDialogButtonBox::Apply)->
      setEnabled(Settings!=*m_pSettings);

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::QuitSlot(void)
{
  bool QuitFlag;


  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::QuitSlot()");
  DEBUGLOG_LogIn();

  /* Check if preferences have been changed.
      If so, ask if user wants to save them, and if yes, save them. */
  CheckSavePreferences();

  /* Need to confirm quit? */
  if (m_pSettings->GetConfirmQuitFlag()==true)
  {
    /* Yes. */
    QuitFlag=false;
    if (QMessageBox::question(this,MOONPHASEQT_DISPLAYNAME,
        tr("Are you sure you want to quit?"),
        QMessageBox::Yes|QMessageBox::No,QMessageBox::No)==QMessageBox::Yes)
      QuitFlag=true;
  }
  else
  {
    /* No. */
    QuitFlag=true;
  }
  if (QuitFlag==true)
    qApp->quit();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::RemoveDataItemButtonClickedSlot(void)
{
  QListWidgetItem *pItem;
  int Row;


  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::RemoveDataItemButtonClickedSlot()");
  DEBUGLOG_LogIn();

  Row=m_pDisplayListWidget->row(m_pDisplayListWidget->selectedItems()[0]);
  pItem=m_pDisplayListWidget->takeItem(Row);
  if (pItem==NULL)
  {
    MESSAGELOG_Error("NULL item pointer.");
  }
  delete pItem;
  m_pInformationPanelDialog->SetLineCount(m_pDisplayListWidget->count());

  /* Update the display. */
  InformationPanelTimerTriggeredSlot();
  UpdateControls();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::ShowControlPanelSlot(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::ShowControlPanelSlot()");
  DEBUGLOG_LogIn();

  ControlPanelActivatedSlot(QSystemTrayIcon::DoubleClick);

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::ShowInformationPanelSlot(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::ShowInformationPanelSlot()");
  DEBUGLOG_LogIn();

//  ControlPanelActivatedSlot(QSystemTrayIcon::Trigger);
  if (m_pInformationPanelDialog->isVisible()==false)
    m_pInformationPanelTimer->start(INFORMATIONPANELTIMER_RATE);
  m_pInformationPanelDialog->show();
  m_pInformationPanelDialog->raise();
  m_pInformationPanelDialog->activateWindow();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::StillRunningReminderClickedSlot(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::StillRunningReminderClickedSlot()");
  DEBUGLOG_LogIn();

  /* If Still Running Reminder checkbox is checked, then the Once Per Session
      checkbox is toggled, and then the Still Running Reminder is unchecked,
      the Apply button should disable, but doesn't. When the Still checkbox is
      cleared, the previous Once state is restored to its prior value. */
  if (m_pStillRunningReminder->isChecked()==false)
    m_pRemindOncePerSessionCheckBox->setChecked(
        m_pSettings->GetRemindOncePerSessionFlag());

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::UpdateTimerTriggeredSlot(void)
{
  QPixmap Pixmap;


  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::UpdateTimerTriggeredSlot()");
  DEBUGLOG_LogIn();

  /* Check weekly for a program update. */
  if (QDate::currentDate()>=m_NextUpdateCheck)
  {
#ifdef    DEBUG
    {
      time_t TimeSeconds1970;
      struct tm *pTimeInfo;
#define   BUFFER_SIZE   (1024)
      char pPtr[BUFFER_SIZE];


      time(&TimeSeconds1970);
      pTimeInfo=localtime(&TimeSeconds1970);
      strftime(pPtr,BUFFER_SIZE,"Check for update: %H:%M:%S",pTimeInfo);
#undef    BUFFER_SIZE
      MESSAGELOG_Info(pPtr);
    }
#endif    /* DEBUG */

#ifndef   DEBUG
    /* Force a check for an update. */
    CheckButtonClickedSlot();
#endif    /* DEBUG */
    m_NextUpdateCheck.addDays(7);
  }

  /* Check if calculations need to be run, and (possibly) the icon updated. */
  m_UpdateIntervalCounter++;
  if (m_UpdateIntervalCounter>=(m_pSettings->GetUpdateInterval()))
  {
#ifdef    DEBUG
    {
      time_t TimeSeconds1970;
      struct tm *pTimeInfo;
#define   BUFFER_SIZE   (1024)
      char pPtr[BUFFER_SIZE];


      time(&TimeSeconds1970);
      pTimeInfo=localtime(&TimeSeconds1970);
      strftime(pPtr,BUFFER_SIZE,"Update tray: %H:%M:%S",pTimeInfo);
#undef    BUFFER_SIZE
      MESSAGELOG_Info(pPtr);
    }
#endif    /* DEBUG */

    /* Recalculate the astronomical data. */
    RecalculateMoonData(time(NULL));

    /* Update the tray icon. */
    UpdateTrayIcon();

    /* Reset the counter. */
    m_UpdateIntervalCounter=0;
  }

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::UpdateTrayIcon(void)
{
  QString PercentString;
  QPixmap Pixmap;
  float Percent;


  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::UpdateTrayIcon()");
  DEBUGLOG_LogIn();

  /* Update the icon. */
  Percent=MoonData_GetMoonPhasePercent(&m_MoonData);
  Pixmap=DrawFrame(&m_MoonTrayImages,Percent,
      m_pSettings->GetUseOpaqueBackgroundFlag(),
      m_pSettings->GetBackgroundColor());
  m_pTrayIcon->setIcon(Pixmap);

  /* Update the tool tip */
  m_pTrayIcon->setToolTip(
      MOONPHASEQT_DISPLAYNAME+QString(" - %1%").arg((int)(Percent+0.5)));

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::UseOpaqueBackgroundClickedSlot(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::UseOpaqueBackgroundClickedSlot()");
  DEBUGLOG_LogIn();

  /* If Use Opaque Background checkbox is checked, then a color is selected
      from the color button, and then the Use Opaque Background is unchecked,
      the Apply button should disable, but doesn't. When the Use checkbox is
      cleared, the previous background color is restored to its prior value. */
  if (m_pUseOpaqueBackgroundGroupBox->isChecked()==false)
    m_pBackgroundColorButton->setCurrentColor(
        m_pSettings->GetBackgroundColor());

  DEBUGLOG_LogOut();
  return;
}

























































/****
*****
***** FUNCTIONS
*****
****/

QString PrintAngle0(MOONDATA_T *pMoonData,double Scale,int Precision)
{
  QString Text;


  Text=QString("%1").arg(90.0*Scale,0,'f',Precision);

  return(Text);
}

QString PrintAngle1(MOONDATA_T *pMoonData,double Scale,int Precision)
{
  QString Text;


  Text=QString("%1").arg(180.0*Scale,0,'f',Precision);

  return(Text);
}

QString PrintAngle2(MOONDATA_T *pMoonData,double Scale,int Precision)
{
  QString Text;


  Text=QString("%1").arg(270.0*Scale,0,'f',Precision);

  return(Text);
}

QString PrintDistance0(MOONDATA_T *pMoonData,double Scale,int Precision)
{
  QString Text;


  Text=QString("%1").arg(1*Scale,0,'f',Precision);

  return(Text);
}

QString PrintDistance1(MOONDATA_T *pMoonData,double Scale,int Precision)
{
  QString Text;


  Text=QString("%1").arg(6.2137119*Scale,0,'f',Precision);

  return(Text);
}

QString PrintDistance2(MOONDATA_T *pMoonData,double Scale,int Precision)
{
  QString Text;


  Text=QString("%1").arg(92955808.0*Scale,0,'f',Precision);

  return(Text);
}


#undef    CONTROLPANELDIALOG_CPP
