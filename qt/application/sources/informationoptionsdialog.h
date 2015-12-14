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
*** \file informationoptionsdialog.h
*** \brief Information options dialog.
*** \details A dialog that allows editing of various options related to an item
***   in the information panel.
**/


#ifndef   INFORMATIONOPTIONSDIALOG_H
#define   INFORMATIONOPTIONSDIALOG_H


/****
*****
***** INCLUDES
*****
****/

#include  "ui_informationoptionsdialog.h"

#include  "information.h"
#include  "options.h"


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
*** \brief Information options dialog.
*** \details A dialog that allows editing of various options related to an item
***   in the information panel.
**/
class INFORMATIONOPTIONSDIALOG_C :
    public QDialog, public Ui::INFORMATIONOPTIONSDIALOGUI_C
{
  Q_OBJECT

  public:
    typedef struct DIALOGDATA
    {
      /**
      *** \brief Description list.
      *** \details Depending on the edit mode, a list of either units or
      ***   date/time options.
      **/
      QList<QString> DescriptionList;
      /**
      *** \brief Date/time print formats.
      *** \details The list of formats used to print the date/time.
      **/
      QList<QString> FormatsList;
      /**
      *** \brief Edit mode.
      *** \details Determines which widgets are displayed in the options dialog.
      **/
      EDITMODE_T EditMode;
      /**
      *** \brief Display options.
      *** \details Various options used when displaying a line of information.
      **/
      OPTIONS_C Options;
    } DIALOGDATA_T;

    /**
    *** \brief Constructor.
    *** \details Constructor.
    *** \param pParent Pointer to parent widget.
    **/
    INFORMATIONOPTIONSDIALOG_C(QWidget *pParent=NULL);

    /**
    *** \brief Destructor.
    *** \details Destructor.
    **/
    ~INFORMATIONOPTIONSDIALOG_C(void);

    /**
    *** \brief Get options.
    *** \details Get the options from the widgets.
    *** \param Options Storage for the options.
    **/
    void GetOptions(OPTIONS_C &Options);

    /**
    *** \brief Set dialog box data.
    *** \details Set the data needed to initialize the dialog box.
    *** \param Data Dialog box data.
    **/
    void SetData(DIALOGDATA_T const &Data);

  private:
    /**
    *** \brief Update the sample text label style sheet.
    *** \details Update the sample text label style sheet.
    **/
    void UpdateSampleTextLabelStyleSheet(void);

  public slots:
    /**
    *** \brief Background color picked.
    *** \details The background color was selected.
    *** \param Color Color selected for the background.
    **/
    void BackgroundColorPickedSlot(QColor Color);

    /**
    *** \brief Button box button clicked.
    *** \details A button in the button box was clicked.
    *** \param pButton Button data.
    **/
    void ButtonBoxButtonClickedSlot(QAbstractButton *pButton);

    /**
    *** \brief Font picked.
    *** \details The font was selected.
    **/
    void ChangeFontButtonClickedSlot(void);

    /**
    *** \brief An option changed.
    *** \details One of the option widgets in the dialog was changed.
    **/
    void OptionChangedSlot(void);

    /**
    *** \brief Text color picked.
    *** \details The text color was selected.
    *** \param Color Color selected for the text.
    **/
    void TextColorPickedSlot(QColor Color);

  signals:
    /**
    *** \brief Apply button clicked.
    *** \details The Apply button was clicked and there changes to the
    ***   corresponding line.
    *** \param Options New options to be applied to the line.
    **/
    void OptionsAppliedSignal(OPTIONS_C const &Options);

  private:
    /**
    *** \brief Edit mode.
    *** \details The edit mode of the dialog box. This determines which options
    ***   can be edited by the user.
    **/
    EDITMODE_T m_Mode;

    /**
    *** \brief Widget is initialized.
    *** \details The widget is initialized.
    **/
    bool m_InitializedFlag;

    /**
    *** \brief Current options.
    *** \details The current state of the options.
    **/
    OPTIONS_C m_Options;

    /**
    *** \brief Original options.
    *** \details The options when the dialog box was started.
    **/
    OPTIONS_C m_OriginalOptions;

    /**
    *** \brief Date/time print formats.
    *** \details The list of formats used to print the date/time.
    **/
    QList<QString> m_FormatList;
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


#endif    /* INFORMATIONOPTIONSDIALOG_H */
