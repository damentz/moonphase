/*
** This file is part of toolbox.
** Copyright (C) 2008-2015 by Alan Wise (alanwise@users.sourceforge.net)
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
*** \file debugtools.cpp
*** \brief debugtools.cpp implementation file.
*** \details Implementation file for debugtools.cpp.
**/


/** Identifier for debugtools.cpp. **/
#define   DEBUGTOOLS_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "debugtools.h"
#include  "debugtools_private.h"
#define   DEBUGLOG_NOWRAPPERMACROS
#include  "debuglog.h"
#define   MESSAGELOG_NOWRAPPERMACROS
#include  "messagelog.h"

#include  <QMainWindow>
#include  <QToolBar>
#include  <QSettings>
#include  <QPushButton>
#include  <QToolBar>
#include  <QMainWindow>


/****
*****
***** DEFINES
*****
****/

/**
*** \brief Debug log and message log poll delay.
*** \details How often to check for debug log and message log modifications.
**/
#define   DELAY_CHECKMODIFICATIONTIME           (1000)  /* 1 second */

/**
*** \brief Debug console array key.
*** \details Configuration file array key name for the debug console.
**/
#define   OPTION_ARRAY_NAME                     "DebugConsole"

/**
*** \brief Alway on top key.
*** \details Configuration file key name for the console always on top
***   preference.
**/
#define   OPTION_KEY_CONSOLEALWAYSONTOP         "AlwaysOnTop"
/**
*** \brief Display on startup key.
*** \details Configuration file key name for the console display on startup
***   preference.
**/
#define   OPTION_KEY_CONSOLEDISPLAYONSTARTUP    "DisplayOnStartup"
/**
*** \brief Window position key.
*** \details Configuration file key name for the console window position
***   preference.
**/
#define   OPTION_KEY_CONSOLEWINDOWPOSITION      "WindowPosition"
/**
*** \brief Window size key.
*** \details Configuration file key name for the console window size preference.
**/
#define   OPTION_KEY_CONSOLEWINDOWSIZE          "WindowSize"
/**
*** \brief Debug log autorefresh key.
*** \details Configuration file key name for the debug log auto refresh
***   preference.
**/
#define   OPTION_KEY_DEBUGLOGAUTOREFRESH        "DebugLogAutoRefresh"
/**
*** \brief Message log autorefresh key.
*** \details Configuration file key name for the message log auto refresh
***   preference.
**/
#define   OPTION_KEY_MESSAGELOGAUTOREFRESH      "MessageLogAutoRefresh"
/**
*** \brief Message log merge duplicates key.
*** \details Configuration file key name for the message log merge duplicates
***   preference.
**/
#define   OPTION_KEY_MESSAGELOGMERGEDUPLICATES  "MessageLogMergeDuplicates"
/**
*** \brief Message log remove paths key.
*** \details Configuration file key name for the message log remove paths
***   preference.
**/
#define   OPTION_KEY_MESSAGELOGREMOVEPATHS      "MessageLogRemovePaths"

/**
*** \brief Message log tab index.
*** \details Index of the message log tab in the debug console dialog.
***/
#define   CONSOLETAB_MESSAGELOG   (0)
/**
*** \brief Debug log tab index.
*** \details Index of the debug log tab in the debug console dialog.
***/
#define   CONSOLETAB_DEBUGLOG     (1)

/**
*** \brief Options options tab index.
*** \details Index of the options tab in the debug tools options dialog.
***/
#define   OPTIONSTAB_OPTIONS      (0)
/**
*** \brief Message log options tab index.
*** \details Index of the message log tab in the debug tools options dialog.
***/
#define   OPTIONSTAB_MESSAGELOG   (1)
/**
*** \brief Debug log options tab index.
*** \details Index of the debug log tab in the debug tools options dialog.
***/
#define   OPTIONSTAB_DEBUGLOG     (2)


/****
*****
***** DATA TYPES
*****
****/

/**
*** \brief Debug/test button data.
*** \details Structure used to create debug/test buttons.
**/
struct structBUTTONDATA
{
  /**
  *** \brief Tool type.
  *** \details The type of tool associated with this button.
  **/
  DEBUGTOOLS_F ToolTypes;
  /**
  *** \brief Icon name.
  *** \details Name of icon to use for button.
  **/
  char const *pIconName;
  /**
  *** \brief Display name.
  *** \details Name to display.
  **/
  char const *pActionName;
  /**
  *** \brief 'triggered()' slot.
  *** \details Slot to handle 'triggered()' signal.
  **/
  char const *pSlot;
  /**
  *** \brief Separator flag.
  *** \details In certain instances, use a separator.
  **/
  bool SeparatorFlag;
};


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

