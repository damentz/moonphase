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
*** \file debugtools.h
*** \brief Debug console dialog box private classes.
*** \details Private classes for the debug console dialog box.
**/


#ifndef   DEBUGTOOLS_PRIVATE_H
#define   DEBUGTOOLS_PRIVATE_H


/****
*****
***** INCLUDES
*****
****/

#include  "ui_debugconsoledialog.h"
#include  "ui_debugconsoleoptionsdialog.h"
#include  <QTimer>


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

class CONSOLEOPTIONS_C;

/**
*** \brief Displays the debug console options dialog box.
*** \details This class provides the ability to display the debug console
***   options dialog box and processes signals sent by the widgets within the
***   dialog box.
**/
class DEBUGCONSOLEOPTIONSDIALOG_C :
    public QDialog, private Ui::DEBUGCONSOLEOPTIONSDIALOGUI_C
{
  Q_OBJECT

  public:
    /**
    *** \brief Constructor.
    *** \details Constructor.
    *** \param DebugLogFlag If non-zero, show the debug log options tab.
    *** \param MessageLogFlag If non-zero, show the message log options tab.
    *** \param pParent Pointer to parent widget.
    **/
    DEBUGCONSOLEOPTIONSDIALOG_C(
        bool DebugLogFlag,bool MessageLogFlag,QWidget *pParent=NULL);
    /**
    *** \brief Destructor.
    *** \details Destructor.
    **/
    ~DEBUGCONSOLEOPTIONSDIALOG_C(void);

  private:
    /**
    *** \brief Read configuration options.
    *** \details Reads the option data from the configuration file.
    **/
    void LoadOptions(void);
    /**
    *** \brief Write configuration options.
    *** \details Writes the option data to the configuration file.
    **/
    void SaveOptions(void);

  private slots:
    /**
    *** \brief Dialog box button clicked.
    *** \details A button in the dialog box was clicked.
    *** \param pButton Pointer to the button that was clicked.
    **/
    void DialogBoxButtonClicked(QAbstractButton *pButton);
    /**
    *** \brief Child widget data changed.
    *** \details Data in a child widget in the dialog box was changed.
    **/
    void DialogBoxDataChanged(void);

  private:
    /**
    *** \brief Parent widget pointer.
    *** \details Pointer to parent widget.
    **/
    QWidget *m_pParent;
    /**
    *** \brief Option data.
    *** \details Console option data.
    **/
    CONSOLEOPTIONS_C *m_pConsoleOptions;
};

/**
*** \brief Displays the debug console dialog box.
*** \details Display the debug console dialog box and process signals sent by
***   the widgets within the dialog box.
**/
class DEBUGCONSOLEDIALOG_C : public QDialog, private Ui::DEBUGCONSOLEDIALOGUI_C
{
  Q_OBJECT

  public:
    /**
    *** \brief Constructor.
    *** \details Constructor.
    *** \param DebugLogFlag If non-zero, show the debug log tab.
    *** \param MessageLogFlag If non-zero, show the message log tab.
    *** \param pParent Pointer to parent widget.
    **/
    DEBUGCONSOLEDIALOG_C(bool DebugLogFlag,bool MessageLogFlag,
        QWidget *pParent=NULL);
    /**
    *** \brief Destructor.
    *** \details Destructor.
    **/
    ~DEBUGCONSOLEDIALOG_C(void);

  private:
    /**
    *** \brief Read and apply settings.
    *** \details Reads the options and applies the settings.
    *** \param StartupFlag
    ***   Flag indicating whether or not the dialog is starting.\n
    ***   =0 - Not in startup mode.\n
    ***   !0 - Startup mode.
    **/
    void ApplyOptions(bool StartupFlag);
    /**
    *** \brief Close event.
    *** \details Processes the dialog box close event.
    *** \param pEvent Pointer to event.
    **/
    void closeEvent(QCloseEvent *pEvent);

  private slots:
    /**
    *** \brief Dialog box button clicked.
    *** \details A button in the dialog box was clicked.
    *** \param pButton Pointer to the button that was clicked.
    **/
    void DialogBoxButtonClickedSlot(QAbstractButton *pButton);

  signals:
    /**
    *** \brief Debug1 signal.
    *** \details Signal emitted when button "Debug1" is clicked.
    **/
    void Debug1Signal(void);
    /**
    *** \brief Debug2 signal.
    *** \details Signal emitted when button "Debug2" is clicked.
    **/
    void Debug2Signal(void);
    /**
    *** \brief Test1 signal.
    *** \details Signal emitted when button "Test1" is clicked.
    **/
    void Test1Signal(void);
    /**
    *** \brief Test2 signal.
    *** \details Signal emitted when button "Test2" is clicked.
    **/
    void Test2Signal(void);

  private:
    /**
    *** \brief Polls the debug log file.
    *** \details Timer used to periodically check if the debug log file has been
    ***   modified in the filesystem.
    **/
    QTimer m_Timer;
    /**
    *** \brief Show debug log widgets.
    *** \details Show debug log widgets.\n 0 - No.\n!0 - Yes.
    **/
    bool m_DebugLogFlag;
    /**
    *** \brief Show message log widgets.
    *** \details Show message log widgets.\n 0 - No.\n!0 - Yes.
    **/
    bool m_MessageLogFlag;
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

#ifdef    __cplusplus
extern "C" {
#endif    /* __cplusplus */

#ifdef    __cplusplus
}
#endif    /* __cplusplus */


#endif    /* DEBUGTOOLS_PRIVATE_H */
