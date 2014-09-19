/*
** This file is part of moonphase.
** Copyright (C) 2014 by Alan Wise (alanwise@users.sourceforge.net)
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
*** \file controlpaneldialog.h
*** \brief Application main window.
*** \details The main window of the application.
**/


#ifndef   CONTROLPANELDIALOG_H
#define   CONTROLPANELDIALOG_H


/****
*****
***** INCLUDES
*****
****/

#include  "ui_controlpaneldialog.h"
#include  "moonanimation.h"
#include  "moondata.h"

#include  <QSystemTrayIcon>


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

class SETTINGS_C;

/**
*** \brief Application main window.
*** \details The main window of the application.
**/
class CONTROLPANELDIALOG_C : public QDialog, public Ui::CONTROLPANELDIALOGUI_C
{
  Q_OBJECT

  public:
    /**
    *** \brief Constructor.
    *** \details Constructor.
    *** \param pParent Pointer to parent widget.
    **/
    CONTROLPANELDIALOG_C(QWidget *pParent=NULL);

    /**
    *** \brief Destructor.
    *** \details Destructor.
    **/
    ~CONTROLPANELDIALOG_C(void);

    /**
    *** \brief Allow multiple instances flag.
    *** \details Limit the program to one running instance or allow multiple
    ***   instances at the same time.
    *** \retval 0 Only once instance allowed.
    *** \retval !0 Allow multiple instances.
    **/
    bool GetAllowMultipleInstancesFlag(void);

  protected:
    /**
    *** \brief Close event handler.
    *** \details Handler called when a window close event occurs.
    *** \param pEvent Close event data.
    **/
    void closeEvent(QCloseEvent *pEvent);

  private:
    /**
    *** \brief Checks for changed preferences, might prompt to save/discard.
    *** \details Checks if the preferences have changed, and if desired, prompts
    ***   the user to save/discard them.
    **/
    void CheckSavePreferences(void);

    /**
    *** \brief Draws a frame of an animation.
    *** \details Given a phase percentage of the moon, draws a frame of an
    ***   animation. The background is transparent, but may be filled with a
    ***   color, if desired.
    *** \param pMoonAnimation Animation image data.
    *** \param Percent Phase percentage of moon [0-100].
    *** \param UseBackgroundColorFlag 0=Draw transparent background,\n
    ***   !0=Draw background using a color.
    *** \param BackgroundColor Background color (only used if
    ***   UseBackgroundColorFlag!=0).
    *** \return Animation frame.
    **/
    QPixmap DrawFrame(MOONANIMATION_T *pMoonAnimation,unsigned int Percent,
        bool UseBackgroundColorFlag,QColor BackgroundColor);

    /**
    *** \brief Forces moon data recalculation and (possibly) icon update.
    *** \details Forces the application to recalculate the moon data and
    ***   (possibly) updates the icon.
    **/
    void ForceUpdate(void);

    /**
    *** \brief About tab initializer.
    *** \details Initializes the About tab.
    **/
    void InitializeAboutTab(void);

    /**
    *** \brief Preferences tab initializer.
    *** \details Initializes the Preferences tab.
    **/
    void InitializePreferencesTab(void);

    /**
    *** \brief Reads settings.
    *** \details Reads application settings from the configuration file.
    **/
    void LoadSettings(void);

    /**
    *** \brief Reads preferences from widgets.
    *** \details Reads the preferences from the various widgets in the
    ***   preferences tab.
    *** \param pSettings Storage for the preferences.
    *** \return Preferences as set in the widgets.
    **/
    void ReadPreferences(SETTINGS_C *pSettings);

    /**
    *** \brief Write settings.
    *** \details Writes application settings to the configuration file.
    **/
    void SaveSettings(void);

    /**
    *** \brief Shows/hides the control panel.
    *** \details Shows/hides the control panel, may also start or stop the
    ***   animation timer.
    *** \param VisibleFlag 0=Hide control panel,\n!0=Show control panel.
    **/
    void SetVisible(bool VisibleFlag);