/**
*** \brief Debug/test/console button definitions.
*** \details Definitions of the debug/test/console buttons. Specifies
***   group, icon, name, and signal emitted. Technically, the slot is both a
***   slot and a signal, but naming them as signals seems more logical to the
***   end user.
**/
struct structBUTTONDATA m_pDebugTestConsoleButtonList[]=
{
  {
    DEBUGBUTTONS,":/DebugConsole/Debug1Icon","Debug1",
        SIGNAL(Debug1ButtonClickedSignal()),0
  },
  {
    DEBUGBUTTONS,":/DebugConsole/Debug2Icon","Debug2",
        SIGNAL(Debug2ButtonClickedSignal()),0
  },
  {
    TESTBUTTONS,":/DebugConsole/Test1Icon","Test1",
        SIGNAL(Test1ButtonClickedSignal()),0
  },
  {
    TESTBUTTONS,":/DebugConsole/Test2Icon","Test2",
        SIGNAL(Test2ButtonClickedSignal()),0
  },
  {
    DEBUGLOG|MESSAGELOG,":/DebugConsole/DebugConsoleIcon","Debug console",
        SLOT(DebugConsoleButtonClickedSlot()),!0
  },
  { NONE,NULL,NULL,NULL,0 }
};


/****
*****
***** VARIABLES
*****
****/

/**
*** \brief Instance.
*** \details Debug tools instance.
**/
DEBUGTOOLS_C *f_pDebugTools;













/****
*****
***** FUNCTIONS
*****
****/






DEBUGTOOLS_C::DEBUGTOOLS_C(DEBUGTOOLS_F ToolFlags,QMainWindow *pMainWindow)
{
  struct structBUTTONDATA *pButton;
  QAction *pAction;


  m_pToolbar=NULL;

  /* Create the toolbar. */
  if (ToolFlags!=0)
    m_pToolbar=pMainWindow->addToolBar("Debug && Test");

  /* Create each action, connect it to a slot, and add each to the toolbar. */
  pButton=m_pDebugTestConsoleButtonList;
  while(pButton->ToolTypes!=NONE)
  {
    if ((pButton->ToolTypes&ToolFlags)!=0)
    {
      if ( ((ToolFlags&(DEBUGBUTTONS|TESTBUTTONS))!=0) && (pButton->SeparatorFlag!=0) )
        m_pToolbar->addSeparator();
      pAction=new QAction(
          QIcon(pButton->pIconName),pButton->pActionName,pMainWindow);
      if (pAction!=NULL)
      {
        connect(pAction,SIGNAL(triggered()),this,pButton->pSlot);
        m_pToolbar->addAction(pAction);
      }
    }
    pButton++;
  }

  /* Create the debug console. */
  m_pConsole=new DEBUGCONSOLEDIALOG_C(
      ToolFlags&DEBUGLOG,ToolFlags&MESSAGELOG,pMainWindow);

  return;
}

DEBUGTOOLS_C::~DEBUGTOOLS_C(void)
{
  return;
}

bool DEBUGTOOLS_C::Connect(
    char const *pSignal,QObject *pObject,char const *pSlot)
{
  return(connect(f_pDebugTools,pSignal,pObject,pSlot));
}

void DEBUGTOOLS_C::DebugConsoleButtonClickedSlot(void)
{
  m_pConsole->setVisible(!0);

  return;
}

void DebugTools_Initialize(QMainWindow *pMainWindow,DEBUGTOOLS_F ToolFlags)
{
  /* Create the dialog box. */
  if (f_pDebugTools==NULL)
  {
    /* Create the debug tools object. */
    f_pDebugTools=new DEBUGTOOLS_C(ToolFlags,pMainWindow);
  }

  return;
}

bool DebugTools_Connect(char const *pSignal,QObject *pObject,char const *pSlot)
{
  return(f_pDebugTools->Connect(pSignal,pObject,pSlot));
}

/**
*** \brief Handles reading/writing of options to/from the configuration file.
***
*** Handles reading/writing of options to/from the configuration file.
***/
class CONSOLEOPTIONS_C
{
  public:
    /**
    *** \brief Contructor.
    *** \details Contructor.
    **/
    CONSOLEOPTIONS_C(void);
    /**
    *** \brief Destructor.
    *** \details Destructor.
    **/
    ~CONSOLEOPTIONS_C(void);

