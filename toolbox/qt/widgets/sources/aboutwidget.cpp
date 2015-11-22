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
*** \file aboutwidget.cpp
*** \brief aboutwidget.h implementation file.
*** \details Implementation file for aboutwidget.h.
**/


/** Identifier for aboutwidget.cpp. **/
#define   ABOUTWIDGET_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "aboutwidget.h"
#ifdef    DEBUG_ABOUTWIDGET_CPP
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_ABOUTWIDGET_CPP */
#include  "debuglog.h"
//#include  "messagelog.h"

//#include  <QTimer>
//#include  <QPushButton>
//#include  <QFileInfo>


/****
*****
***** DEFINES
*****
****/

/**
*** \brief Information tab index.
*** \details Index of the information tab in the about widget.
***/
#define   ABOUTTAB_INFORMATION  (0)

/**
*** \brief License tab index.
*** \details Index of the license tab in the about widget.
***/
#define   ABOUTTAB_LICENSE      (1)


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

void ABOUTWIDGET_C::SetExecutableNameAndVersionText(void)
{
  DEBUGLOG_Printf0("ABOUTWIDGET_C::SetExecutableNameAndVersionText()");
  DEBUGLOG_LogIn();

  m_pProgramVersionLabel->setText(m_ExecutableName+" Version ("+m_Version+")");

  DEBUGLOG_LogOut();
  return;
}

ABOUTWIDGET_C::ABOUTWIDGET_C(QWidget *pParent) : QWidget(pParent)
{
  DEBUGLOG_Printf1("ABOUTWIDGET_C::ABOUTWIDGET_C(%p)",pParent);
  DEBUGLOG_LogIn();

  /* Setup the user interface. */
  setupUi(this);

#ifndef   BUILD_PLUGIN
  m_pCheckFrame->setVisible(false);
#endif    /* BUILD_PLUGIN */

  DEBUGLOG_LogOut();
return;
}