  private slots:
    /**
    *** \brief Animation pathname changed.
    *** \details The animation pathname has changed, attempt to read the file.
    **/
    void AnimationPathnameChangedSlot(void);

    /**
    *** \brief Animation timer triggered.
    *** \details The animation timer has been triggered, update the preview
    ***   image.
    **/
    void AnimationTimerTriggeredSlot(void);

    /**
    *** \brief Button box button clicked.
    *** \details A button in the button box was clicked.
    *** \param pButton
    **/
    void ButtonBoxButtonClickedSlot(QAbstractButton *pButton);

    /**
    *** \brief Control panel activated.
    *** \details The control panel was activated.
    *** \param Reason The reason the system tray was activated.
    **/
    void ControlPanelActivatedSlot(QSystemTrayIcon::ActivationReason Reason);

    /**
    *** \brief Help button clicked.
    *** \details The help button was clicked.
    **/
    void HelpButtonClickedSlot(void);

    /**
    *** \brief Preferences changed.
    *** \details The preferences have changed.
    **/
    void PreferencesChangedSlot(void);

    /**
    *** \brief Message from another instance was received.
    *** \details A messsage from another instance was received.
    **/
    void InstanceMessageSlot(QString const &Message);

    /**
    *** \brief Quit requested.
    *** \details The user wants to quit.
    **/
    void QuitSlot(void);

    /**
    *** \brief Still Running Reminder widget clicked.
    *** \details The Still Running Reminder widget was clicked.
    **/
    void StillRunningReminderClickedSlot(void);

    /**
    *** \brief Show control panel.
    *** \details The control panel needs to be shown.
    **/
    void ShowControlPanelSlot(void);

    /**
    *** \brief Update timer triggered.
    *** \details The update timer has been triggered, update the moon data and
    ***   (possibly) the icon.
    **/
    void UpdateTimerTriggeredSlot(void);

    /**
    *** \brief Use Opaque Background widget clicked.
    *** \details The Use Opaque Background widget was clicked.
    **/
    void UseOpaqueBackgroundClickedSlot(void);

  private:
    /**
    *** \brief Moon data.
    *** \details All data pertaining to the moon (phase, etc.).
    **/
    MOONDATA_T m_MoonData;

    /**
    *** \brief Tray icon.
    *** \details The images displayed in the tray icon.
    **/
    MOONANIMATION_T m_MoonTrayImages;

    /**
    *** \brief Preview icon.
    *** \details The images displayed in the preview widget.
    **/
    MOONANIMATION_T m_MoonPreviewImages;

    /**
    *** \brief Tray icon menu.
    *** \details Menu displayed when the tray icon is right clicked.
    **/
    QMenu *m_pTrayIconMenu;

    /**
    *** \brief Tray icon.
    *** \details Icon display in the tray.
    **/
    QSystemTrayIcon *m_pTrayIcon;

    /**
    *** \brief Animation timer.
    *** \details Timer used to update the preview widget.
    **/
    QTimer *m_pAnimationTimer;

    /**
    *** \brief Update timer.
    *** \details Timer used to update the moon data and (possibly) the tray
    ***   icon.
    **/
    QTimer *m_pUpdateTimer;

    /**
    *** \brief Settings.
    *** \details Setting read from the configuration file, modified by the user,
    ***   and written to the configuration file.
    **/
    SETTINGS_C *m_pSettings;

    /**
    *** \brief Preview percent counter.
    *** \details Counter used to animate the preview widget.
    **/
    unsigned int m_PreviewPercentCounter;

    /**
    *** \brief Update interval counter.
    *** \details Counter used to determine when to update the moon data and
    ***   (possibly) the tray icon.
    **/
    unsigned int m_UpdateIntervalCounter;

    /**
    *** \brief Close Warning issued.
    *** \details Used with the Still Running Reminder - Once Per Session
    ***   preferences. Indicates if the reminder has been issued already.
    **/
    bool m_CloseReminderIssued;
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


#endif    /* CONTROLPANELDIALOG_H */