    /**
    *** \brief Compare options.
    *** \details Compare two sets of options.
    *** \param Other Second set of options.
    *** \retval 0 Options are different.
    *** \retval !0 Options are the same.
    **/
    bool operator!=(CONSOLEOPTIONS_C &Other);

    /**
    *** \brief Load options.
    *** \details Load options from the configuration file.
    **/
    void Load(void);
    /**
    *** \brief Save options.
    *** \details Save options to the configuration file.
    **/
    void Save(void);

    /**
    *** \brief Returns the always on top flag.
    *** \details Returns the status of the console always on top flag.
    *** \retval 0 Console is always on top.
    *** \retval !0 Console behaves like
    **/
    bool GetConsoleAlwaysOnTopFlag(void);
    /**
    *** \brief Returns the display on startup flag.
    *** \details Returns the status of the console display on startup flag.
    *** \retval 0 Do not display on startup.
    *** \retval !0 Display on startup.
    **/
    bool GetConsoleDisplayOnStartupFlag(void);
    /**
    *** \brief Returns the console position.
    *** \details Returns the console position.
    *** \returns Console position.
    **/
    QPoint& GetConsolePosition(void);
    /**
    *** \brief Returns the console size.
    *** \details Returns the console size.
    *** \returns Console size.
    **/
    QSize& GetConsoleSize(void);
    /**
    *** \brief Returns the debug log auto refresh flag.
    *** \details Returns the status of the debug log auto refresh flag.
    *** \retval 0 Only manually refresh.
    *** \retval !0 Automatically refresh.
    **/
    bool GetDebugLogAutoRefreshFlag(void);
    /**
    *** \brief Returns the message log auto refresh flag.
    *** \details Returns the status of the message log auto refresh flag.
    *** \retval 0 Only manually refresh.
    *** \retval !0 Automatically refresh.
    **/
    bool GetMessageLogAutoRefreshFlag(void);
    /**
    *** \brief Returns the message log merge duplicates flag.
    *** \details Returns the status of the message log merge duplicates flag.
    *** \retval 0 Do not merge duplicates.
    *** \retval !0 Merge duplicates.
    **/
    bool GetMessageLogMergeDuplicatesFlag(void);
    /**
    *** \brief Returns the message log remove paths flag.
    *** \details Returns the status of the message log remove paths flag.
    *** \retval 0 Do not remove paths.
    *** \retval !0 Remove paths.
    **/
    bool GetMessageLogRemovePathsFlag(void);

    /**
    *** \brief Sets the always on top flag.
    *** \details Sets the console always on top flag.
    *** \param ConsoleAlwaysOnTopFlag Enable/disable the windows always on top.\n
    ***   0 - Behave like a normal window.\n
    ***   !0 - Alway display on top of all other windows.
    **/
    void SetConsoleAlwaysOnTopFlag(bool ConsoleAlwaysOnTopFlag);
    /**
    *** \brief Sets the display on startup flag.
    *** \details Sets the console display on startup flag.
    *** \param ConsoleDisplayOnStartupFlag Enable/disable display of console on
    ***   startup.\n
    ***   0 - Do not display on startup.\n
    ***   !0 - Display on startup.
    **/
    void SetConsoleDisplayOnStartupFlag(bool ConsoleDisplayOnStartupFlag);
    /**
    *** \brief Sets the console position.
    *** \details Sets the console position.
    *** \param ConsolePosition Position of the console.
    **/
    void SetConsolePosition(QPoint &ConsolePosition);
    /**
    *** \brief Sets the console size.
    *** \details Sets the console size.
    *** \param ConsoleSize Size of the console.
    **/
    void SetConsoleSize(QSize &ConsoleSize);
    /**
    *** \brief Sets the debug log auto refresh flag.
    *** \details Sets the debug log auto refresh flag.
    *** \param DebugLogAutoRefreshFlag Enable/disable auto refresh.\n
    ***   0 - Only manually refresh.\n
    ***   !0 - Automatically refresh.
    **/
    void SetDebugLogAutoRefreshFlag(bool DebugLogAutoRefreshFlag);
    /**
    *** \brief Sets the message log auto refresh flag.
    *** \details Sets the message log auto refresh flag.
    *** \param MessageLogAutoRefreshFlag Enable/disable auto refresh.\n
    ***   0 - Only manually refresh.\n
    ***   !0 - Automatically refresh.
    **/
    void SetMessageLogAutoRefreshFlag(bool MessageLogAutoRefreshFlag);
    /**
    *** \brief Sets the merge duplicates flag.
    *** \details Sets the message log merge duplicates flag.
    *** \param MessageLogMergeDuplicatesFlag Enable/disable merging of duplicate
    ***   messages.\n
    ***   0 - Do not merge duplicates.\n
    ***   !0 - Merge duplicates.
    **/
    void SetMessageLogMergeDuplicatesFlag(bool MessageLogMergeDuplicatesFlag);
    /**
    *** \brief Sets the remove paths flag.
    *** \details Sets the message log remove paths flag.
    *** \param MessageLogRemovePathsFlag Enable/disable removal of pathnames.\n
    ***   0 - Do not remove paths.\n
    ***   !0 - Remove paths.
    **/
    void SetMessageLogRemovePathsFlag(bool MessageLogRemovePathsFlag);

