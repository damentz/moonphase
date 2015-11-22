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
*** \file debuglogviewerwidget.cpp
*** \brief debuglogviewerwidget.h implementation file.
*** \details Implementation file for debuglogviewerwidget.h.
**/


/** Identifier for debuglogviewerwidget.cpp. **/
#define   DEBUGLOGVIEWERWIDGET_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "debuglogviewerwidget.h"

#include  <QPushButton>
#include  <QFileInfo>


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

DEBUGLOGVIEWERWIDGET_C::DEBUGLOGVIEWERWIDGET_C(QWidget *pParent)
    : QWidget(pParent)
{
  QPushButton *pRefreshButton;


  /* Setup the user interface. */
  setupUi(this);

  /* Add/create a "Refresh" button. */
  pRefreshButton=m_pButtonBox->button(QDialogButtonBox::Apply);
  if (pRefreshButton!=NULL)
  {
    pRefreshButton->setText("&Refresh");
    pRefreshButton->setIcon(QIcon(":/DebugConsole/RefreshIcon"));
  }

  /* Initialize members. */
  m_Pathname=QString();
  m_AutoRefreshFlag=0;

#ifdef    BUILD_PLUGIN
  /* Provide some dummy text for the plugin. */
  m_pTextEdit->setPlainText("Sample text.\nThis is more sample text.\n"
      "Still more sample text.");
#endif    /* BUILD_PLUGIN */

  /* Disable the "Refresh" button and the "Disable autorefresh" checkbox. */
  m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
  m_pDisableAutoRefreshCheckBox->setEnabled(false);

  return;
}

DEBUGLOGVIEWERWIDGET_C::~DEBUGLOGVIEWERWIDGET_C(void)
{
  return;
}

void DEBUGLOGVIEWERWIDGET_C::LoadDebugLog(void)
{
  QFileInfo FileInfo;
  QFile File;
  QString Data;


  /* Make sure there is a pathname. */
  if (m_Pathname.isEmpty()==0)
  {
    /* Open the debug log file. */
    File.setFileName(m_Pathname);
    if (File.open(QFile::ReadOnly)==true)
    {
      /* Read the debug log file. */
      Data=File.readAll();
      File.close();
      if (Data.isEmpty()==0)
      {
        /* Populate the text edit with the contents of the debug log file. */
        /** \todo Save scrollbar position and then after new data is set,
              restore the scrollbar position. **/
        m_pTextEdit->setPlainText((Data));

        /* Get and save the "last modified" date/time. */
        FileInfo.setFile(File);
        m_LastModifiedDateTime=FileInfo.lastModified();

        /* Disable the "Refresh" button. */
        m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
      }
    }
  }

  return;
}

void DEBUGLOGVIEWERWIDGET_C::SetAutoRefreshFlag(bool AutoRefreshFlag)
{
  m_AutoRefreshFlag=AutoRefreshFlag;
  UpdateWidgets();
  m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(false);

  return;
}

void DEBUGLOGVIEWERWIDGET_C::SetDebugLogPathname(QString Pathname)
{
  if (Pathname.isEmpty()==0)
    m_Pathname=Pathname;

  return;
}

void DEBUGLOGVIEWERWIDGET_C::UpdateWidgets(void)
{
  m_pDisableAutoRefreshCheckBox->setEnabled(m_AutoRefreshFlag!=0);
  m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(
      (m_AutoRefreshFlag==0) ||
      (m_pDisableAutoRefreshCheckBox->isChecked()!=0));

  return;
}

void DEBUGLOGVIEWERWIDGET_C::CheckFileDateTimeSlot(void)
{
  QFileInfo FileInfo;


  /* Make sure there is a pathname. */
  if (m_Pathname.isEmpty()==0)
  {
    /* Get info about the file. */
    FileInfo.setFile(m_Pathname);

    /* If the file has been modified since last read. */
    if (m_LastModifiedDateTime!=FileInfo.lastModified())
    {
      /* Enable/disable button and checkbox depending on settings. */
      UpdateWidgets();

      /* Reload debug log only if autorefresh is active and
          "Disable autorefresh" is not checked. */
      if ( (m_AutoRefreshFlag!=0) &&
          (m_pDisableAutoRefreshCheckBox->isChecked()==0) )
        LoadDebugLog();
    }
  }

  return;
}

void DEBUGLOGVIEWERWIDGET_C::ButtonBoxButtonClickedSlot(
    QAbstractButton *pButton)
{
  switch(m_pButtonBox->standardButton(pButton))
  {
    case QDialogButtonBox::Apply:
      LoadDebugLog();
      break;
    default:
      break;
  }

  return;
}


#undef    DEBUGLOGVIEWERWIDGET_CPP
