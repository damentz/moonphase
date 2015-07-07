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
*** \file messagelogviewerwidget.h
*** \brief Reads and displays the message log.
*** \details Read the message log and display it in a widget.
**/


#ifndef   MESSAGELOGVIEWERWIDGET_H
#define   MESSAGELOGVIEWERWIDGET_H


/****
*****
***** INCLUDES
*****
****/

#include  "ui_messagelogviewerwidget.h"
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

class MESSAGESTABLEMODEL_C;
class QSortFilterProxyModel;

/**
*** \brief Reads and displays the message log.
*** \details Read the message log and display it in a widget.
**/
class MESSAGELOGVIEWERWIDGET_C :
    public QWidget, private Ui::MESSAGELOGVIEWERWIDGETUI_C
{
  Q_OBJECT

  public:
    /**
    *** \brief Constructor.
    *** \details Constructor.
    *** \param pParent Pointer to parent object.
    **/
    MESSAGELOGVIEWERWIDGET_C(QWidget *pParent=NULL);
    /**
    *** \brief Destructor.
    *** \details Destructor.
    **/
    ~MESSAGELOGVIEWERWIDGET_C(void);
    /**
    *** \brief Set the autorefresh flag.
    *** \details Sets the state of the autorefresh flag.
    *** \param AutoRefreshFlag Automatically refresh the widget.\n
    ***   0 - Do not automatically refresh.\n
    ***   !0 - Automatically refresh.
    **/
    void SetAutoRefreshFlag(bool AutoRefreshFlag);
    /**
    *** \brief Set the merge duplicates flag.
    *** \details Sets the state of the merge duplicates flag.
    *** \param MergeDuplicatesFlag Remove paths flag\n
    ***   0 - Do not strip leading directory from pathname.\n
    ***   !0 - Strip leading directory from pathname.
    **/
    void SetMergeDuplicatesFlag(bool MergeDuplicatesFlag);
    /**
    *** \brief Set the remove paths flag.
    *** \details Sets the state of the remove paths flag.
    *** \param RemovePathsFlag Remove paths flag\n
    ***   0 - Do not strip leading directories from pathname.\n
    ***   !0 - Strip leading directories from pathname.
    **/
    void SetRemovePathsFlag(bool RemovePathsFlag);
    /**
    *** \brief Set message log pathname.
    *** \details Sets the pathname of the message log.
    *** \param Pathname The pathname of the message log.
    **/
    void SetMessageLogPathname(QString Pathname);
    /**
    *** \brief Load the file into the dialog box.
    *** \details Loads the message log file into the dialog box.
    **/
    void LoadMessageLog(void);

  public slots:
    /**
    *** \brief Check the current date/time of the message log file.
    *** \details Function called to compare the current date/time of the
    ***   message log file with the last modified date/time. If different, the
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
    *** \brief Message log pathname.
    *** \details Pathname of the message log.
    **/
    QString m_Pathname;
    /**
    *** \brief Message log file last modified date/time.
    *** \details The last date/time the message log file was modified.
    **/
    QDateTime m_LastModifiedDateTime;
    /**
    *** \brief Automatically reload message log flag.
    *** \details Flag indicating whether or not to automatically reload the
    ***   message log file when it changes in the file system.
    **/
    bool m_AutoRefreshFlag;
    /**
    *** \brief Merge same messages flag.
    *** \details Flag indicating whether or not to merge messages that are the
    ***   same.
    **/
    bool m_MergeDuplicatesFlag;
    /**
    *** \brief Remove the path from a pathname flag.
    *** \details Flag indicating whether or not to remove the path from a
    ***   pathname.
    **/
    bool m_RemovePathsFlag;
    /**
    *** \brief Message log table model.
    *** \details Table model of the message log.
    **/
    MESSAGESTABLEMODEL_C *m_pMessageLogTableModel;
    /**
    *** \brief Message log sort/filter proxy model.
    *** \details Sort/filter proxy model of the message log.
    **/
    QSortFilterProxyModel *m_pSortFilterProxyModel;

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


#endif    /* MESSAGELOGVIEWERWIDGET_H */
