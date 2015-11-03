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
*** \file informationoptionsdialog.cpp
*** \brief informationoptionsdialog.h implementation.
*** \details Implementation file for informationoptionsdialog.h.
***
**/


/** Identifier for informationoptionsdialog.cpp. **/
#define   INFORMATIONOPTIONSDIALOG_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "informationoptionsdialog.h"
#ifdef    DEBUG_INFORMATIONOPTIONSDIALOG_CPP
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_INFORMATIONOPTIONSDIALOG_CPP */
#include  "debuglog.h"
#include  "messagelog.h"

#include  "config.h"

#include  <QRadioButton>
#include  <QFontDialog>


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

INFORMATIONOPTIONSDIALOG_C::INFORMATIONOPTIONSDIALOG_C(QWidget *pParent)
    : QDialog(pParent)
{
  DEBUGLOG_Printf1(
      "INFORMATIONOPTIONSDIALOG_C::INFORMATIONOPTIONSDIALOG_C(%p)",pParent);
  DEBUGLOG_LogIn();

  m_InitializedFlag=false;
  m_OriginalOptions=OPTIONS_C();
  m_Options=OPTIONS_C();

  /* Set up the user interface. */
  setupUi(this);

  /* Set window title. */
  setWindowTitle(windowTitle()+tr(" - ")+tr(MOONPHASEQT_DISPLAYNAME));

  /* Initialize the color buttons to the system colors. */
  m_pTextColorButton->setCurrentColor(
      QDialog().palette().color(QPalette::Text));
  m_pBackgroundColorButton->setCurrentColor(
      QDialog().palette().color(QPalette::Background));

  /* Disable Apply button. */
  m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(false);

  /* Allow widgets to update. */
  m_InitializedFlag=true;

  DEBUGLOG_LogOut();
  return;
}

INFORMATIONOPTIONSDIALOG_C::~INFORMATIONOPTIONSDIALOG_C(void)
{
  DEBUGLOG_Printf0("INFORMATIONOPTIONSDIALOG_C::~INFORMATIONOPTIONSDIALOG_C()");
  DEBUGLOG_LogIn();

  while(m_pUnitsVLayout->count()>0)
    delete m_pUnitsVLayout->takeAt(0)->widget();

  DEBUGLOG_LogOut();
  return;
}

OPTIONS_C & INFORMATIONOPTIONSDIALOG_C::GetOptions(void)
{
  OPTIONS_C *pOptions;
  int Index;
  QRadioButton *pRadioButton;


  DEBUGLOG_Printf0("INFORMATIONOPTIONSDIALOG_C::GetOptions()");
  DEBUGLOG_LogIn();

  /* Create the options storage. */
  pOptions=new OPTIONS_C();

  for(Index=0;m_pUnitsVLayout->count();Index++)
  {
    pRadioButton=
        dynamic_cast<QRadioButton*>(m_pUnitsVLayout->itemAt(Index)->widget());
    if (pRadioButton==NULL)
    {
      MESSAGELOG_Error("NULL radio button pointer.");
    }
    else if (pRadioButton->isChecked()==true)
    {
      pOptions->SetUnitIndex(Index);
      break;
    }
  }

  /* Get the margin. */
  pOptions->SetMargin(m_pMarginSpinBox->value());

  /* Get the system font flag and font. */
  pOptions->SetUseSystemFontFlag(m_pUseSystemFontCheckBox->isChecked());
  if (pOptions->GetUseSystemFontFlag()==false)
    pOptions->SetFont(m_Options.GetFont());
  else
    pOptions->SetFont(QFont());

  /* Get the system text color flag and font. */
  pOptions->SetUseSystemTextColorFlag(
      m_pUseSystemTextColorCheckBox->isChecked());
  if (m_pUseSystemTextColorCheckBox->isChecked()==false)
    pOptions->SetTextColor(m_pTextColorButton->currentColor());
  else
    pOptions->SetTextColor(QColor());
  pOptions->SetUseSystemBackgroundColorFlag(
      m_pUseSystemBackgroundColorCheckBox->isChecked());
  if (m_pUseSystemBackgroundColorCheckBox->isChecked()==false)
    pOptions->SetBackgroundColor(m_pBackgroundColorButton->currentColor());
  else
    pOptions->SetBackgroundColor(QColor());

  DEBUGLOG_LogOut();
  return(*pOptions);
}

