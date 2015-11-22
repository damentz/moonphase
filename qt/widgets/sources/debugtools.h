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
*** \brief Display the debug console dialog box and process its events.
*** \details  Displays the debug console dialog box and processes signals sent
***   by the widgets within the dialog box.
**/


#ifndef   DEBUGTOOLS_H
#define   DEBUGTOOLS_H


/****
*****
***** INCLUDES
*****
****/

#include  <QWidget>


/****
*****
***** DEFINES
*****
****/

#ifdef    USE_DEBUGTOOLS
/**
*** \brief DebugTools_Connect() wrapper.
*** \details Wrapper macro for DebugTools_Connect().
*** \param sig Signal.
*** \param obj Receiver object.
*** \param slot Receiver slot.
***/
#define   DEBUGTOOLS_Connect(sig,obj,slot)  DebugTools_Connect(sig,obj,slot)
/**
*** \brief DebugTools_Initialize() wrapper.
*** \details Wrapper macro for DebugTools_Connect().
*** \param win Pointer to main window.
*** \param flags List of tools to enable (DEBUGTOOLS_F).
***/
#define   DEBUGTOOLS_Initialize(win,flags)  DebugTools_Initialize(win,flags)
/**
*** \brief DebugTools_InitResource() wrapper.
*** \details Wrapper macro for DebugTools_Connect().
***/
#define   DEBUGTOOLS_InitResource()         Q_INIT_RESOURCE(debugconsole)
#else     /* USE_DEBUGTOOLS */
/**
*** \brief Does nothing.
*** \details Does nothing. DebugTools are disabled.
*** \param sig Ignored.
*** \param obj Ignored.
*** \param slot Ignored.
***/
#define   DEBUGTOOLS_Connect(sig,obj,slot)
/**
*** \brief Does nothing.
*** \details Does nothing. DebugTools are disabled.
*** \param win Ignored.
*** \param flags Ingored.
***/
#define   DEBUGTOOLS_Initialize(win,flags)
/**
*** \brief Does nothing.
*** \details Does nothing. DebugTools are disabled.
***/
#define   DEBUGTOOLS_InitResource()
#endif    /* USE_DEBUGTOOLS */


/****
*****
***** DATA TYPES
*****
****/

/**
*** \brief Debug tools.
*** \details Available debug tools.
***/
typedef enum enumDEBUGTOOLS
{
  NONE=0,
  DEBUGBUTTONS=1,
  TESTBUTTONS=2,
  DEBUGLOG=4,
  MESSAGELOG=8
} DEBUGTOOLS_F;

class DEBUGCONSOLEDIALOG_C;
class QMainWindow;
class QToolBar;

/**
*** \brief Display a toolbar.
*** \details Displays a toolbar containing debug/test buttons and/or a button
***   to access to the debug console.
**/
class DEBUGTOOLS_C : private QWidget
{
  Q_OBJECT

  public:
    /**
    *** \brief Constructor.
    *** \details Constructor.
    *** \param ToolFlags Debug tools to enable (DEBUGTOOLS_F).
    *** \param pMainWindow Pointer to the application main window.
    **/
    DEBUGTOOLS_C(DEBUGTOOLS_F ToolFlags,QMainWindow *pMainWindow);
    /**
    *** \brief Destructor.
    *** \details Destructor.
    **/
    ~DEBUGTOOLS_C(void);
    /**
    *** \brief Connect a signal to a slot.
    *** \details Connects a signal from the debug tools to a user defined slot.
    *** \param pSignal Signal.
    *** \param pObject Receiver object.
    *** \param pSlot Receiver slot.
    *** \retval 0 Failure.
    *** \retval !0 Success.
    **/
    bool Connect(char const *pSignal,QObject *pObject,char const *pSlot);

  private slots:
    /**
    *** \brief "Debug console" button clicked.
    *** \details "Debug console" button was clicked.
    **/
    void DebugConsoleButtonClickedSlot(void);

  signals:
    /**
    *** \brief "Debug1" button clicked.
    *** \details "Debug1" button was clicked.
    **/
    void Debug1ButtonClickedSignal(void);
    /**
    *** \brief "Debug2" button clicked.
    *** \details "Debug2" button was clicked.
    **/
    void Debug2ButtonClickedSignal(void);
    /**
    *** \brief "Test1" button clicked.
    *** \details "Test1" button was clicked.
    **/
    void Test1ButtonClickedSignal(void);
    /**
    *** \brief "Test2" button clicked.
    *** \details "Test2" button was clicked.
    **/
    void Test2ButtonClickedSignal(void);

  private:
    /**
    *** \brief The test/debug console toolbar.
    *** \details The test/debug console toolbar.
    **/
    QToolBar *m_pToolbar;
    /**
    *** \brief The debug console dialog box.
    *** \details The debug console dialog box.
    **/
    DEBUGCONSOLEDIALOG_C *m_pConsole;
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

/**
*** \brief Bitwise OR operator.
*** \details Bitwise OR operator.
*** \param LHS Left hand side value.
*** \param RHS Right hand side value.
*** \returns Bitwise OR of both values.
***/
inline DEBUGTOOLS_F operator|(DEBUGTOOLS_F LHS,DEBUGTOOLS_F RHS)
{
  return((DEBUGTOOLS_F)(((int)LHS)|((int)RHS)));
}

#ifdef    __cplusplus
extern "C" {
#endif    /* __cplusplus */

/**
*** \brief Connect a signal to a slot.
*** \details Connects a signal from the debug tools to a user defined slot.
*** \param pSignal Signal.
*** \param pObject Receiver object.
*** \param pSlot Receiver slot.
*** \retval 0 Failure.
*** \retval !0 Success.
***/
bool DebugTools_Connect(char const *pSignal,QObject *pObject,char const *pSlot);
/**
*** \brief Initialize debug tools.
*** \details Initializes the debug tools.
*** \param pMainWindow Pointer to main window.
*** \param ToolFlags List of tools to enable (DEBUGTOOLS_F).
***/
void DebugTools_Initialize(QMainWindow *pMainWindow,DEBUGTOOLS_F ToolFlags);

#ifdef    __cplusplus
}
#endif    /* __cplusplus */


#endif    /* DEBUGTOOLS_H */
