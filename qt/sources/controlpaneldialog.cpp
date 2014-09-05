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
*** \file controlpaneldialog.cpp
*** \brief controlpaneldialog.h implementation.
*** \details Implementation file for controlpaneldialog.h.
**/


/** Identifier for CONTROLPANELDIALOG.cpp. **/
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
#include  "../licenseagreement.h"

#ifdef    DEBUG
#include  <time.h>
#endif    /* DEBUG */
#include  <QtGui>


/****
*****
***** DEFINES
*****
****/

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
#define   UPDATETIMER_RATE        (4*60*60*1000)  /* 4 hours, in milliseconds */

/**
*** \brief Binary subdirectory.
*** \details Subdirectory containing the executable.
**/
#define   DIRECTORY_BINARY  "/bin"

/**
*** \brief Image subdirectory.
*** \details Subdirectory containing the moonphase images.
**/
#define   DIRECTORY_IMAGES  "/share/moonphase"

/**
*** \brief Default animation.
*** \details Filename of the default animation.
**/
#define   FILENAME_IMAGE    "moon_56frames.png"


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

SETTINGS_C::SETTINGS_C(void)
{
  DEBUGLOG_Printf0("SETTINGS_C::SETTINGS_C()");
  DEBUGLOG_LogIn();

  m_AnimationPathname="";
  m_BackgroundColor=QColor(0,0,0);
  m_ConfirmDiscardFlag=true;
  m_ConfirmQuitFlag=true;
  m_RemindOncePerSessionFlag=true;
  m_StillRunningReminderFlag=true;
  m_UpdateInterval=24;
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
      (m_UpdateInterval==RHS.m_UpdateInterval) &&
      (m_UseOpaqueBackgroundFlag==RHS.m_UseOpaqueBackgroundFlag) &&
      (m_BackgroundColor==RHS.m_BackgroundColor) &&
      (m_StillRunningReminderFlag==RHS.m_StillRunningReminderFlag) &&
      (m_RemindOncePerSessionFlag==RHS.m_RemindOncePerSessionFlag) &&
      (m_ConfirmDiscardFlag==RHS.m_ConfirmDiscardFlag) &&
      (m_ConfirmQuitFlag==RHS.m_ConfirmQuitFlag);

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

  m_AnimationPathname=
      value(PREFERENCES_ANIMATIONPATHNAME,m_AnimationPathname).toString();
  m_BackgroundColor=
      value(PREFERENCES_BACKGROUNDCOLOR,m_BackgroundColor).value<QColor>();
  m_ConfirmDiscardFlag=value(
      PREFERENCES_CONFIRMDISCARDCHANGESFLAG,m_ConfirmDiscardFlag).toBool();
  m_ConfirmQuitFlag=
      value(PREFERENCES_CONFIRMQUITFLAG,m_ConfirmQuitFlag).toBool();
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

void SETTINGS_C::Save(void)
{
  DEBUGLOG_Printf0("SETTINGS_C::Save()");
  DEBUGLOG_LogIn();

  setValue(PREFERENCES_ANIMATIONPATHNAME,m_AnimationPathname);
  setValue(PREFERENCES_BACKGROUNDCOLOR,m_BackgroundColor);
  setValue(PREFERENCES_CONFIRMDISCARDCHANGESFLAG,m_ConfirmDiscardFlag);
  setValue(PREFERENCES_CONFIRMQUITFLAG,m_ConfirmQuitFlag);
  setValue(PREFERENCES_USEOPAQUEBACKGROUNDFLAG,m_UseOpaqueBackgroundFlag);
  setValue(PREFERENCES_REMINDONCEPERSESSIONFLAG,m_RemindOncePerSessionFlag);
  setValue(PREFERENCES_STILLRUNNINGREMINDERFLAG,m_StillRunningReminderFlag);
  setValue(PREFERENCES_UPDATEINTERVAL,m_UpdateInterval);

  DEBUGLOG_LogOut();
  return;
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

bool SETTINGS_C::GetRemindOncePerSessionFlag(void) const
{
  DEBUGLOG_Printf0("SETTINGS_C::GetRemindOncePerSessionFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_RemindOncePerSessionFlag);
}

bool SETTINGS_C::GetStillRunningReminderFlag(void) const
{
  DEBUGLOG_Printf0("SETTINGS_C::GetStillRunningReminderFlag()");
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
  DEBUGLOG_Printf0("SETTINGS_C::GetUseOpaqueBackgroundFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_UseOpaqueBackgroundFlag);
}

void SETTINGS_C::SetAnimationPathname(QString const Pathname)
{
  DEBUGLOG_Printf2("SETTINGS_C::SetAnimationPathname(%p(%s))",
      &Pathname,qPrintable(Pathname));
  DEBUGLOG_LogIn();

  m_AnimationPathname=Pathname;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::SetBackgroundColor(QColor const BackgroundColor)
{
  DEBUGLOG_Printf1(
      "SETTINGS_C::SetBackgroundColor(%u)",BackgroundColor.value());
  DEBUGLOG_LogIn();

  m_BackgroundColor=BackgroundColor;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::SetConfirmDiscardFlag(bool const ConfirmDiscardFlag)
{
  DEBUGLOG_Printf1("SETTINGS_C::SetConfirmDiscardFlag(%u)",ConfirmDiscardFlag);
  DEBUGLOG_LogIn();

  m_ConfirmDiscardFlag=ConfirmDiscardFlag;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::SetConfirmQuitFlag(bool const ConfirmQuitFlag)
{
  DEBUGLOG_Printf1("SETTINGS_C::SetConfirmQuitFlag(%u)",ConfirmQuitFlag);
  DEBUGLOG_LogIn();

  m_ConfirmQuitFlag=ConfirmQuitFlag;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::SetRemindOncePerSessionFlag(bool const OnceFlag)
{
  DEBUGLOG_Printf1("SETTINGS_C::SetRemindOncePerSessionFlag(%u)",OnceFlag);
  DEBUGLOG_LogIn();

  m_RemindOncePerSessionFlag=OnceFlag;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::SetStillRunningReminderFlag(bool const ReminderFlag)
{
  DEBUGLOG_Printf1("SETTINGS_C::SetStillRunningReminderFlag(%u)",ReminderFlag);
  DEBUGLOG_LogIn();

  m_StillRunningReminderFlag=ReminderFlag;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::SetUpdateInterval(unsigned int const Interval)
{
  DEBUGLOG_Printf1("SETTINGS_C::SetUpdateInterval(%u)",Interval);
  DEBUGLOG_LogIn();

  m_UpdateInterval=Interval;

  DEBUGLOG_LogOut();
  return;
}

void SETTINGS_C::SetUseOpaqueBackgroundFlag(bool const UseFlag)
{
  DEBUGLOG_Printf1("SETTINGS_C::SetUseOpaqueBackgroundFlag(%u)",UseFlag);
  DEBUGLOG_LogIn();

  m_UseOpaqueBackgroundFlag=UseFlag;

  DEBUGLOG_LogOut();
  return;
}

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
  m_pAnimationTimer=NULL;
  m_pUpdateTimer=NULL;
  m_pSettings=NULL;
  m_PreviewPercentCounter=0;
  m_UpdateIntervalCounter=0;
  m_CloseReminderIssued=false;

  /* Set up the user interface. */
  setupUi(this);

  /* Set window title. */
  setWindowTitle(MOONPHASEQT_DISPLAYNAME_STRING);

  /* Add minimize button. */
  setWindowFlags(Qt::Window);

  /* Because of above call, window starts in odd places. Center it instead. */
  move(QPoint(
    (QApplication::desktop()->width()-frameGeometry().width())/2,
    (QApplication::desktop()->height()-frameGeometry().height())/2));

  /* Disable help (temporarily). */
  m_pButtonBox->button(QDialogButtonBox::Help)->setEnabled(false);

  /* Create and set up the tray icon context menu. */
  m_pTrayIconMenu = new QMenu(this);
  m_pTrayIconMenu->addAction(m_pShowControlPanelAction);
  m_pTrayIconMenu->addSeparator();
  m_pTrayIconMenu->addAction(m_pQuitAction);

  /* Create and set up the tray icon. */
  m_pTrayIcon=new QSystemTrayIcon(this);
  m_pTrayIcon->setContextMenu(m_pTrayIconMenu);
  connect(m_pTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
      this,SLOT(ControlPanelActivatedSlot(QSystemTrayIcon::ActivationReason)));

  /* Connect the quit action to the quit slot. */
  connect(m_pQuitAction,SIGNAL(triggered()),this,SLOT(QuitSlot()));

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

  if (ErrorCode<0)
  {
    ControlPanelActivatedSlot(QSystemTrayIcon::DoubleClick);
    QMessageBox::warning(this,tr(MOONPHASEQT_DISPLAYNAME_STRING),
        tr("Unable to load moon animation. Please select a new file."));
    ErrorCode=ERRORCODE_SUCCESS;  /* "Error" handled. */
  }

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
    if (QMessageBox::question(this,tr(MOONPHASEQT_DISPLAYNAME_STRING),
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
    QMessageBox::information(this,tr(MOONPHASEQT_DISPLAYNAME_STRING),
        tr("The program will continue to run in the system tray. To stop it, "
        "right click the system tray icon and select <b>Quit</b>."));
    if (m_pSettings->GetRemindOncePerSessionFlag()==true)
      m_CloseReminderIssued=true;
  }
  SetVisible(false);
  pEvent->ignore();

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

void CONTROLPANELDIALOG_C::InitializeAboutTab(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::InitializeAboutTab()");
  DEBUGLOG_LogIn();

  /* Set the data in the various widgets. */
  m_pProgramNameLabel->setText(MOONPHASEQT_DISPLAYNAME_STRING);
  m_pExecutableNameVersionLabel->setText(MOONPHASEQT_EXECUTABLENAME_STRING
      " (Version "MOONPHASEQT_VERSION_STRING")");
  m_pProgramInformationEdit->setText(MOONPHASEQT_DESCRIPTION_STRING"\n");
  m_pProgramInformationEdit->append(MOONPHASEQT_COPYRIGHTNOTICE_STRING"\n");
  m_pProgramInformationEdit->append("<a href=\""MOONPHASEQT_WEBSITE_STRING"\">"
      MOONPHASEQT_WEBSITE_STRING"</a>");
  m_pLicenseAgreementEdit->setText(f_pLicenseAgreement);

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

void CONTROLPANELDIALOG_C::AnimationPathnameChangedSlot(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::AnimationPathnameChangedSlot()");
  DEBUGLOG_LogIn();

  /* Try to load the file.  Don't care about return value. */
  MoonAnimation_ReadFile(
      &m_MoonPreviewImages,qPrintable(m_pAnimationFilenameChooser->text()));
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
  PercentString.sprintf("%d%%",m_PreviewPercentCounter);
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
          m_pSettings->GetBackgroundColor()) )
      {
        if (m_pAnimationFilenameChooser->text()!=
            m_pSettings->GetAnimationPathname())
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

void CONTROLPANELDIALOG_C::ControlPanelActivatedSlot(
    QSystemTrayIcon::ActivationReason Reason)
{
  DEBUGLOG_Printf1(
      "CONTROLPANELDIALOG_C::ControlPanelActivatedSlot(%d)",Reason);
  DEBUGLOG_LogIn();

  switch(Reason)
  {
    case QSystemTrayIcon::DoubleClick:
      SetVisible(true);
      break;
    default:
      break;
  }

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::HelpButtonClickedSlot(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::HelpButtonClickedSlot()");
  DEBUGLOG_LogIn();

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
    if (QMessageBox::question(this,MOONPHASEQT_DISPLAYNAME_STRING,
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

void CONTROLPANELDIALOG_C::ShowControlPanelSlot(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::ShowControlPanelSlot()");
  DEBUGLOG_LogIn();

  ControlPanelActivatedSlot(QSystemTrayIcon::DoubleClick);

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
  QString PercentString;
  QPixmap Pixmap;


  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::UpdateTimerTriggeredSlot()");
  DEBUGLOG_LogIn();

  /* Check if calculations need to be run, and (possibly) the icon updated. */
  m_UpdateIntervalCounter++;
  if (m_UpdateIntervalCounter>=(m_pSettings->GetUpdateInterval()))
  {
#ifdef    DEBUG
    {
      time_t TimeSeconds1970;
      struct tm *pTimeInfo;
      char pPtr[1024];


      time(&TimeSeconds1970);
      pTimeInfo=localtime(&TimeSeconds1970);
      strftime(pPtr,1024,"%H:%M:%S",pTimeInfo);
      MESSAGELOG_Info(pPtr);
    }
#endif    /* DEBUG */

    /* Recalculate the astronomical data. */
    MoonData_Recalculate(&m_MoonData);

    /* Update the icon. */
    Pixmap=DrawFrame(&m_MoonTrayImages,
        MoonData_GetMoonPhasePercent(&m_MoonData),
        m_pSettings->GetUseOpaqueBackgroundFlag(),
        m_pSettings->GetBackgroundColor());
    m_pTrayIcon->setIcon(Pixmap);

    m_UpdateIntervalCounter=0;
  }

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


#undef    CONTROLPANELDIALOG_CPP
