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
*** \file debuglogviewerwidget.h
*** \brief Reads and displays the debug log.
*** \details Read the debug log and display it in a widget.
**/


#ifndef   DEBUGLOGVIEWERWIDGET_H
#define   DEBUGLOGVIEWERWIDGET_H


/****
*****
***** INCLUDES
*****
****/

#include  "ui_debuglogviewerwidget.h"
#include  <QDateTime>


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

/**
*** \brief Reads and displays the debug log.
*** \details Read the debug log and display it in a widget.
**/
class DEBUGLOGVIEWERWIDGET_C :
    public QWidget, private Ui::DEBUGLOGVIEWERWIDGETUI_C
{
  Q_OBJECT

  public:
    /**
    *** \brief Constructor.
    *** \details Constructor.
    *** \param pParent Pointer to parent object.
    **/
    DEBUGLOGVIEWERWIDGET_C(QWidget *pParent=NULL);
    /**
    *** \brief Destructor.
    *** \details Destructor.
    **/
    ~DEBUGLOGVIEWERWIDGET_C(void);
    /**
    *** \brief Set the autorefresh flag.
    *** \details Sets the state of the autorefresh flag.
    *** \param AutoRefreshFlag Automatically refresh the widget.\n
    ***   0 - Do not automatically refresh.\n
    ***   !0 - Automatically refresh.
    **/
    void SetAutoRefreshFlag(bool AutoRefreshFlag);
    /**
    *** \brief Set debug log pathname.
    *** \details Sets the pathname of the debug log.
    *** \param Pathname The pathname of the debug log.
    **/
    void SetDebugLogPathname(QString Pathname);
    /**
    *** \brief Load the file into the dialog box.
    *** \details Loads the debug log file into the dialog box.
    **/
    void LoadDebugLog(void);

  public slots:
    /**
    *** \brief Check the current date/time of the debug log file.
    *** \details Function called to compare the current date/time of the
    ***   debug log file with the last modified date/time. If different, the
    ***   dialog box is updated.
    **/
    void CheckFileDateTimeSlot(void);

  private slots:
    /**
    *** \brief Dialog button clicked.
    *** \details A button in the dialog button box was clicked.
    *** \param pButton Pointer to the button that was clicked.
    **/
    void ButtonBoxButtonClickedSlot(QAbstractButton *pButton);

  protected:
    /**
    *** \brief Debug log pathname.
    *** \details Pathname of the debug log.
    **/
    QString m_Pathname;
    /**
    *** \brief Debug log file last modified date/time.
    *** \details The last date/time the debug log file was modified.
    **/
    QDateTime m_LastModifiedDateTime;
    /**
    *** \brief Debug log file last modified date/time.
    *** \details The last date/time the debug log file was modified.
    **/
    bool m_AutoRefreshFlag;

  private:
    /**
    *** \brief Update the dialog box widgets.
    *** \details Updates the dialog box widgets depending on the internal state
    ***   of the dialog box.
    **/
    void UpdateWidgets(void);
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


#endif    /* DEBUGLOGVIEWERWIDGET_H */
