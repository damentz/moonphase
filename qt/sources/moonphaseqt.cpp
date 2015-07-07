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
*** \file moonphaseqt.cpp
*** \brief moonphase-qt operating system entry point.
*** \details Operating system entry point for moonphase-qt. Initializes the
***   application, creates the main window, and begins event processing.
*** \todo If another instance is running, activate the current instance.
**/


/** Identifier for moonphase.cpp. **/
#define   MOONPHASEQT_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "config.h"
#if       defined(DEBUG_MOONPHASEQT_CPP)
#if       !defined(USE_DEBUGLOG)
#define   USE_DEBUGLOG
#endif    /* !defined(USE_DEBUGLOG) */
#endif    /* defined(DEBUG_MOONPHASEQT_CPP) */
#include  "debuglog.h"
#include  "messagelog.h"

#include  "errorcode.h"
#include  "controlpaneldialog.h"
#include  "QtSingleApplication"

#include  <QSystemTrayIcon>
#include  <QMessageBox>


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
*** \brief Application starting point.
*** \details Operating system entry function for the application. Initializes
***   the application, creates the main window, and begins event processing on
***   the window.
*** \param ArgC
***   Number of command line arguments.
*** \param ppArgV
***   Pointer to array of command line argument strings.
*** \retval 0 Success.
*** \retval !0 Error.
**/
int main(int ArgC, char *ppArgV[])
{
  QtSingleApplication *pApplication=NULL;
  CONTROLPANELDIALOG_C *pDialog;
  int Return;

  /* Initialize the debug and message logs (possibly, depends on defines). */
  DEBUGLOG_Initialize(!0);
  MESSAGELOG_Initialize();

  DEBUGLOG_Printf2("main(%d,%p)",ArgC,ppArgV);
  DEBUGLOG_LogIn();

  try
  {
    /* Initialize resources specified by the .qrc file. */
    Q_INIT_RESOURCE(moonphaseqt);

    /* Create the application. */
    pApplication=new QtSingleApplication(ArgC,ppArgV);

    /* Set up settings keys. */
    QCoreApplication::setApplicationName(MOONPHASEQT_EXECUTABLENAME_STRING);
    QCoreApplication::setOrganizationName(MOONPHASEQT_OWNER_STRING);
    QCoreApplication::setOrganizationDomain(MOONPHASEQT_WEBSITE_STRING);

    /* Create the main window. */
    pDialog=new CONTROLPANELDIALOG_C();

    Return=EXIT_SUCCESS;
    if (QSystemTrayIcon::isSystemTrayAvailable()==false)
    {
      QMessageBox::critical(pDialog,MOONPHASEQT_DISPLAYNAME_STRING,
          "The system tray was not detected.\nThis program will quit now.");
    }
    else
    {
      QApplication::setQuitOnLastWindowClosed(false);

      /* Check for an already running instance and
          for allow multiple instances flag cleared. */
      if ( (pApplication->isRunning()==true) &&
          (pDialog->GetAllowMultipleInstancesFlag()==false) )
      {
        /* Not allowed by configuration. */
        QMessageBox::warning(pDialog,QObject::tr(MOONPHASEQT_DISPLAYNAME_STRING),
            QObject::tr("Another instance of this program is already running. "
            "This instance will be stopped and the other instance will be activated."));
        pApplication->sendMessage("Activate");
      }
      else
      {
        QObject::connect(pApplication,SIGNAL(messageReceived(const QString &)),
            pDialog,SLOT(InstanceMessageSlot(const QString&)));

        /* Begin processing events. */
        Return=pApplication->exec();
      }

      /* Free the main window. */
      delete pDialog;
    }

    /* Free the application. */
    delete pApplication;
  }
  catch(ERRORCODE_T const &EC)
  {
    /* Free the main window. */
    delete pDialog;

    /* Free the application. */
    delete pApplication;

    MESSAGELOG_LogError(EC);
    Return=EXIT_FAILURE;
  }
  catch(std::bad_alloc const &BadAllocation)
  {
    /* Free the main window. */
    delete pDialog;

    /* Free the application. */
    delete pApplication;

    MESSAGELOG_LogError(ERRORCODE_OUTOFMEMORY);
    Return=EXIT_FAILURE;
  }

  DEBUGLOG_LogOut();
  return(Return);
}


#undef    MOONPHASEQT_CPP
