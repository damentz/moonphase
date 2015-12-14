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
*** \file settings.cpp
*** \brief settings.cpp implementation.
*** \details Implementation file for settings.cpp.
**/


/** Identifier for settings.cpp. **/
#define   SETTINGS_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "settings.h"
#ifdef    DEBUG_SETTINGS_CPP
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_SETTINGS_CPP */
#include  "debuglog.h"
#include  "messagelog.h"


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
*** \brief Latitude key.
*** \details Key to access latitude in configuration file.
**/
#define   PREFERENCES_LATITUDE                      "Latitude"

/**
*** \brief Longitude key.
*** \details Key to access Longitude in configuration file.
**/
#define   PREFERENCES_LONGITUDE                     "Longitude"

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
*** \brief Use opaque background flag key.
*** \details Key to access use opaque background flag in configuration file.
**/
#define   PREFERENCES_USEOPAQUEBACKGROUNDFLAG       "UseOpaqueBackgroundFlag"


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

SETTINGS_C::SETTINGS_C(void)
{
  DEBUGLOG_Printf0("SETTINGS_C::SETTINGS_C()");
  DEBUGLOG_LogIn();

  m_AllowMultipleInstancesFlag=false;
  m_AnimationPathname="";
  m_BackgroundColor=QColor(0,0,0);
  m_ConfirmDiscardFlag=true;
  m_ConfirmQuitFlag=true;
  m_DefaultToMetricUnitsFlag=true;
  m_Latitude=0.0;
  m_Longitude=0.0;
  m_RemindOncePerSessionFlag=true;
  m_StillRunningReminderFlag=true;
  m_UpdateInterval=4;
  m_UseOpaqueBackgroundFlag=false;

  DEBUGLOG_LogOut();
  return;
}

