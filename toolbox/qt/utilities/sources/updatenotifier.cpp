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
*** \file updatenotifier.cpp
*** \brief updatenotifier.h implementation file.
*** \details Implementation file for updatenotifier.h.
**/


/** Identifier for updatenotifier.cpp. **/
#define   UPDATENOTIFIER_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "updatenotifier.h"
#ifdef    DEBUG_UPDATENOTIFIER_CPP
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_UPDATENOTIFIER_CPP */
#include  "debuglog.h"
//#include  "messagelog.h"

#include  <QTimer>
#include  <QNetworkAccessManager>
#include  <QNetworkRequest>
#include  <QNetworkReply>
//#include  <QPushButton>
//#include  <QFileInfo>


/****
*****
***** DEFINES
*****
****/

/**
*** \brief Update timer.
*** \details Time between checks updates.
**/
#define   UPDATETIMER_RATE    (24*60*60*1000)    /* 1 hour, in milliseconds */


/**
*** \brief Update timer.
*** \details Time between checks updates.
**/
//#define   UPDATETIMER_RATE    (24*60*60*1000)    /* 1 hour, in milliseconds */

/**
*** \brief Information tab index.
*** \details Index of the information tab in the about widget.
***/
//#define   ABOUTTAB_INFORMATION  (0)

/**
*** \brief License tab index.
*** \details Index of the license tab in the about widget.
***/
//#define   ABOUTTAB_LICENSE      (1)


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
#if 0
void UPDATENOTIFIER_C::SetExecutableNameAndVersionText(void)
{
  DEBUGLOG_Printf0("UPDATENOTIFIER_C::SetExecutableNameAndVersionText()");
  DEBUGLOG_LogIn();

  m_pProgramVersionLabel->setText(m_ExecutableName+" Version ("+m_Version+")");

  DEBUGLOG_LogOut();
  return;
}
#endif
UPDATENOTIFIER_C::UPDATENOTIFIER_C(void)//QWidget *pParent) : QWidget(pParent)
{
  DEBUGLOG_Printf0("UPDATENOTIFIER_C::UPDATENOTIFIER_C()");
//  DEBUGLOG_Printf1("UPDATENOTIFIER_C::UPDATENOTIFIER_C(%p)",pParent);
  DEBUGLOG_LogIn();

  /* Initialize members. */
  m_pNetworkAccess=NULL;
  m_pTimer=NULL;
  m_CheckingFlag=false;

  /* Network access. */
  m_pNetworkAccess=new QNetworkAccessManager;
  connect(m_pNetworkAccess,SIGNAL(finished(QNetworkReply*)),
      this,SLOT(DownloadCompleteSlot(QNetworkReply*)));

  DEBUGLOG_LogOut();
  return;
}

UPDATENOTIFIER_C::~UPDATENOTIFIER_C(void)
{
  DEBUGLOG_Printf0("UPDATENOTIFIER_C::~UPDATENOTIFIER_C()");
  DEBUGLOG_LogIn();

  if (m_pTimer!=NULL)
    delete m_pTimer;
  if (m_pNetworkAccess!=NULL)
    delete m_pNetworkAccess;

  DEBUGLOG_LogOut();
  return;
}























void UPDATENOTIFIER_C::SetURL(QString URL)
{
  DEBUGLOG_Printf2("UPDATENOTIFIER_C::SetURL(%p(%s))",&URL,qPrintable(URL));
  DEBUGLOG_LogIn();

  /* Save the URL. */
  m_URL=URL;

  /* Empty? */
  if (URL.isEmpty()==true)
  {
    /* Yes, stop the timer. */
    if (m_pTimer!=NULL)
      m_pTimer->stop();
  }
  else
  {
    /* No, create the timer (if necessary) and start it. */
    if (m_pTimer==NULL)
    {
      m_pTimer=new QTimer(this);
      connect(m_pTimer,SIGNAL(timeout()),this,SLOT(TimerTriggeredSlot()));
    }
    m_pTimer->start(UPDATETIMER_RATE);

    /* Check immediately. */
    TimerTriggeredSlot();
  }

  DEBUGLOG_LogOut();
  return;
}

void UPDATENOTIFIER_C::CheckForUpdate(void)
{
  DEBUGLOG_Printf0("UPDATENOTIFIER_C::CheckForUpdate()");
  DEBUGLOG_LogIn();

  TimerTriggeredSlot();

  DEBUGLOG_LogOut();
  return;
}

void UPDATENOTIFIER_C::TimerTriggeredSlot(void)
{
  QNetworkRequest Request;


  DEBUGLOG_Printf0("UPDATENOTIFIER_C::TimerTriggeredSlot()");
  DEBUGLOG_LogIn();

  if ( (m_URL.isEmpty()==false) && (m_CheckingFlag==false) )
  {
    m_CheckingFlag=true;

    /* Send the request. */
    Request.setUrl(m_URL);
    Request.setRawHeader("User-Agent","Mozilla Firefox");
        // QNetworkRequest seems to default to "Mozilla" for the user agent
        //   and sourceforge has implemented blocking for certain user agents.
    m_pNetworkAccess->get(Request);
  }

  DEBUGLOG_LogOut();
  return;
}

void UPDATENOTIFIER_C::DownloadCompleteSlot(QNetworkReply *pReply)
{
  QVariant RedirectURL;
  QNetworkRequest Request;
  QByteArray Data;


  DEBUGLOG_Printf1("UPDATENOTIFIER_C::DownloadCompleteSlot(%p)",pReply);
  DEBUGLOG_LogIn();

  /* Being redirected? */
  RedirectURL=pReply->attribute(QNetworkRequest::RedirectionTargetAttribute);
  if (RedirectURL!=QVariant())
  {
    Request.setUrl(RedirectURL.toString());
    Request.setRawHeader("User-Agent","Mozilla Firefox");
        // See previous comment about user agent.
    m_pNetworkAccess->get(Request);
  }
  else
  {
    /* Read the data. */
    Data=pReply->readAll();
    if (Data==QByteArray())
      emit VersionSignal(QString());
    else
    {
      /* Convert the data to a string. */
      QString DataString(Data);

      /* Inform the user. */
      emit VersionSignal(DataString);
    }

    m_CheckingFlag=false;
  }

  pReply->deleteLater();

  DEBUGLOG_LogOut();
  return;
}


#undef    UPDATENOTIFIER_CPP
