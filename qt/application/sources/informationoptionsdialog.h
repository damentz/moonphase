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
    *** \brief Read options.
    *** \details Read the options from the widgets.
    *** \returns Options.
    **/
    OPTIONS_C & GetOptions(void);

    /**
    *** \brief Set options.
    *** \details Set the options to the widgets.
    *** \param Options Options.
    **/
    void SetOptions(OPTIONS_C const &Options);

    /**
    *** \brief Set unit list.
    *** \details Set the list of units.
    *** \param List Unit list.
    **/
    void SetUnitList(QList<QString> List);

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
    *** \brief A checkbox changed.
    *** \details On of the checkboxes (font, text, background) was changed.
    **/
    void CheckBoxChangedSlot(void);

    /**
    *** \brief Margin changed.
    *** \details The margin changed.
    *** \param Margin Size (in pixels) of area around text.
    **/
    void MarginChangedSlot(int Margin);

    /**
    *** \brief Radio button selection changed.
    *** \details A unit radio button selection changed.
    **/
    void RadioButtonClickedSlot(void);

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
    *** \brief Widget is initialized.
    *** \details The widget is initialized.
    **/
    bool m_InitializedFlag;

    /**
    *** \brief Original options.
    *** \details The options when the dialog box was started.
    **/
    OPTIONS_C m_OriginalOptions;

    /**
    *** \brief Current options.
    *** \details The current state of the options.
    **/
    OPTIONS_C m_Options;
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