  private:
    /**
    *** \brief Always on top flag.
    *** \details Console always on top flag.
    **/
    bool m_ConsoleAlwaysOnTopFlag;
    /**
    *** \brief Display on startup flag.
    *** \details Console display on startup flag.
    **/
    bool m_ConsoleDisplayOnStartupFlag;
    /**
    *** \brief Save position flag.
    *** \details Save console position flag.
    **/
    bool m_SaveConsolePositionFlag;
    /**
    *** \brief Console position.
    *** \details Console position.
    **/
    QPoint m_ConsolePosition;
    /**
    *** \brief Save size flag.
    *** \details Save console size flag.
    **/
    bool m_SaveConsoleSizeFlag;
    /**
    *** \brief Console size.
    *** \details Console size.
    **/
    QSize m_ConsoleSize;
    /**
    *** \brief Debug log auto refresh flag.
    *** \details Debug log auto refresh flag.
    **/
    bool m_DebugLogAutoRefreshFlag;
    /**
    *** \brief Message log auto refresh flag.
    *** \details Message log auto refresh flag.
    **/
    bool m_MessageLogAutoRefreshFlag;
    /**
    *** \brief Message log merge duplicates flag.
    *** \details Message log merge duplicates flag.
    **/
    bool m_MessageLogMergeDuplicatesFlag;
    /**
    *** \brief Message log remove paths flag.
    *** \details Message log remove paths flag.
    **/
    bool m_MessageLogRemovePathsFlag;
};

CONSOLEOPTIONS_C::CONSOLEOPTIONS_C(void)
{
  /* Automatically load the option data. */
  Load();

  return;
}

CONSOLEOPTIONS_C::~CONSOLEOPTIONS_C(void)
{
  return;
}

bool CONSOLEOPTIONS_C::operator!=(CONSOLEOPTIONS_C &Other)
{
  if (m_ConsoleAlwaysOnTopFlag!=Other.m_ConsoleAlwaysOnTopFlag)
    return(true);
  if (m_ConsoleDisplayOnStartupFlag!=Other.m_ConsoleDisplayOnStartupFlag)
    return(true);
  if (m_SaveConsolePositionFlag!=Other.m_SaveConsolePositionFlag)
    return(true);
  if (m_ConsolePosition!=Other.m_ConsolePosition)
    return(true);
  if (m_SaveConsoleSizeFlag!=Other.m_SaveConsoleSizeFlag)
    return(true);
  if (m_ConsoleSize!=Other.m_ConsoleSize)
    return(true);
  if (m_DebugLogAutoRefreshFlag!=Other.m_DebugLogAutoRefreshFlag)
    return(true);
  if (m_MessageLogAutoRefreshFlag!=Other.m_MessageLogAutoRefreshFlag)
    return(true);
  if (m_MessageLogMergeDuplicatesFlag!=Other.m_MessageLogMergeDuplicatesFlag)
    return(true);
  if (m_MessageLogRemovePathsFlag!=Other.m_MessageLogRemovePathsFlag)
    return(true);

  return(false);
}

