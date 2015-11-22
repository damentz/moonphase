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
*** \file aboutwidget.h
*** \brief TODO
*** \details TODO
**/


#ifndef   ABOUTWIDGET_H
#define   ABOUTWIDGET_H


/****
*****
***** INCLUDES
*****
****/

#include  "ui_aboutwidget.h"
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

//class QTimer;

/**
*** \brief Reads and displays the debug log.
*** \details Read the debug log and display it in a widget.
**/
class ABOUTWIDGET_C : public QWidget, private Ui::ABOUTWIDGETUI_C
{
  Q_OBJECT

  Q_PROPERTY(QPixmap Pixmap READ GetImage WRITE SetImage)
  Q_PROPERTY(QString DisplayName READ GetDisplayName WRITE SetDisplayName)
  Q_PROPERTY(QString ExecutableName
      READ GetExecutableName WRITE SetExecutableName)
  Q_PROPERTY(QString Version READ GetVersion WRITE SetVersion)
  Q_PROPERTY(QString Information READ GetInformation WRITE SetInformation)
  Q_PROPERTY(QString License READ GetLicense WRITE SetLicense)
  Q_PROPERTY(QIcon InformationIcon
      READ GetInformationIcon WRITE SetInformationIcon)
  Q_PROPERTY(QIcon LicenseIcon READ GetLicenseIcon WRITE SetLicenseIcon)

  public:
    /**
    *** \brief Constructor.
    *** \details Constructor.
    *** \param pParent Pointer to parent object.
    **/
    ABOUTWIDGET_C(QWidget *pParent=NULL);
    /**
    *** \brief Destructor.
    *** \details Destructor.
    **/
    ~ABOUTWIDGET_C(void);

    bool GetCheckButtonEnabled(void);
    QString GetDisplayName(void);
    QString GetExecutableName(void);
    QPixmap GetImage(void);
    QString GetInformation(void);
    QIcon GetInformationIcon(void);
    QString GetLicense(void);
    QIcon GetLicenseIcon(void);
    QString GetVersion(void);

    void SetCheckButtonEnabled(bool EnabledFlag);
    void SetDisplayName(QString Name);
    void SetExecutableName(QString Name);
    void SetImage(QPixmap Pixmap);
    void SetInformation(QString Information);
    void SetInformationIcon(QIcon Icon);
    void SetLicense(QString License);
    void SetLicenseIcon(QIcon Icon);
    void SetUpdateText(QString Text);
    void SetVersion(QString Version);
    void ShowCheckForUpdateWidget(bool ShowFlag);

  private:
    void SetExecutableNameAndVersionText(void);

    QString m_ExecutableName;
    QString m_Version;
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


#endif    /* ABOUTWIDGET_H */
