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
*** \file updatenotifier.h
*** \brief TODO
*** \details TODO
**/


#ifndef   UPDATENOTIFIER_H
#define   UPDATENOTIFIER_H


/****
*****
***** INCLUDES
*****
****/

#include  <QObject>
//#include  "ui_updatenotifier.h"
//#include  <QDateTime>


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

class QNetworkAccessManager;
class QTimer;
class QNetworkReply;

/**
*** \brief Reads and displays the debug log.
*** \details Read the debug log and display it in a widget.
**/
class UPDATENOTIFIER_C : public QObject//Widget, private Ui::UPDATENOTIFIERUI_C
{
  Q_OBJECT

  public:
    /**
    *** \brief Constructor.
    *** \details Constructor.
    **/
    UPDATENOTIFIER_C(void);
    /**
    *** \brief Destructor.
    *** \details Destructor.
    **/
    ~UPDATENOTIFIER_C(void);

    void CheckForUpdate(void);
    void SetURL(QString URL);

  private slots:
    void DownloadCompleteSlot(QNetworkReply *pReply);
    void TimerTriggeredSlot(void);

  signals:
    void EnableCheckButtonSignal(bool EnableFlag);
    void VersionSignal(QString Version);

  private:
    QString m_URL;
    /**
    *** \brief Network access manager.
    *** \details Allows the application to send network request and receive
    ***   replies.
    **/
    QNetworkAccessManager *m_pNetworkAccess;
    QTimer *m_pTimer;
    bool m_CheckingFlag;
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


#endif    /* UPDATENOTIFIER_H */