SETTINGS_C::~SETTINGS_C(void)
{
  DEBUGLOG_Printf0("SETTINGS_C::~SETTINGS_C()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return;
}

bool SETTINGS_C::operator==(SETTINGS_C const &RHS) const
{
  bool EqualFlag;


  DEBUGLOG_Printf1("SETTINGS_C::operator==(%p)",&RHS);
  DEBUGLOG_LogIn();

  EqualFlag=(QString::localeAwareCompare(
      m_AnimationPathname,RHS.m_AnimationPathname)==0) &&
      (m_AllowMultipleInstancesFlag==RHS.m_AllowMultipleInstancesFlag) &&
      (m_BackgroundColor==RHS.m_BackgroundColor) &&
      (m_ConfirmDiscardFlag==RHS.m_ConfirmDiscardFlag) &&
      (m_ConfirmQuitFlag==RHS.m_ConfirmQuitFlag) &&
      (m_DefaultToMetricUnitsFlag==RHS.m_DefaultToMetricUnitsFlag) &&
      (m_Latitude==RHS.m_Latitude) && (m_Longitude==RHS.m_Longitude) &&
      (m_RemindOncePerSessionFlag==RHS.m_RemindOncePerSessionFlag) &&
      (m_StillRunningReminderFlag==RHS.m_StillRunningReminderFlag) &&
      (m_UpdateInterval==RHS.m_UpdateInterval) &&
      (m_UseOpaqueBackgroundFlag==RHS.m_UseOpaqueBackgroundFlag);

  DEBUGLOG_LogOut();
  return(EqualFlag);
}

bool SETTINGS_C::operator!=(SETTINGS_C const &RHS) const
{
  bool EqualFlag;


  DEBUGLOG_Printf1("SETTINGS_C::operator==(%p)",&RHS);
  DEBUGLOG_LogIn();

  EqualFlag=!((*this)==RHS);

  DEBUGLOG_LogOut();
  return(EqualFlag);
}

void SETTINGS_C::Load(void)
{
  DEBUGLOG_Printf0("SETTINGS_C::Load()");
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
  m_DefaultToMetricUnitsFlag=value(
      PREFERENCES_DEFAULTTOMETRICUNITSFLAG,m_DefaultToMetricUnitsFlag).toBool();
  m_Latitude=value(PREFERENCES_LATITUDE,m_Latitude).toDouble();
  m_Longitude=value(PREFERENCES_LONGITUDE,m_Longitude).toDouble();
  m_RemindOncePerSessionFlag=value(PREFERENCES_REMINDONCEPERSESSIONFLAG,
      m_RemindOncePerSessionFlag).toBool();
  m_StillRunningReminderFlag=value(
      PREFERENCES_STILLRUNNINGREMINDERFLAG,m_StillRunningReminderFlag).toBool();
  m_UpdateInterval=value(PREFERENCES_UPDATEINTERVAL,m_UpdateInterval).toUInt();
  m_UseOpaqueBackgroundFlag=value(PREFERENCES_USEOPAQUEBACKGROUNDFLAG,
      m_UseOpaqueBackgroundFlag).toBool();

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::Save(void)
{
  DEBUGLOG_Printf0("SETTINGS_C::Save()");
  DEBUGLOG_LogIn();

  setValue(PREFERENCES_ALLOWMULTIPLEINSTANCESFLAG,m_AllowMultipleInstancesFlag);
  setValue(PREFERENCES_ANIMATIONPATHNAME,m_AnimationPathname);
  setValue(PREFERENCES_BACKGROUNDCOLOR,m_BackgroundColor);
  setValue(PREFERENCES_CONFIRMDISCARDCHANGESFLAG,m_ConfirmDiscardFlag);
  setValue(PREFERENCES_CONFIRMQUITFLAG,m_ConfirmQuitFlag);
  setValue(PREFERENCES_DEFAULTTOMETRICUNITSFLAG,m_DefaultToMetricUnitsFlag);
  setValue(PREFERENCES_LATITUDE,m_Latitude);
  setValue(PREFERENCES_LONGITUDE,m_Longitude);
  setValue(PREFERENCES_REMINDONCEPERSESSIONFLAG,m_RemindOncePerSessionFlag);
  setValue(PREFERENCES_STILLRUNNINGREMINDERFLAG,m_StillRunningReminderFlag);
  setValue(PREFERENCES_UPDATEINTERVAL,m_UpdateInterval);
  setValue(PREFERENCES_USEOPAQUEBACKGROUNDFLAG,m_UseOpaqueBackgroundFlag);

  DEBUGLOG_LogOut();
  return;
}

bool SETTINGS_C::GetAllowMultipleInstancesFlag(void) const
{
  DEBUGLOG_Printf0(
      "SETTINGS_C::GetAllowMultipleInstancesFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_AllowMultipleInstancesFlag);
}

QString SETTINGS_C::GetAnimationPathname(void) const
{
  DEBUGLOG_Printf0("SETTINGS_C::GetAnimationPathname()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_AnimationPathname);
}

QColor SETTINGS_C::GetBackgroundColor(void) const
{
  DEBUGLOG_Printf0("SETTINGS_C::GetBackgroundColor()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_BackgroundColor);
}

bool SETTINGS_C::GetConfirmDiscardFlag(void) const
{
  DEBUGLOG_Printf0("SETTINGS_C::GetConfirmDiscardFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_ConfirmDiscardFlag);
}

bool SETTINGS_C::GetConfirmQuitFlag(void) const
{
  DEBUGLOG_Printf0("SETTINGS_C::GetConfirmQuitFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_ConfirmQuitFlag);
}

bool SETTINGS_C::GetDefaultToMetricUnitsFlag(void) const
{
  DEBUGLOG_Printf0(
      "SETTINGS_C::GetDefaultToMetricUnitsFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_DefaultToMetricUnitsFlag);
}

double SETTINGS_C::GetLatitude(void) const
{
  DEBUGLOG_Printf0("SETTINGS_C::GetLatitude()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_Latitude);
}

double SETTINGS_C::GetLongitude(void) const
{
  DEBUGLOG_Printf0("SETTINGS_C::GetLongitude()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_Longitude);
}

bool SETTINGS_C::GetRemindOncePerSessionFlag(void) const
{
  DEBUGLOG_Printf0(
      "SETTINGS_C::GetRemindOncePerSessionFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_RemindOncePerSessionFlag);
}

bool SETTINGS_C::GetStillRunningReminderFlag(void) const
{
  DEBUGLOG_Printf0(
      "SETTINGS_C::GetStillRunningReminderFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_StillRunningReminderFlag);
}

unsigned int SETTINGS_C::GetUpdateInterval(void) const
{
  DEBUGLOG_Printf0("SETTINGS_C::GetUpdateInterval()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_UpdateInterval);
}

bool SETTINGS_C::GetUseOpaqueBackgroundFlag(void) const
{
  DEBUGLOG_Printf0(
      "SETTINGS_C::GetUseOpaqueBackgroundFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_UseOpaqueBackgroundFlag);
}

void SETTINGS_C::
    SetAllowMultipleInstancesFlag(bool const AllowMultipleInstancesFlag)
{
  DEBUGLOG_Printf1(
      "SETTINGS_C::SetAllowMultipleInstancesFlag(%u)",
      AllowMultipleInstancesFlag);
  DEBUGLOG_LogIn();

  m_AllowMultipleInstancesFlag=AllowMultipleInstancesFlag;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::
    SetAnimationPathname(QString const Pathname)
{
  DEBUGLOG_Printf2(
      "SETTINGS_C::SetAnimationPathname(%p(%s))",
      &Pathname,qPrintable(Pathname));
  DEBUGLOG_LogIn();

  m_AnimationPathname=Pathname;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::
    SetBackgroundColor(QColor const BackgroundColor)
{
  DEBUGLOG_Printf1("SETTINGS_C::SetBackgroundColor(%u)",
      BackgroundColor.value());
  DEBUGLOG_LogIn();

  m_BackgroundColor=BackgroundColor;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::
    SetConfirmDiscardFlag(bool const ConfirmDiscardFlag)
{
  DEBUGLOG_Printf1(
      "SETTINGS_C::SetConfirmDiscardFlag(%u)",
      ConfirmDiscardFlag);
  DEBUGLOG_LogIn();

  m_ConfirmDiscardFlag=ConfirmDiscardFlag;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::
    SetConfirmQuitFlag(bool const ConfirmQuitFlag)
{
  DEBUGLOG_Printf1("SETTINGS_C::SetConfirmQuitFlag(%u)",
      ConfirmQuitFlag);
  DEBUGLOG_LogIn();

  m_ConfirmQuitFlag=ConfirmQuitFlag;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::
    SetDefaultToMetricUnitsFlag(bool const DefaultToMetricUnitsFlag)
{
  DEBUGLOG_Printf1(
      "SETTINGS_C::SetDefaultToMetricUnitsFlag(%u)",
      DefaultToMetricUnitsFlag);
  DEBUGLOG_LogIn();

  m_DefaultToMetricUnitsFlag=DefaultToMetricUnitsFlag;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::SetLatitude(double Latitude)
{
  DEBUGLOG_Printf1(
      "SETTINGS_C::SetLatitude(%u)",Latitude);
  DEBUGLOG_LogIn();

  m_Latitude=Latitude;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::SetLongitude(double Longitude)
{
  DEBUGLOG_Printf1(
      "SETTINGS_C::SetLongitude(%u)",Longitude);
  DEBUGLOG_LogIn();

  m_Longitude=Longitude;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::
    SetRemindOncePerSessionFlag(bool const OnceFlag)
{
  DEBUGLOG_Printf1(
      "SETTINGS_C::SetRemindOncePerSessionFlag(%u)",
      OnceFlag);
  DEBUGLOG_LogIn();

  m_RemindOncePerSessionFlag=OnceFlag;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::
    SetStillRunningReminderFlag(bool const ReminderFlag)
{
  DEBUGLOG_Printf1(
      "SETTINGS_C::SetStillRunningReminderFlag(%u)",
      ReminderFlag);
  DEBUGLOG_LogIn();

  m_StillRunningReminderFlag=ReminderFlag;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::
    SetUpdateInterval(unsigned int const Interval)
{
  DEBUGLOG_Printf1("SETTINGS_C::SetUpdateInterval(%u)",
      Interval);
  DEBUGLOG_LogIn();

  m_UpdateInterval=Interval;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::
    SetUseOpaqueBackgroundFlag(bool const UseFlag)
{
  DEBUGLOG_Printf1(
      "SETTINGS_C::SetUseOpaqueBackgroundFlag(%u)",
      UseFlag);
  DEBUGLOG_LogIn();

  m_UseOpaqueBackgroundFlag=UseFlag;

  DEBUGLOG_LogOut();
  return;
}


#undef    SETTINGS_CPP