void CONSOLEOPTIONS_C::Load(void)
{
  QSettings Settings;


  Settings.beginReadArray(OPTION_ARRAY_NAME);
  m_ConsoleAlwaysOnTopFlag=
      Settings.value(OPTION_KEY_CONSOLEALWAYSONTOP,0).toBool();
  m_ConsoleDisplayOnStartupFlag=
      Settings.value(OPTION_KEY_CONSOLEDISPLAYONSTARTUP,0).toBool();
  m_SaveConsolePositionFlag=0;
  m_ConsolePosition=
      Settings.value(OPTION_KEY_CONSOLEWINDOWPOSITION,QPoint()).toPoint();
  m_SaveConsoleSizeFlag=0;
  m_ConsoleSize=Settings.value(OPTION_KEY_CONSOLEWINDOWSIZE,QSize()).toSize();
  m_DebugLogAutoRefreshFlag=
      Settings.value(OPTION_KEY_DEBUGLOGAUTOREFRESH,0).toBool();
  m_MessageLogAutoRefreshFlag=
      Settings.value(OPTION_KEY_MESSAGELOGAUTOREFRESH,0).toBool();
  m_MessageLogMergeDuplicatesFlag=
      Settings.value(OPTION_KEY_MESSAGELOGMERGEDUPLICATES,0).toBool();
  m_MessageLogRemovePathsFlag=
      Settings.value(OPTION_KEY_MESSAGELOGREMOVEPATHS,0).toBool();
  Settings.endArray();

  return;
}

void CONSOLEOPTIONS_C::Save(void)
{
  QSettings Settings;


  Settings.beginWriteArray(OPTION_ARRAY_NAME);
  Settings.setValue(OPTION_KEY_CONSOLEALWAYSONTOP,m_ConsoleAlwaysOnTopFlag);
  Settings.setValue(
      OPTION_KEY_CONSOLEDISPLAYONSTARTUP,m_ConsoleDisplayOnStartupFlag);
  if (m_SaveConsolePositionFlag!=0)
  {
    Settings.setValue(OPTION_KEY_CONSOLEWINDOWPOSITION,m_ConsolePosition);
    m_SaveConsolePositionFlag=0;
  }
  if (m_SaveConsoleSizeFlag!=0)
  {
    Settings.setValue(OPTION_KEY_CONSOLEWINDOWSIZE,m_ConsoleSize);
    m_SaveConsoleSizeFlag=0;
  }
  Settings.setValue(OPTION_KEY_DEBUGLOGAUTOREFRESH,m_DebugLogAutoRefreshFlag);
  Settings.setValue(
      OPTION_KEY_MESSAGELOGAUTOREFRESH,m_MessageLogAutoRefreshFlag);
  Settings.setValue(
      OPTION_KEY_MESSAGELOGMERGEDUPLICATES,m_MessageLogMergeDuplicatesFlag);
  Settings.setValue(
      OPTION_KEY_MESSAGELOGREMOVEPATHS,m_MessageLogRemovePathsFlag);
  Settings.endArray();

  return;
}

bool CONSOLEOPTIONS_C::GetConsoleAlwaysOnTopFlag(void)
{
  return(m_ConsoleAlwaysOnTopFlag);
}

bool CONSOLEOPTIONS_C::GetConsoleDisplayOnStartupFlag(void)
{
  return(m_ConsoleDisplayOnStartupFlag);
}

QPoint& CONSOLEOPTIONS_C::GetConsolePosition(void)
{
  return(m_ConsolePosition);
}

QSize& CONSOLEOPTIONS_C::GetConsoleSize(void)
{
  return(m_ConsoleSize);
}

bool CONSOLEOPTIONS_C::GetDebugLogAutoRefreshFlag(void)
{
  return(m_DebugLogAutoRefreshFlag);
}

bool CONSOLEOPTIONS_C::GetMessageLogAutoRefreshFlag(void)
{
  return(m_MessageLogAutoRefreshFlag);
}

bool CONSOLEOPTIONS_C::GetMessageLogMergeDuplicatesFlag(void)
{
  return(m_MessageLogMergeDuplicatesFlag);
}

bool CONSOLEOPTIONS_C::GetMessageLogRemovePathsFlag(void)
{
  return(m_MessageLogRemovePathsFlag);
}

void CONSOLEOPTIONS_C::SetConsoleAlwaysOnTopFlag(bool ConsoleAlwaysOnTopFlag)
{
  m_ConsoleAlwaysOnTopFlag=ConsoleAlwaysOnTopFlag;

  return;
}

void CONSOLEOPTIONS_C::SetConsoleDisplayOnStartupFlag(
    bool ConsoleDisplayOnStartupFlag)
{
  m_ConsoleDisplayOnStartupFlag=ConsoleDisplayOnStartupFlag;

  return;
}

void CONSOLEOPTIONS_C::SetConsolePosition(QPoint &ConsolePosition)
{
  m_ConsolePosition=ConsolePosition;
  m_SaveConsolePositionFlag=!0;

  return;
}

