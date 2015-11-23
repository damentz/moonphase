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
#include  "ui_testwidget.h"
#include  "moonanimation.h"
#include  "moondata.h"
#include  "updatenotifier.h"

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

class OPTIONS_C;
class INFORMATIONPANELDIALOG_C;

#ifdef    DEBUG
/**
*** \brief Test widget.
*** \details A widget containing other widgets to be used for testing.
**/
class TESTWIDGET_C : public QWidget, public Ui::TESTWIDGETUI_C
{
  Q_OBJECT

  public:
    /**
    *** \brief Constructor.
    *** \details Constructor.
    *** \param pParent Pointer to parent widget.
    **/
    TESTWIDGET_C(QWidget *pParent=NULL);

    /**
    *** \brief Destructor.
    *** \details Destructor.
    **/
    ~TESTWIDGET_C(void);
};
#endif    /* DEBUG */

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
    class SETTINGS_C;

    /**
    *** \brief Checks for changed preferences, might prompt to save/discard.
    *** \details Checks if the preferences have changed, and if desired, prompts
    ***   the user to save/discard them.
    **/
    void CheckSavePreferences(void);

    /**
    *** \brief Creates and initializes the test tab.
    *** \details Creates the test tab in the tab widget and initializes it.
    **/
    void CreateAndInitializeTestTab(void);

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
    *** \brief Move a display item.
    *** \details Moves a display item up or down in the display list.
    *** \param Direction - 1 to move the item up\n - -1 to move the item down.
    **/
    void MoveItem(int Direction);

    /**
    *** \brief Reads preferences from widgets.
    *** \details Reads the preferences from the various widgets in the
    ***   preferences tab.
    *** \param pSettings Storage for the preferences.
    *** \return Preferences as set in the widgets.
    **/
    void ReadPreferences(SETTINGS_C *pSettings);

    /**
    *** \brief Recalculates moon data.
    *** \details Recalculates the moon data for a specific time.
    *** \param Time Time to use for calculations.
    **/
    void RecalculateMoonData(time_t Time);

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

    /**
    *** \brief Update information panel tab controls.
    *** \details Enables/disables the add/remove/up/down/options buttons in the
    ***   information panel tab.
    **/
    void UpdateControls(void);

    /**
    *** \brief Updates tray icon.
    *** \details Updates the moon phase icon in the system tray.
    **/
    void UpdateTrayIcon(void);

  private slots:
    /**
    *** \brief Data item added to display.
    *** \details Adds an item from the data list to the display list.
    **/
    void AddDataItemButtonClickedSlot(void);

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
    *** \brief Check button clicked.
    *** \details The Check button was clicked.
    **/
    void CheckButtonClickedSlot(void);

    /**
    *** \brief Control panel activated.
    *** \details The control panel was activated.
    *** \param Reason The reason the system tray was activated.
    **/
    void ControlPanelActivatedSlot(QSystemTrayIcon::ActivationReason Reason);

    /**
    *** \brief Data item selected.
    *** \details An item in the data list was selected.
    **/
    void DataItemSelectionChangedSlot(void);

    /**
    *** \brief Date and/or time changed.
    *** \details The date and/or time changed in the test widget.
    *** \param DateTime
    **/
    void DateTimeChanged(QDateTime DateTime);

    /**
    *** \brief Display item selected.
    *** \details An item in the display list was selected.
    **/
    void DisplayItemSelectionChangedSlot(void);

    /**
    *** \brief Double click timed out.
    *** \details The delay used to determine if two clicks are actually a
    ***   double click.
    **/
    void DoubleClickTimeoutTimerTriggered(void);

    /**
    *** \brief Update panel timer triggered.
    *** \details The timer to update the information panel triggered.
    **/
    void InformationPanelTimerTriggeredSlot(void);

    /**
    *** \brief Message from another instance was received.
    *** \details A messsage from another instance was received.
    *** \param Message
    **/
    void InstanceMessageSlot(QString const &Message);

    /**
    *** \brief Latitude changed.
    *** \details The data in the latitude widget changed.
    *** \param Latitude Users latitude.
    **/
    void LatitudeChangedSlot(double Latitude);

    /**
    *** \brief Longitude changed.
    *** \details The data in the longitude widget changed.
    *** \param Longitude Users longitude.
    **/
    void LongitudeChangedSlot(double Longitude);

    /**
    *** \brief Move display item down.
    *** \details Moves a display item down in the list.
    **/
    void MoveDownDisplayItemButtonClickedSlot(void);

    /**
    *** \brief Move display item up.
    *** \details Moves a display item up in the list.
    **/
    void MoveUpDisplayItemButtonClickedSlot(void);

    /**
    *** \brief Apply button clicked.
    *** \details The Apply button in the options dialog box was clicked.
    *** \param Options Options to be applied.
    **/
    void OptionsAppliedSlot(OPTIONS_C const &Options);

    /**
    *** \brief Options button was clicked.
    *** \details The options button in the information panel tab was clicked.
    **/
    void OptionsDisplayItemButtonClickedSlot(void);

    /**
    *** \brief Preferences changed.
    *** \details The preferences have changed.
    **/
    void PreferencesChangedSlot(void);

    /**
    *** \brief Quit requested.
    *** \details The user wants to quit.
    **/
    void QuitSlot(void);

    /**
    *** \brief Remove button was clicked.
    *** \details The remove button in the information panel tab was clicked.
    **/
    void RemoveDataItemButtonClickedSlot(void);

    /**
    *** \brief Show control panel.
    *** \details The control panel needs to be shown.
    **/
    void ShowControlPanelSlot(void);

    /**
    *** \brief Show the information panel.
    *** \details User request that the information panel be shown.
    **/
    void ShowInformationPanelSlot(void);

    /**
    *** \brief Still Running Reminder widget clicked.
    *** \details The Still Running Reminder widget was clicked.
    **/
    void StillRunningReminderClickedSlot(void);

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

    /**
    *** \brief Newest version number was downloaded.
    *** \details The number of the newest program version was downloaded.
    *** \param Version Version string.
    **/
    void VersionSlot(QString Version);

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
    *** \brief Information panel timer.
    *** \details Timer used to update the information panel display.
    **/
    QTimer *m_pInformationPanelTimer;

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
    *** \brief Start up flag.
    *** \details If true, the control panel dialog has not completed
    ***   initialization.
    **/
    bool m_StartUpFlag;

    /**
    *** \brief First update flag.
    *** \details If true, the application has yet to download the current
    ***   version file from the internet.
    **/
    bool m_FirstUpdateFlag;

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

    /**
    *** \brief Information panel dialog box.
    *** \details Dialog box for the information panel.
    **/
    INFORMATIONPANELDIALOG_C *m_pInformationPanelDialog;

    /**
    *** \brief Next update check.
    *** \details Date to next check for a program update.
    **/
    QDate m_NextUpdateCheck;

    /**
    *** \brief Program update checker.
    *** \details Checks for program updates.
    **/
    UPDATENOTIFIER_C m_UpdateNotifier;

    /**
    *** \brief Double click timout timer.
    *** \details Timer used to differentiate between one or two clicks and a
    ***   double click.
    **/
    QTimer *m_pDoubleClickTimeoutTimer;

#ifdef    DEBUG
    /**
    *** \brief Test widget.
    *** \details A test widget used for testing/debugging.
    **/
    TESTWIDGET_C *m_pTestWidget;
#endif    /* DEBUG */
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