void INFORMATIONOPTIONSDIALOG_C::SetOptions(OPTIONS_C const &Options)
{
  int SelectedIndex;
  QRadioButton *pRadioButton;
  QColor Color;


  DEBUGLOG_Printf1("INFORMATIONOPTIONSDIALOG_C::SetOptions(%p)",&Options);
  DEBUGLOG_LogIn();

  /* Copy the options. */
  m_OriginalOptions=Options;
  m_Options=Options;

  /* Make sure the selected index is in range. */
  SelectedIndex=Options.GetUnitIndex();
  if ( (SelectedIndex<0) || (SelectedIndex>=m_pUnitsVLayout->count()) )
  {
    MESSAGELOG_Error("Selected index out of bounds.");
    SelectedIndex=0;
  }

  /* Set the selected checkbox. */
  if (m_pUnitsVLayout->count()>0)
  {
    pRadioButton=dynamic_cast<QRadioButton*>(
        m_pUnitsVLayout->itemAt(SelectedIndex)->widget());
    if (pRadioButton==NULL)
    {
      MESSAGELOG_Error("NULL radio button pointer.");
    }
    else
      pRadioButton->setChecked(true);
  }

  /* Set the margin. */
  m_pMarginSpinBox->setValue(Options.GetMargin());
  m_pSampleTextLabel->setMargin(Options.GetMargin());

  /* Set the font. */
  m_pUseSystemFontCheckBox->setChecked(Options.GetUseSystemFontFlag());
  if ( (Options.GetUseSystemFontFlag()==false) &&
      (Options.GetFont()!=QFont()) )
    m_pSampleTextLabel->setFont(Options.GetFont());

  /* Set the colors in the color buttons. */
  m_pUseSystemTextColorCheckBox->setChecked(
      Options.GetUseSystemTextColorFlag());
  if ( (Options.GetUseSystemTextColorFlag()==false) &&
      (Options.GetTextColor()!=QColor()) )
    m_pTextColorButton->setCurrentColor(Options.GetTextColor());
  m_pUseSystemBackgroundColorCheckBox->setChecked(
      Options.GetUseSystemBackgroundColorFlag());
  if ( (Options.GetUseSystemBackgroundColorFlag()==false) &&
      (Options.GetBackgroundColor()!=QColor()) )
    m_pBackgroundColorButton->setCurrentColor(Options.GetBackgroundColor());

  /* Update the sample text label. */
  UpdateSampleTextLabelStyleSheet();

  /* Initialize the checkboxes and related widgets. */
  CheckBoxChangedSlot();

  DEBUGLOG_LogOut();
  return;
}

void INFORMATIONOPTIONSDIALOG_C::SetUnitList(QList<QString> List)
{
  QRadioButton *pRadioButton;


  DEBUGLOG_Printf1("INFORMATIONOPTIONSDIALOG_C::SetUnitList(%p)",&List);
  DEBUGLOG_LogIn();

  /* Create a radio button for each option and set the data. */
  for(int Index=0;Index<List.count();Index++)
  {
    pRadioButton=new QRadioButton(this);
    pRadioButton->setText(List[Index]);
    connect(pRadioButton,SIGNAL(clicked()),this,SLOT(RadioButtonClickedSlot()));
    m_pUnitsVLayout->insertWidget(-1,pRadioButton);   // -1 == end of list.
  }

  /* Resize the dialog to minimum size. */
  resize(minimumSizeHint());

  DEBUGLOG_LogOut();
  return;
}

void INFORMATIONOPTIONSDIALOG_C::UpdateSampleTextLabelStyleSheet(void)
{
  QString StyleSheetString;


  DEBUGLOG_Printf0(
      "INFORMATIONOPTIONSDIALOG_C::UpdateSampleTextLabelStyleSheet(%p)");
  DEBUGLOG_LogIn();

  /* Set the style sheet. */
  StyleSheetString=m_Options.BuildStyleSheetString();
  m_pSampleTextLabel->setStyleSheet(StyleSheetString);

  DEBUGLOG_LogOut();
  return;
}

void INFORMATIONOPTIONSDIALOG_C::BackgroundColorPickedSlot(QColor Color)
{
  DEBUGLOG_Printf1(
      "INFORMATIONOPTIONSDIALOG_C::BackgroundColorPickedSlot(%p)",&Color);
  DEBUGLOG_LogIn();

  if (m_InitializedFlag==true)
  {
    m_Options.SetBackgroundColor(Color);
    UpdateSampleTextLabelStyleSheet();
    m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(
        m_Options!=m_OriginalOptions);
  }

  DEBUGLOG_LogOut();
  return;
}