void CONSOLEOPTIONS_C::SetConsoleSize(QSize &ConsoleSize)
{
  m_ConsoleSize=ConsoleSize;
  m_SaveConsoleSizeFlag=!0;

  return;
}

void CONSOLEOPTIONS_C::SetDebugLogAutoRefreshFlag(bool DebugLogAutoRefreshFlag)
{
  m_DebugLogAutoRefreshFlag=DebugLogAutoRefreshFlag;

  return;
}

void CONSOLEOPTIONS_C::SetMessageLogAutoRefreshFlag(
    bool MessageLogAutoRefreshFlag)
{
  m_MessageLogAutoRefreshFlag=MessageLogAutoRefreshFlag;

  return;
}

void CONSOLEOPTIONS_C::SetMessageLogMergeDuplicatesFlag(
    bool MessageLogMergeDuplicatesFlag)
{
  m_MessageLogMergeDuplicatesFlag=MessageLogMergeDuplicatesFlag;

  return;
}

void CONSOLEOPTIONS_C::SetMessageLogRemovePathsFlag(
    bool MessageLogRemovePathsFlag)
{
  m_MessageLogRemovePathsFlag=MessageLogRemovePathsFlag;

  return;
}

DEBUGCONSOLEOPTIONSDIALOG_C::DEBUGCONSOLEOPTIONSDIALOG_C(
    bool DebugLogFlag,bool MessageLogFlag,QWidget *pParent) : QDialog(pParent)
{
  /* Set up the user interface. */
  setupUi(this);

  if (DebugLogFlag==0)
    m_pTabWidget->removeTab(OPTIONSTAB_DEBUGLOG);
  if (MessageLogFlag==0)
    m_pTabWidget->removeTab(OPTIONSTAB_MESSAGELOG);

  /* Copy the parent (the console window) so its data can be accessed later. */
  m_pParent=pParent;

  /* Create an instance of the option class. */
  m_pConsoleOptions=new CONSOLEOPTIONS_C;

  /* Initialize child widgets. */
  LoadOptions();

  /* Gray out "Apply" button. */
  m_pDialogBoxButtonBox->button(QDialogButtonBox::Apply)->setEnabled(0);

  /* Force the window to be as small as possible. */
  resize(0,0);

  return;
}

DEBUGCONSOLEOPTIONSDIALOG_C::~DEBUGCONSOLEOPTIONSDIALOG_C(void)
{
  if (m_pConsoleOptions!=NULL)
    delete m_pConsoleOptions;

  return;
}

void DEBUGCONSOLEOPTIONSDIALOG_C::LoadOptions(void)
{
  bool SavePositionFlag;
  bool SaveSizeFlag;


  /* Initialize the widgets according to the option data. */
  m_pConsoleAlwaysOnTopCheckBox->setChecked(
      m_pConsoleOptions->GetConsoleAlwaysOnTopFlag());
  m_pConsoleDisplayOnStartupCheckBox->setChecked(
      m_pConsoleOptions->GetConsoleDisplayOnStartupFlag());
  SavePositionFlag=(m_pConsoleOptions->GetConsolePosition().isNull()!=0);
  m_pConsoleSaveWindowPositionCheckBox->setVisible(SavePositionFlag!=0);
  m_pConsoleClearWindowPositionCheckBox->setVisible(SavePositionFlag==0);
  SaveSizeFlag=(m_pConsoleOptions->GetConsoleSize().isValid()==0);
  m_pConsoleSaveWindowSizeCheckBox->setVisible(SaveSizeFlag!=0);
  m_pConsoleClearWindowSizeCheckBox->setVisible(SaveSizeFlag==0);
  m_pConsoleSaveWindowPositionCheckBox->setChecked(0);
  m_pConsoleClearWindowPositionCheckBox->setChecked(0);
  m_pConsoleSaveWindowSizeCheckBox->setChecked(0);
  m_pConsoleClearWindowSizeCheckBox->setChecked(0);
  m_pDebugLogAutoRefreshCheckBox->setChecked(
      m_pConsoleOptions->GetDebugLogAutoRefreshFlag());
  m_pMessageLogAutoRefreshCheckBox->setChecked(
      m_pConsoleOptions->GetMessageLogAutoRefreshFlag());
  m_pMessageLogMergeDuplicatesCheckBox->setChecked(
      m_pConsoleOptions->GetMessageLogMergeDuplicatesFlag());
  m_pMessageLogRemovePathsCheckBox->setChecked(
      m_pConsoleOptions->GetMessageLogRemovePathsFlag());

  return;
}

