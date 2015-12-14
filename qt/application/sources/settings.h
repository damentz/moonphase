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
*** \file settings.h
*** \brief Change/save/load settings.
*** \details Allows changing, saving, and loading of settings.
**/


#ifndef   SETTINGS_H
#define   SETTINGS_H


/****
*****
***** INCLUDES
*****
****/

#include  <QSettings>
#include  <QColor>


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
*** \brief Change/save/load settings.
*** \details Allows changing, saving, and loading of settings.
**/
class SETTINGS_C : protected QSettings
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
    *** \brief Return latitude.
    *** \details Returns the latitude.
    *** \returns Latitude.
    **/
    double GetLatitude(void) const;

    /**
    *** \brief Return longitude.
    *** \details Returns the longitude.
    *** \returns Longitude.
    **/
    double GetLongitude(void) const;

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
    *** \brief Set latitude.
    *** \details Set the latitude.
    *** \returns Latitude.
    **/
    void SetLatitude(double Latitude);

    /**
    *** \brief Set longitude.
    *** \details Set the longitude.
    *** \returns Longitude.
    **/
    void SetLongitude(double Longitude);

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
    *** \brief Latitude.
    *** \details Laitude.
    **/
    double m_Latitude;

    /**
    *** \brief Longitude.
    *** \details Longitude.
    **/
    double m_Longitude;

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


#endif    /* SETTINGS_H */
