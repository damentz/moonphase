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
#include  "options.h"
#include  "informationpaneldialog.h"
#include  "settings.h"
#include  "information.h"
#include  "informationoptionsdialog.h"
#include  "versionstring.h"

#include  <QDesktopWidget>
#include  <QMenu>
#include  <QTimer>
#include  <QMessageBox>
#include  <QPainter>


/****
*****
***** DEFINES
*****
****/

/**
*** \brief Animation update rate.
*** \details Time between animation updates.
**/
#define   ANIMATIONTIMER_RATE     (200)         /* in milliseconds */

/**
*** \brief Icon update rate.
*** \details Time between checks for any icon updates.
**/
#define   UPDATETIMER_RATE        (60*60*1000)  /* 1 hour, in milliseconds */

/**
*** \brief Information panel update rate.
*** \details Time between checks for information panel updates.
**/
#define   INFORMATIONPANELTIMER_RATE  (1000)    /* 1 second, in milliseconds */

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


/****
*****
***** DATA TYPES
*****
****/

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
    *** \brief Return information index.
    *** \details Returns the index into the information table.
    *** \returns Index into the information table.
    **/
    int GetInformationIndex(void);

    /**
    *** \brief Return item options.
    *** \details Returns the options for this item.
    *** \returns Options for this line.
    **/
    void GetOptions(OPTIONS_C &Options);

    /**
    *** \brief Return unit or format index.
    *** \details Returns the index into the unit table or the index of the
    ***   date/time format.
    *** \returns Index into the unit table.
    **/
    int GetUnitFormatIndex(void);

    /**
    *** \brief Set information index.
    *** \details Sets the index into the information table.
    *** \param Index Index into the information table.
    **/
    void SetInformationIndex(int Index);

    /**
    *** \brief Set item options.
    *** \details Sets the options for this item.
    *** \param Options Line Options.
    **/
    void SetOptions(OPTIONS_C const &Options);

    /**
    *** \brief Set unit or format index.
    *** \details Sets the index into the unit table or the index of the
    ***   date/time format.
    *** \param Index into the unit table.
    **/
    void SetUnitFormatIndex(int Index);

  private:
    /**
    *** \brief Information index.
    *** \details The index into the information table.
    **/
    int m_InformationIndex;

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

