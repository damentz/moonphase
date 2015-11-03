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
*** \file informationpaneldialog.h
*** \brief TODO.
*** \details TODO.
**/


#ifndef   INFORMATIONPANELDIALOG_H
#define   INFORMATIONPANELDIALOG_H


/****
*****
***** INCLUDES
*****
****/

#include  "ui_informationpaneldialog.h"

#include  "options.h"
//#include  "moonanimation.h"
//#include  "moondata.h"

//#include  <QSystemTrayIcon>


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

//class QLabel;

/**
*** \brief TODO
*** \details TODO
**/
class INFORMATIONPANELDIALOG_C : public QDialog, public Ui::INFORMATIONPANELDIALOGUI_C
{
  Q_OBJECT

  public:
    /**
    *** \brief Constructor.
    *** \details Constructor.
    *** \param pParent Pointer to parent widget.
    **/
    INFORMATIONPANELDIALOG_C(QWidget *pParent=NULL);

    /**
    *** \brief Destructor.
    *** \details Destructor.
    **/
    ~INFORMATIONPANELDIALOG_C(void);

    /**
    *** \brief Set line text and options.
    *** \details Sets the text and options for a line in the dialog box.
    *** \param Index Line number.
    *** \param Text Line text.
    *** \param Options Options for the line (color, font, etc.).
    **/
    void SetLine(int Index,QString const Text,OPTIONS_C const &Options);

    /**
    *** \brief Set line count.
    *** \details Sets the number of lines in the dialog box.
    *** \param Count Line count.
    **/
    void SetLineCount(int Count);

  protected:
    /**
    *** \brief Close event handler.
    *** \details Handler called when a window close event occurs.
    *** \param pEvent Close event data.
    **/
    void closeEvent(QCloseEvent *pEvent);

  private slots:
    /**
    *** \brief Close button clicked.
    *** \details The Close button in the dialog box was clicked.
    **/
    void CloseButtonClickedSlot(void);
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


#endif    /* INFORMATIONPANELDIALOG_H */