void DEBUGCONSOLEOPTIONSDIALOG_C::SaveOptions(void)
{
  QPoint Position;
  QSize Size;


  /* Set the option data according to the widgets. */
  m_pConsoleOptions->SetConsoleAlwaysOnTopFlag(
      m_pConsoleAlwaysOnTopCheckBox->isChecked());
  m_pConsoleOptions->SetConsoleDisplayOnStartupFlag(
      m_pConsoleDisplayOnStartupCheckBox->isChecked());
  if (m_pConsoleOptions->GetConsolePosition().isNull()!=0)
  {
    /* Save position. */
    if (m_pConsoleSaveWindowPositionCheckBox->isChecked()!=0)
    {
      Position=m_pParent->pos();
      m_pConsoleOptions->SetConsolePosition(Position);
    }
  }
  else
  {
    /* Clear position. */
    if (m_pConsoleClearWindowPositionCheckBox->isChecked()!=0)
    {
      Position=QPoint();
      m_pConsoleOptions->SetConsolePosition(Position);
    }
  }
  if (m_pConsoleOptions->GetConsoleSize().isValid()==0)
  {
    /* Save position. */
    if (m_pConsoleSaveWindowSizeCheckBox->isChecked()!=0)
    {
      Size=m_pParent->size();
      m_pConsoleOptions->SetConsoleSize(Size);
    }
  }
  else
  {
    /* Clear position. */
    if (m_pConsoleClearWindowSizeCheckBox->isChecked()!=0)
    {
      Size=QSize();
      m_pConsoleOptions->SetConsoleSize(Size);
    }
  }
  m_pConsoleOptions->SetDebugLogAutoRefreshFlag(
      m_pDebugLogAutoRefreshCheckBox->isChecked());
  m_pConsoleOptions->SetMessageLogAutoRefreshFlag(
      m_pMessageLogAutoRefreshCheckBox->isChecked());
  m_pConsoleOptions->SetMessageLogMergeDuplicatesFlag(
      m_pMessageLogMergeDuplicatesCheckBox->isChecked());
  m_pConsoleOptions->SetMessageLogRemovePathsFlag(
      m_pMessageLogRemovePathsCheckBox->isChecked());

  return;
}

void DEBUGCONSOLEOPTIONSDIALOG_C::DialogBoxButtonClicked(
    QAbstractButton* pButton)
{
  switch(m_pDialogBoxButtonBox->standardButton(pButton))
  {
    case QDialogButtonBox::Ok:
    case QDialogButtonBox::Apply:
      /* Read the widgets. */
      SaveOptions();

      /* Save the options. */
      m_pConsoleOptions->Save();

      if (m_pDialogBoxButtonBox->standardButton(pButton)==QDialogButtonBox::Ok)
      {
        /* Close dialog on "Ok". */
        accept();
      }
      else
      {
        /* Reload widget data. */
        LoadOptions();

        /* Gray out "Apply" button. */
        m_pDialogBoxButtonBox->button(QDialogButtonBox::Apply)->setEnabled(0);
      }
      break;
    case QDialogButtonBox::Cancel:
      reject();
      break;
    default:
      break;
  }

  return;
}

void DEBUGCONSOLEOPTIONSDIALOG_C::DialogBoxDataChanged(void)
{
  CONSOLEOPTIONS_C ConfigFile;


  /* Transfer the widget data into member variable. */
  SaveOptions();

  /* Compare the member variable to the config file and enable "Apply" if
      different. */
  m_pDialogBoxButtonBox->button(QDialogButtonBox::Apply)->setEnabled(
      ConfigFile!=*m_pConsoleOptions);

  /* Restore the member variable. */
  m_pConsoleOptions->Load();

  return;
}