INFORMATIONITEM_C::INFORMATIONITEM_C(void)
{
  DEBUGLOG_Printf0("INFORMATIONITEM_C::INFORMATIONITEM_C()");
  DEBUGLOG_LogIn();

  m_InformationIndex=-1;

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

int INFORMATIONITEM_C::GetInformationIndex(void)
{
  DEBUGLOG_Printf0("INFORMATIONITEM_C::GetInformationIndex()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_InformationIndex);
}

void INFORMATIONITEM_C::GetOptions(OPTIONS_C &Options)
{
  DEBUGLOG_Printf1("INFORMATIONITEM_C::GetOptions(%p)",&Options);
  DEBUGLOG_LogIn();

  Options=m_Options;

  DEBUGLOG_LogOut();
  return;
}

int INFORMATIONITEM_C::GetUnitFormatIndex(void)
{
  DEBUGLOG_Printf0("INFORMATIONITEM_C::GetUnitFormatIndex()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_Options.GetUnitFormatIndex());
}

void INFORMATIONITEM_C::SetInformationIndex(int Index)
{
  DEBUGLOG_Printf1("INFORMATIONITEM_C::SetInformationIndex(%d)",Index);
  DEBUGLOG_LogIn();

  m_InformationIndex=Index;

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

void INFORMATIONITEM_C::SetUnitFormatIndex(int Index)
{
  DEBUGLOG_Printf1("INFORMATIONITEM_C::SetUnitFormatIndex(%d)",Index);
  DEBUGLOG_LogIn();

  m_Options.SetUnitFormatIndex(Index);

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
  m_PreviewPercentCounter=0;
  m_UpdateIntervalCounter=0;
  m_CloseReminderIssued=false;
  m_StartUpFlag=true;
  m_FirstUpdateFlag=true;
  m_NextUpdateCheck=QDate::currentDate();
  m_pDoubleClickTimeoutTimer=NULL;

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
  m_pAboutWidget->ShowCheckForUpdateWidget(true);

  /* Create and set up the animation timer. */
  m_pAnimationTimer=new QTimer(this);
  connect(m_pAnimationTimer,SIGNAL(timeout()),
      this,SLOT(AnimationTimerTriggeredSlot()));

  /* Create and set up the information panel timer. */
  m_pInformationPanelTimer=new QTimer(this);
  connect(m_pInformationPanelTimer,SIGNAL(timeout()),
      this,SLOT(InformationPanelTimerTriggeredSlot()));

  m_pDoubleClickTimeoutTimer=new QTimer(this);
  m_pDoubleClickTimeoutTimer->setSingleShot(true);
  connect(m_pDoubleClickTimeoutTimer,SIGNAL(timeout()),
      this,SLOT(DoubleClickTimeoutTimerTriggered()));

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
  {
    int Index;
    char const *pLabel;

    Index=0;
    goto IntoLoop;
    while(pLabel!=NULL)
    {
      m_pDataListWidget->addItem(pLabel);
      Index++;
IntoLoop:
      /*pLabel=*/Information_GetLabel(Index,&pLabel);
    }
  }

  /* Resize the control panel to minimum size. */
  resize(minimumSizeHint());

  connect(&m_UpdateNotifier,SIGNAL(VersionSignal(QString)),
      this,SLOT(VersionSlot(QString)));
  m_UpdateNotifier.SetURL(
      "http://downloads.sourceforge.net/project/moonphase/current_release");

  m_StartUpFlag=false;

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
  m_DateTimeOverrideFlag=false;
  m_pTabWidget->addTab(m_pTestWidget,QIcon(":/WidgetIcons/TestIcon"),"&Test");
  m_pTestWidget->m_pDateTimeEdit->setDateTime(QDateTime::currentDateTime());
  connect(m_pTestWidget->m_pDateTimeGroupBox,SIGNAL(clicked()),
      this,SLOT(DateTimeGroupBoxClickedSlot()));
  connect(m_pTestWidget->m_pDateTimeEdit,SIGNAL(dateTimeChanged(QDateTime)),
      this,SLOT(DateTimeChangedSlot(QDateTime)));
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
  QString Information;


  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::InitializeAboutTab()");
  DEBUGLOG_LogIn();

  /* Set the data in the various widgets. */
  m_pAboutWidget->SetDisplayName(MOONPHASEQT_DISPLAYNAME);
  m_pAboutWidget->SetExecutableName(MOONPHASEQT_EXECUTABLENAME);
  m_pAboutWidget->SetVersion(MOONPHASEQT_VERSION);
  Information=MOONPHASEQT_DESCRIPTION;
  Information+="<br><br>"MOONPHASEQT_COPYRIGHTNOTICE;
#ifdef    _WIN32
  Information+="<br><br>"+QString(tr("Statically linked with Qt (Version "))
      +qVersion()+QString(tr(")\n"));
#endif    /* _WIN32 */
  Information+="<br><br><a href=\""MOONPHASEQT_WEBSITE"\">"" \
    "MOONPHASEQT_DISPLAYNAME" "+tr("Web Site")+QString("</a>\n");
  m_pAboutWidget->SetInformation(Information);

  m_pAboutWidget->SetLicense(f_pLicenseAgreement);

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
  m_pAllowMultipleInstancesCheckBox->setChecked(
      m_pSettings->GetAllowMultipleInstancesFlag());
  m_pAnimationFilenameChooser->setText(m_pSettings->GetAnimationPathname());
  m_pBackgroundColorButton->setCurrentColor(m_pSettings->GetBackgroundColor());
  m_pConfirmDiscardCheckBox->setChecked(m_pSettings->GetConfirmDiscardFlag());
  m_pConfirmQuitCheckBox->setChecked(m_pSettings->GetConfirmQuitFlag());
  m_pImperialUnitsRadioButton->setChecked(
      !m_pSettings->GetDefaultToMetricUnitsFlag());
  m_pLatitudeSpinBox->setValue(m_pSettings->GetLatitude());
  m_pLongitudeSpinBox->setValue(m_pSettings->GetLongitude());
  m_pMetricUnitsRadioButton->setChecked(
      m_pSettings->GetDefaultToMetricUnitsFlag());
  m_pRemindOncePerSessionCheckBox->setChecked(
      m_pSettings->GetRemindOncePerSessionFlag());
  m_pStillRunningReminder->setChecked(
      m_pSettings->GetStillRunningReminderFlag());
  m_pUpdateIntervalSpinBox->setValue(m_pSettings->GetUpdateInterval());
  m_pUseOpaqueBackgroundGroupBox->setChecked(
      m_pSettings->GetUseOpaqueBackgroundFlag());

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
  pSettings->SetAllowMultipleInstancesFlag(
      m_pAllowMultipleInstancesCheckBox->isChecked());
  pSettings->SetAnimationPathname(m_pAnimationFilenameChooser->text());
  pSettings->SetBackgroundColor(m_pBackgroundColorButton->currentColor());
  pSettings->SetConfirmDiscardFlag(m_pConfirmDiscardCheckBox->isChecked());
  pSettings->SetConfirmQuitFlag(m_pConfirmQuitCheckBox->isChecked());
  pSettings->SetDefaultToMetricUnitsFlag(
      m_pMetricUnitsRadioButton->isChecked());
  pSettings->SetLatitude(m_pLatitudeSpinBox->value());
  pSettings->SetLongitude(m_pLongitudeSpinBox->value());
  pSettings->SetRemindOncePerSessionFlag(
      m_pRemindOncePerSessionCheckBox->isChecked());
  pSettings->SetStillRunningReminderFlag(m_pStillRunningReminder->isChecked());

  pSettings->SetUpdateInterval(m_pUpdateIntervalSpinBox->value());
  pSettings->SetUseOpaqueBackgroundFlag(
      m_pUseOpaqueBackgroundGroupBox->isChecked());

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::RecalculateMoonData(time_t Time)
{
  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::RecalculateMoonData(%1)",time);
  DEBUGLOG_LogIn();

  /* Recalculate the astronomical data. */
#ifdef    DEBUG
  if (m_DateTimeOverrideFlag==true)
    MoonData_Recalculate(&m_MoonData,m_DateTimeOverride.toTime_t());
  else
#endif    /* DEBUG */
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

      if (m_pDisplayListWidget->selectedItems().count()==1)
        EnableOptionsFlag=true;
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
  int InfoItemIndex;
  char const *pLabel;
  QListWidgetItem *pLWItem;
  INFORMATIONITEM_C *pIItem;
  int Index;


  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::AddDataItemButtonClickedSlot()");
  DEBUGLOG_LogIn();

  foreach(pSelectedItem,m_pDataListWidget->selectedItems())
  {
    /* Add a row at the end of the display list widget. */
    InfoItemIndex=m_pDataListWidget->row(pSelectedItem);
    /*pLabel=*/Information_GetLabel(InfoItemIndex,&pLabel);
    if (pLabel==NULL)
    {
      MESSAGELOG_Error("Invalid item label index.");
    }
    else
      m_pDisplayListWidget->addItem(pLabel);

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

      /* The information item index is the same as the row index. */
      pIItem->SetInformationIndex(InfoItemIndex);

      /* Get the default unit/format index. */
      Information_GetDefaultUnitFormatIndex(
          InfoItemIndex,m_pImperialUnitsRadioButton->isChecked()==true,&Index);
      pIItem->SetUnitFormatIndex(Index);
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
      &m_MoonPreviewImages,
      qPrintable(m_pAnimationFilenameChooser->text()))<0) &&
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
    default:
      MESSAGELOG_Error("Invalid button.");
      break;
  }

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::CheckButtonClickedSlot(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::CheckButtonClickedSlot()");
  DEBUGLOG_LogIn();

  m_pAboutWidget->SetUpdateText(tr("Checking for an update!"));
  m_UpdateNotifier.CheckForUpdate();

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
      m_pDoubleClickTimeoutTimer->stop();
      SetVisible(true);
      break;
    case QSystemTrayIcon::Trigger:
      if (m_pDoubleClickTimeoutTimer->isActive()==true)
        return;
      m_pDoubleClickTimeoutTimer->setInterval(
          QApplication::doubleClickInterval());
      m_pDoubleClickTimeoutTimer->start();
      break;
    default:
      break;
  }

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

void CONTROLPANELDIALOG_C::DateTimeChangedSlot(QDateTime DateTime)
{
  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::DateTimeChanged(%p)",&DateTime);
  DEBUGLOG_LogIn();

#ifdef    DEBUG
  m_DateTimeOverride=DateTime;

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

void CONTROLPANELDIALOG_C::
    DoubleClickTimeoutTimerTriggered(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::DoubleClickTimeoutTimerTriggered()");
  DEBUGLOG_LogIn();

  ShowInformationPanelSlot();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::InformationPanelTimerTriggeredSlot(void)
{
  QListWidgetItem *pLWItem;
  QString Text;
  INFORMATIONITEM_C *pIItem;
  OPTIONS_C Options;


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
    RecalculateMoonData(time(NULL));

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
          OPTIONS_C Options;
          DATETIMEOPTIONS_T DTOptions;
          MOONDATAPRINTOPTIONS_T MDPOptions;
          char *pPtr;

          pIItem->GetOptions(Options);
          Options.Convert(&DTOptions);
          memcpy(&MDPOptions,&DTOptions,sizeof(MDPOptions));
          Information_Print(&m_MoonData,pIItem->GetInformationIndex(),
              pIItem->GetUnitFormatIndex(),&MDPOptions,&pPtr);

          m_pInformationPanelDialog->SetLine(Index,QString::fromUtf8(pPtr),Options);
          if (pPtr!=NULL)
            free(pPtr);
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
  PreferencesChangedSlot();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::LongitudeChangedSlot(double Longitude)
{
  DEBUGLOG_Printf1("CONTROLPANELDIALOG_C::LongitudeChangedSlot(%f)",Longitude);
  DEBUGLOG_LogIn();

  m_MoonData.CTransData.Glon=-Longitude;
  MoonData_Recalculate(&m_MoonData,time(NULL));
  PreferencesChangedSlot();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::DateTimeGroupBoxClickedSlot(void)
{
  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::DateTimeGroupBoxClickedSlot()");
  DEBUGLOG_LogIn();

#ifdef    DEBUG
  m_DateTimeOverrideFlag=m_pTestWidget->m_pDateTimeGroupBox->isChecked();
  if (m_DateTimeOverrideFlag==false)
    m_pTestWidget->m_pDateTimeEdit->setDateTime(QDateTime::currentDateTime());
  m_DateTimeOverride=m_pTestWidget->m_pDateTimeEdit->dateTime();
  DateTimeChangedSlot(m_DateTimeOverride);
#endif    /* DEBUG */

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

  /* Update the display. */
  InformationPanelTimerTriggeredSlot();

  DEBUGLOG_LogOut();
  return;
}

void CONTROLPANELDIALOG_C::OptionsDisplayItemButtonClickedSlot(void)
{
  QListWidgetItem *pLWItem;
  INFORMATIONITEM_C *pIItem;
  int Index;
  char *pPtr;
  QList<QString> List;
  INFORMATIONOPTIONSDIALOG_C::DIALOGDATA_T DialogData;
  OPTIONS_C Options;
  INFORMATIONOPTIONSDIALOG_C OptionsDialog(this);


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
      Index=0;
      goto Start0;
      while(pPtr!=NULL)
      {
        List.append(QString::fromUtf8(pPtr));
        free(pPtr);
        Index++;
Start0:
        Information_GetUnitFormatDescription(
            pIItem->GetInformationIndex(),Index,&pPtr);
      }

      DialogData.DescriptionList=List;

      List.clear();
      Index=0;
      goto Start1;
      while(pPtr!=NULL)
      {
        List.append(QString::fromUtf8(pPtr));
        free(pPtr);
        Index++;
Start1:
        Information_GetFormat(pIItem->GetInformationIndex(),Index,&pPtr);
      }

      DialogData.FormatsList=List;

      /* Set the mode. */
      EDITMODE_T EditMode;
      Information_GetEditMode(pIItem->GetInformationIndex(),&EditMode);
      DialogData.EditMode=EditMode;

      /* Set the options in the dialog box. */
      pIItem->GetOptions(Options);
      DialogData.Options=Options;

      /* Set the dialog data. */
      OptionsDialog.SetData(DialogData);

      /* Catch the signal from the Apply button. */
      connect(&OptionsDialog,SIGNAL(OptionsAppliedSignal(OPTIONS_C const &)),
          this,SLOT(OptionsAppliedSlot(OPTIONS_C const &)));

      /* Show the dialog box. */
      if (OptionsDialog.exec()==QDialog::Accepted)
      {
        /* Accepted. */

        /* Copy the options. */
        OptionsDialog.GetOptions(Options);
        pIItem->SetOptions(Options);

        /* Update the display. */
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

void CONTROLPANELDIALOG_C::RemoveDisplayItemButtonClickedSlot(void)
{
  QListWidgetItem *pSelectedItem;
  QListWidgetItem *pItem;
  int Row;


  DEBUGLOG_Printf0("CONTROLPANELDIALOG_C::RemoveDisplayItemButtonClickedSlot()");
  DEBUGLOG_LogIn();

  foreach(pSelectedItem,m_pDisplayListWidget->selectedItems())
  {
    Row=m_pDisplayListWidget->row(pSelectedItem);
    pItem=m_pDisplayListWidget->takeItem(Row);
    if (pItem==NULL)
    {
      MESSAGELOG_Error("NULL item pointer.");
    }
    delete pItem;
  }
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

  if (m_pInformationPanelDialog->isVisible()==false)
    m_pInformationPanelTimer->start(INFORMATIONPANELTIMER_RATE);
  m_pInformationPanelDialog->show();
  m_pInformationPanelDialog->raise();
  m_pInformationPanelDialog->activateWindow();

  /* Update the display. */
  InformationPanelTimerTriggeredSlot();

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
    m_NextUpdateCheck=m_NextUpdateCheck.addDays(7);
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

void CONTROLPANELDIALOG_C::VersionSlot(QString Version)
{
  VERSIONSTRING_C Current(MOONPHASEQT_VERSION);
  VERSIONSTRING_C Internet;//(qPrintable(Version));


  DEBUGLOG_Printf2(
      "CONTROLPANELDIALOG_C::VersionSlot(%p(%s))",&Version,qPrintable(Version));
  DEBUGLOG_LogIn();

  if (Version.isEmpty()==true)
    m_pAboutWidget->SetUpdateText(tr("Error accessing the internet!"));
  else
  {
    Internet.Set(qPrintable(Version));
    if (Current>Internet)
      m_pAboutWidget->SetUpdateText(tr("You have a pre-release version!"));
    else if (Current==Internet)
      m_pAboutWidget->SetUpdateText(tr("This program is up to date!"));
    else
    {
      m_pAboutWidget->SetUpdateText(tr("An update is available!"));

      if (m_FirstUpdateFlag==true)
      {
        QMessageBox UpdateMessageBox(this);


        UpdateMessageBox.setWindowTitle(MOONPHASEQT_DISPLAYNAME);
        UpdateMessageBox.setTextFormat(Qt::RichText); // Makes links clickable
        UpdateMessageBox.setText(tr("An update to this program is available!"
            "<br><br>"
            "Visit the <a href='"MOONPHASEQT_WEBSITE"'>"
            MOONPHASEQT_DISPLAYNAME" Web Site</a>"));
        UpdateMessageBox.exec();
      }
    }
    m_FirstUpdateFlag=false;
  }

  DEBUGLOG_LogOut();
  return;
}


#undef    CONTROLPANELDIALOG_CPP