ABOUTWIDGET_C::~ABOUTWIDGET_C(void)
{
  DEBUGLOG_Printf0("ABOUTWIDGET_C::~ABOUTWIDGET_C()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return;
}

bool ABOUTWIDGET_C::GetCheckButtonEnabled(void)
{
  DEBUGLOG_Printf0("ABOUTWIDGET_C::GetCheckButtonEnabled()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_pCheckButton->isEnabled());
}

QString ABOUTWIDGET_C::GetDisplayName(void)
{
  DEBUGLOG_Printf0("ABOUTWIDGET_C::GetDisplayName()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_pProgramNameLabel->text());
}

QString ABOUTWIDGET_C::GetExecutableName(void)
{
  DEBUGLOG_Printf0("ABOUTWIDGET_C::GetExecutableName()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_ExecutableName);
}

QPixmap ABOUTWIDGET_C::GetImage(void)
{
  QPixmap Pixmap;


  DEBUGLOG_Printf0("ABOUTWIDGET_C::GetImage()");
  DEBUGLOG_LogIn();

  Pixmap=*m_pProgramIcon->pixmap();

  DEBUGLOG_LogOut();
  return(Pixmap);
}

QString ABOUTWIDGET_C::GetInformation(void)
{
  DEBUGLOG_Printf0("ABOUTWIDGET_C::GetInformation()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_pInformationEdit->toPlainText());
}

QIcon ABOUTWIDGET_C::GetInformationIcon(void)
{
  DEBUGLOG_Printf0("ABOUTWIDGET_C::GetInformationIcon()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_pAboutTabWidget->tabIcon(ABOUTTAB_INFORMATION));
}

QString ABOUTWIDGET_C::GetLicense(void)
{
  DEBUGLOG_Printf0("ABOUTWIDGET_C::GetLicense()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_pLicenseAgreementEdit->toPlainText());
}

QIcon ABOUTWIDGET_C::GetLicenseIcon(void)
{
  DEBUGLOG_Printf0("ABOUTWIDGET_C::GetLicenseIcon()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_pAboutTabWidget->tabIcon(ABOUTTAB_LICENSE));
}

QString ABOUTWIDGET_C::GetVersion(void)
{
  DEBUGLOG_Printf0("ABOUTWIDGET_C::GetVersion()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_Version);
}

void ABOUTWIDGET_C::SetCheckButtonEnabled(bool EnabledFlag)
{
  DEBUGLOG_Printf1("ABOUTWIDGET_C::SetCheckButtonEnabled(%u)",EnabledFlag);
  DEBUGLOG_LogIn();

  m_pCheckButton->setEnabled(EnabledFlag);

  DEBUGLOG_LogOut();
  return;
}

void ABOUTWIDGET_C::SetDisplayName(QString Name)
{
  DEBUGLOG_Printf2(
      "ABOUTWIDGET_C::SetDisplayName(%p(%s))",&Name,qPrintable(Name));
  DEBUGLOG_LogIn();

  m_pProgramNameLabel->setText(Name);

  DEBUGLOG_LogOut();
  return;
}

void ABOUTWIDGET_C::SetExecutableName(QString Name)
{
  DEBUGLOG_Printf2(
      "ABOUTWIDGET_C::SetExecutableName(%p(%s))",&Name,qPrintable(Name));
  DEBUGLOG_LogIn();

  m_ExecutableName=Name;
  SetExecutableNameAndVersionText();

  DEBUGLOG_LogOut();
  return;
}

void ABOUTWIDGET_C::SetInformation(QString Information)
{
  DEBUGLOG_Printf2("ABOUTWIDGET_C::SetInformation(%p(%s))",
      &Information,qPrintable(Information));
  DEBUGLOG_LogIn();

  m_pInformationEdit->setHtml(Information);

  DEBUGLOG_LogOut();
  return;
}

void ABOUTWIDGET_C::SetInformationIcon(QIcon Icon)
{
  DEBUGLOG_Printf1("ABOUTWIDGET_C::SetInformationIcon(%p)",&Icon);
  DEBUGLOG_LogIn();

  m_pAboutTabWidget->setTabIcon(ABOUTTAB_INFORMATION,Icon);

  DEBUGLOG_LogOut();
  return;
}

void ABOUTWIDGET_C::SetImage(QPixmap Pixmap)
{
  DEBUGLOG_Printf1("ABOUTWIDGET_C::SetImage(%p)",&Pixmap);
  DEBUGLOG_LogIn();

  m_pProgramIcon->setPixmap(Pixmap);

  DEBUGLOG_LogOut();
  return;
}

void ABOUTWIDGET_C::SetLicense(QString License)
{
  DEBUGLOG_Printf2(
      "ABOUTWIDGET_C::SetLicense(%p(%s))",&License,qPrintable(License));
  DEBUGLOG_LogIn();

  m_pLicenseAgreementEdit->setPlainText(License);

  DEBUGLOG_LogOut();
  return;
}

void ABOUTWIDGET_C::SetLicenseIcon(QIcon Icon)
{
  DEBUGLOG_Printf1("ABOUTWIDGET_C::SetLicenseIcon(%p)",&Icon);
  DEBUGLOG_LogIn();

  m_pAboutTabWidget->setTabIcon(ABOUTTAB_LICENSE,Icon);

  DEBUGLOG_LogOut();
  return;
}

void ABOUTWIDGET_C::SetUpdateText(QString Text)
{
  DEBUGLOG_Printf2(
      "ABOUTWIDGET_C::SetUpdateText(%p(%s))",&Text,qPrintable(Text));
  DEBUGLOG_LogIn();

  m_pCheckLabel->setText(Text);

  DEBUGLOG_LogOut();
  return;
}

void ABOUTWIDGET_C::SetVersion(QString Version)
{
  DEBUGLOG_Printf2(
      "ABOUTWIDGET_C::SetVersion(%p(%s))",&Version,qPrintable(Version));
  DEBUGLOG_LogIn();

  m_Version=Version;
  SetExecutableNameAndVersionText();

  DEBUGLOG_LogOut();
  return;
}

void ABOUTWIDGET_C::ShowCheckForUpdateWidget(bool ShowFlag)
{
  DEBUGLOG_Printf1("ABOUTWIDGET_C::ShowCheckForUpdateWidget(%u)",ShowFlag);
  DEBUGLOG_LogIn();

  m_pCheckFrame->setVisible(ShowFlag);

  DEBUGLOG_LogOut();
  return;
}


#undef    ABOUTWIDGET_CPP