DEBUGCONSOLEDIALOG_C::DEBUGCONSOLEDIALOG_C(
    bool DebuglogFlag,bool MessageLogFlag,QWidget *pParent) : QDialog(pParent)
{
  CONSOLEOPTIONS_C ConsoleOptions;
  QPushButton *pOptionsButton;
  QString Pathname;
  char const *pPathname;


  /* Set up the user interface. */
  setupUi(this);

  m_DebugLogFlag=DebuglogFlag;
  m_MessageLogFlag=MessageLogFlag;

  /* Remove in reverse order so the indices don't change. */
  if (m_MessageLogFlag==0)
    m_pTabWidget->removeTab(CONSOLETAB_MESSAGELOG);
  if (m_DebugLogFlag==0)
    m_pTabWidget->removeTab(CONSOLETAB_DEBUGLOG);

  /* Set up options. */
  ApplyOptions(!0);

  if (m_DebugLogFlag!=0)
  {
    pPathname=DEBUGLOG_GetFilenamePointer();
    m_pDebugLogViewerWidget->SetDebugLogPathname(pPathname);
  }
  if (m_MessageLogFlag!=0)
  {
    pPathname=MESSAGELOG_GetFilenamePointer();
    m_pMessageLogViewerWidget->SetMessageLogPathname(pPathname);
  }

  /* Start a timer to periodically check the modified time/date. */
  connect(&m_Timer,SIGNAL(timeout()),
      m_pDebugLogViewerWidget,SLOT(CheckFileDateTimeSlot()));
  connect(&m_Timer,SIGNAL(timeout()),
      m_pMessageLogViewerWidget,SLOT(CheckFileDateTimeSlot()));
  m_Timer.start(DELAY_CHECKMODIFICATIONTIME);

  /* Add/create an "Options" button. */
  pOptionsButton=m_pButtonBox->addButton(QDialogButtonBox::Help);
  pOptionsButton->setText("&Options");
  pOptionsButton->setIcon(QIcon(":/DebugConsole/OptionsIcon"));

  return;
}

DEBUGCONSOLEDIALOG_C::~DEBUGCONSOLEDIALOG_C(void)
{
  /* Stop the timer. */
  m_Timer.stop();

  return;
}

void DEBUGCONSOLEDIALOG_C::ApplyOptions(bool StartupFlag)
{
  CONSOLEOPTIONS_C ConsoleOptions;
  bool AlwaysOnTopSettingFlag;
  bool AlwaysOnTopWindowFlag;
  Qt::WindowFlags WindowFlags;
  QPoint Position;
  QSize Size;
  bool ShowFlag;


  /* Modify window as necessary depending on options. */
  ShowFlag=0;

  /* \todo Always on top not working right. */
  AlwaysOnTopSettingFlag=ConsoleOptions.GetConsoleAlwaysOnTopFlag();
  AlwaysOnTopWindowFlag=((windowFlags()&Qt::WindowStaysOnTopHint)!=0);
  if ( (AlwaysOnTopSettingFlag!=AlwaysOnTopWindowFlag)!=0)
  {
    if (AlwaysOnTopSettingFlag==0)
      WindowFlags=windowFlags()&~Qt::WindowStaysOnTopHint;
    else
      WindowFlags=windowFlags()|Qt::WindowStaysOnTopHint;
    setWindowFlags(WindowFlags);
    ShowFlag=!0;
  }
  Position=ConsoleOptions.GetConsolePosition();
  if (Position.isNull()==0)
    move(Position);
  Size=ConsoleOptions.GetConsoleSize();
  if (Size.isValid()!=0)
    resize(Size);
  if (StartupFlag!=0)
    if (ConsoleOptions.GetConsoleDisplayOnStartupFlag())
      ShowFlag=!0;
  if (ShowFlag!=0)
    show();

  m_pDebugLogViewerWidget->SetAutoRefreshFlag(
      ConsoleOptions.GetDebugLogAutoRefreshFlag());
  m_pMessageLogViewerWidget->SetAutoRefreshFlag(
      ConsoleOptions.GetMessageLogAutoRefreshFlag());
  m_pMessageLogViewerWidget->SetMergeDuplicatesFlag(
      ConsoleOptions.GetMessageLogMergeDuplicatesFlag());
  m_pMessageLogViewerWidget->SetRemovePathsFlag(
      ConsoleOptions.GetMessageLogRemovePathsFlag());

  return;
}

void DEBUGCONSOLEDIALOG_C::DialogBoxButtonClickedSlot(QAbstractButton *pButton)
{
  DEBUGCONSOLEOPTIONSDIALOG_C Dialog(m_DebugLogFlag,m_MessageLogFlag,this);


  switch(m_pButtonBox->standardButton(pButton))
  {
    case QDialogButtonBox::Close:
      setVisible(false);
      break;
    case QDialogButtonBox::Help:
      /* Display the options dialog, and if accepted, reload options. */
      if (Dialog.exec()==QDialog::Accepted)
        ApplyOptions(0);
    default:
      break;
  }

  return;
}

void DEBUGCONSOLEDIALOG_C::closeEvent(QCloseEvent *pEvent)
{
  setVisible(false);
  pEvent->ignore();

  return;
}


#undef    DEBUGCONSOLEDIALOG_CPP