void INFORMATIONOPTIONSDIALOG_C::ButtonBoxButtonClickedSlot(
    QAbstractButton *pButton)
{
  DEBUGLOG_Printf1(
      "INFORMATIONOPTIONSDIALOG_C::ButtonBoxButtonClickedSlot(%p)",pButton);
  DEBUGLOG_LogIn();

  switch(m_pButtonBox->standardButton(pButton))
  {
    case QDialogButtonBox::Cancel:
      reject();
      break;
    case QDialogButtonBox::Ok:
      accept();
      break;
    case QDialogButtonBox::Apply:
      m_Options=GetOptions();
      m_OriginalOptions=m_Options;
      emit OptionsAppliedSignal(m_Options);
      m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
      break;
    default:
      break;
  }

  DEBUGLOG_LogOut();
  return;
}

void INFORMATIONOPTIONSDIALOG_C::ChangeFontButtonClickedSlot(void)
{
  QFont Font;
  bool OkFlag;


  DEBUGLOG_Printf0("INFORMATIONOPTIONSDIALOG_C::ChangeFontButtonClickedSlot()");
  DEBUGLOG_LogIn();

  Font=QFontDialog::getFont(&OkFlag,m_Options.GetFont(),this);
  if (OkFlag==true)
  {
    /* Only save if different. */
    if (Font!=QDialog::font())
    {
      m_Options.SetFont(Font);
      m_pSampleTextLabel->setFont(Font);
      m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(
          m_Options!=m_OriginalOptions);
    }
  }

  DEBUGLOG_LogOut();
  return;
}

void INFORMATIONOPTIONSDIALOG_C::CheckBoxChangedSlot(void)
{
  DEBUGLOG_Printf0("INFORMATIONOPTIONSDIALOG_C::CheckBoxChangedSlot()");
  DEBUGLOG_LogIn();

  m_pChangeFontButton->setEnabled(!m_pUseSystemFontCheckBox->isChecked());
  m_Options.SetUseSystemFontFlag(m_pUseSystemFontCheckBox->isChecked());

  m_pTextColorButton->setEnabled(!m_pUseSystemTextColorCheckBox->isChecked());
  m_Options.SetUseSystemTextColorFlag(
      m_pUseSystemTextColorCheckBox->isChecked());

  m_pBackgroundColorButton->setEnabled(
      !m_pUseSystemBackgroundColorCheckBox->isChecked());
  m_Options.SetUseSystemBackgroundColorFlag(
      m_pUseSystemBackgroundColorCheckBox->isChecked());

  /* Update the sample text label. */
  m_pSampleTextLabel->setFont(m_Options.GetFont());
  UpdateSampleTextLabelStyleSheet();

  m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(
      m_Options!=m_OriginalOptions);

  DEBUGLOG_LogOut();
  return;
}

void INFORMATIONOPTIONSDIALOG_C::MarginChangedSlot(int Margin)
{
  DEBUGLOG_Printf1("INFORMATIONOPTIONSDIALOG_C::MarginChangedSlot(%d)",Margin);
  DEBUGLOG_LogIn();

  m_pSampleTextLabel->setMargin(Margin);
  m_Options.SetMargin(Margin);
  m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(
      m_Options!=m_OriginalOptions);

  DEBUGLOG_LogOut();
  return;
}

void INFORMATIONOPTIONSDIALOG_C::RadioButtonClickedSlot(void)
{
  int Index;
  QRadioButton *pRadioButton;


  DEBUGLOG_Printf0("INFORMATIONOPTIONSDIALOG_C::RadioButtonClickedSlot()");
  DEBUGLOG_LogIn();

  for(Index=0;Index<m_pUnitsVLayout->count();Index++)
  {
    pRadioButton=
        dynamic_cast<QRadioButton*>(m_pUnitsVLayout->itemAt(Index)->widget());
    if (pRadioButton==NULL)
    {
      MESSAGELOG_Error("NULL radio button pointer.");
    }
    else if (pRadioButton->isChecked()==true)
    {
      m_Options.SetUnitIndex(Index);
      break;
    }
  }

  m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(
      m_Options!=m_OriginalOptions);

  DEBUGLOG_LogOut();
  return;
}

void INFORMATIONOPTIONSDIALOG_C::TextColorPickedSlot(QColor Color)
{
  DEBUGLOG_Printf1(
      "INFORMATIONOPTIONSDIALOG_C::TextColorPickedSlot(%p)",&Color);
  DEBUGLOG_LogIn();

  if (m_InitializedFlag==true)
  {
    m_Options.SetTextColor(Color);
    UpdateSampleTextLabelStyleSheet();
    m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(
        m_Options!=m_OriginalOptions);
  }

  DEBUGLOG_LogOut();
  return;
}


#undef    INFORMATIONOPTIONSDIALOG_CPP
