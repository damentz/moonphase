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

  m_Mode=EDITMODE_DISPLAY;
  m_InitializedFlag=false;
//  m_Options=OPTIONS_C();
//  m_OriginalOptions=OPTIONS_C();

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

void INFORMATIONOPTIONSDIALOG_C::GetOptions(OPTIONS_C &Options)
{
  int Index;
  QRadioButton *pRadioButton;


  DEBUGLOG_Printf0("INFORMATIONOPTIONSDIALOG_C::GetOptions()");
  DEBUGLOG_LogIn();

  /* Read the selected unit (if enabled). */
  if (m_pUnitsVLayout->count()>0)
  {
    for(Index=0;Index<m_pUnitsVLayout->count();Index++)
    {
      pRadioButton=dynamic_cast<QRadioButton*>(
          m_pUnitsVLayout->itemAt(Index)->widget());
      if (pRadioButton==NULL)
      {
        MESSAGELOG_Error("NULL radio button pointer.");
      }
      else if (pRadioButton->isChecked()==true)
      {
        Options.SetUnitFormatIndex(Index);
        break;
      }
    }
  }

  /* Get the time options. */
  Options.Set24HourFormatFlag(m_p24HourFormatCheckBox->isChecked());
  Options.SetShowSecondsFlag(m_pShowSecondsCheckBox->isChecked());

  /* Get the date options. */
  if (m_pStyleComboBox->count()>0)
    Options.SetUnitFormatIndex(m_pStyleComboBox->currentIndex());
  Options.SetLongMonthFormatFlag(m_pLongMonthFormatCheckBox->isChecked());
  Options.Set4DigitYearFlag(m_p4DigitYearCheckBox->isChecked());
  Options.SetShowDayOfWeekFlag(m_pShowDayOfWeekCheckBox->isChecked());
  Options.SetLongDayOfWeekFormatFlag(
      m_pLongDayOfWeekFormatCheckBox->isChecked());

  /* Get the margin. */
  Options.SetMargin(m_pMarginSpinBox->value());

  /* Get the system font flag and font. */
  Options.SetUseSystemFontFlag(m_pUseSystemFontCheckBox->isChecked());
  if (Options.GetUseSystemFontFlag()==false)
    Options.SetFont(m_Options.GetFont());
  else
    Options.SetFont(QFont());

  /* Get the system text color flag and font. */
  Options.SetUseSystemTextColorFlag(
      m_pUseSystemTextColorCheckBox->isChecked());
  if (m_pUseSystemTextColorCheckBox->isChecked()==false)
    Options.SetTextColor(m_pTextColorButton->currentColor());
  else
    Options.SetTextColor(QColor());
  Options.SetUseSystemBackgroundColorFlag(
      m_pUseSystemBackgroundColorCheckBox->isChecked());
  if (m_pUseSystemBackgroundColorCheckBox->isChecked()==false)
    Options.SetBackgroundColor(m_pBackgroundColorButton->currentColor());
  else
    Options.SetBackgroundColor(QColor());

  DEBUGLOG_LogOut();
  return;
}

void INFORMATIONOPTIONSDIALOG_C::SetData(DIALOGDATA_T const &Data)
{
  int Index;
  QRadioButton *pRadioButton;
  int SelectedIndex;


  DEBUGLOG_Printf1("INFORMATIONOPTIONSDIALOG_C::SetData(%p)",&Data);
  DEBUGLOG_LogIn();

  /* Populate the units widget or the date format combobox. */
  if ( (Data.EditMode!=EDITMODE_TIME) && (Data.EditMode!=EDITMODE_DATETIME) )
  {
    for(Index=0;Index<Data.DescriptionList.count();Index++)
    {
      pRadioButton=new QRadioButton(this);
      pRadioButton->setText(Data.DescriptionList[Index]);
      connect(pRadioButton,SIGNAL(clicked()),
          this,SLOT(OptionChangedSlot()));
      m_pUnitsVLayout->insertWidget(-1,pRadioButton);   // -1 == end of list.
    }
  }
  else if (Data.EditMode==EDITMODE_DATETIME)
    for(Index=0;Index<Data.DescriptionList.count();Index++)
      m_pStyleComboBox->addItem(Data.DescriptionList[Index]);

  /* Save any formats. */
  m_FormatList=Data.FormatsList;

  /* Show/hide various widgets depending on mode. */
  switch(Data.EditMode)
  {
    default:
      MESSAGELOG_Error("Invalid mode.");
      m_pUnitsGroupBox->setVisible(false);
      m_pFormatGroupBox->setVisible(false);
      m_pDisplayGroupBox->setVisible(false);
      break;
    case EDITMODE_DISPLAY:
      m_pUnitsGroupBox->setVisible(false);
      m_pFormatGroupBox->setVisible(false);
      break;
    case EDITMODE_UNITS:
      m_pFormatGroupBox->setVisible(false);
      break;
    case EDITMODE_TIME:
      m_pUnitsGroupBox->setVisible(false);
      m_pDateGroupBox->setVisible(false);
      break;
    case EDITMODE_DATETIME:
      m_pUnitsGroupBox->setVisible(false);
      break;
  }

  /* Save the mode. */
  m_Mode=Data.EditMode;

  /* Copy the options. */
  m_OriginalOptions=Data.Options;
  m_Options=Data.Options;

  /* Make sure the selected index is in range. */
  if (m_pUnitsVLayout->count()>0)
  {
    SelectedIndex=Data.Options.GetUnitFormatIndex();
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
  }

  /* Get the time options. */
  m_p24HourFormatCheckBox->setChecked(Data.Options.Get24HourFormatFlag());
  m_pShowSecondsCheckBox->setChecked(Data.Options.GetShowSecondsFlag());

  /* Get the date options. */
  if (m_pStyleComboBox->count()>0)
    m_pStyleComboBox->setCurrentIndex(Data.Options.GetUnitFormatIndex());
  m_pLongMonthFormatCheckBox->setChecked(Data.Options.GetLongMonthFormatFlag());
  m_p4DigitYearCheckBox->setChecked(Data.Options.Get4DigitYearFlag());
  m_pShowDayOfWeekCheckBox->setChecked(Data.Options.GetShowDayOfWeekFlag());
  m_pLongDayOfWeekFormatCheckBox->setChecked(
      Data.Options.GetLongDayOfWeekFormatFlag());

  /* Set the margin. */
  m_pMarginSpinBox->setValue(Data.Options.GetMargin());
  m_pDisplaySampleTextLabel->setMargin(Data.Options.GetMargin());

  /* Set the font. */
  m_pUseSystemFontCheckBox->setChecked(Data.Options.GetUseSystemFontFlag());
  if ( (Data.Options.GetUseSystemFontFlag()==false) &&
      (Data.Options.GetFont()!=QFont()) )
    m_pDisplaySampleTextLabel->setFont(Data.Options.GetFont());

  /* Set the colors in the color buttons. */
  m_pUseSystemTextColorCheckBox->setChecked(
      Data.Options.GetUseSystemTextColorFlag());
  if ( (Data.Options.GetUseSystemTextColorFlag()==false) &&
      (Data.Options.GetTextColor()!=QColor()) )
    m_pTextColorButton->setCurrentColor(Data.Options.GetTextColor());
  m_pUseSystemBackgroundColorCheckBox->setChecked(
      Data.Options.GetUseSystemBackgroundColorFlag());
  if ( (Data.Options.GetUseSystemBackgroundColorFlag()==false) &&
      (Data.Options.GetBackgroundColor()!=QColor()) )
    m_pBackgroundColorButton->setCurrentColor(
        Data.Options.GetBackgroundColor());

  /* Update the sample text label. */
  UpdateSampleTextLabelStyleSheet();

  /* Initialize the checkboxes and related widgets. */
  OptionChangedSlot();

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
  m_pDisplaySampleTextLabel->setStyleSheet(StyleSheetString);

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
      GetOptions(m_Options);
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
      m_pDisplaySampleTextLabel->setFont(Font);
      m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(
          m_Options!=m_OriginalOptions);
    }
  }

  DEBUGLOG_LogOut();
  return;
}

void INFORMATIONOPTIONSDIALOG_C::OptionChangedSlot(void)
{
  QRadioButton *pRadioButton;
  int Index;
  struct tm Time;
  time_t TimeT;
  struct tm *pTime;
  DATETIMEOPTIONS_T DTO;
  QString DateFormat;
  char *pString;


  DEBUGLOG_Printf0("INFORMATIONOPTIONSDIALOG_C::OptionChangedSlot()");
  DEBUGLOG_LogIn();

  /*
  ** Units group box.
  */
  /* I consider this a fix for a Qt "bug". If there is only one radio button
      in a button group, that radio button can actually be unselected. WTF?
      Why not just use a checkbox then? */
  if (m_pUnitsVLayout->count()==1)
  {
    pRadioButton=
        dynamic_cast<QRadioButton*>(m_pUnitsVLayout->itemAt(0)->widget());
    if (pRadioButton==NULL)
    {
      MESSAGELOG_Error("NULL radio button pointer.");
    }
    else if (pRadioButton->isChecked()==false)
      pRadioButton->setChecked(true);
  }

  if (m_pUnitsVLayout->count()>0)
  {
    for(Index=0;Index<m_pUnitsVLayout->count();Index++)
    {
      pRadioButton=dynamic_cast<QRadioButton*>(
          m_pUnitsVLayout->itemAt(Index)->widget());
      if (pRadioButton==NULL)
      {
        MESSAGELOG_Error("NULL radio button pointer.");
      }
      else if (pRadioButton->isChecked()==true)
      {
        m_Options.SetUnitFormatIndex(Index);
        break;
      }
    }
  }

  /*
  ** Format group box.
  */
  m_Options.Set24HourFormatFlag(m_p24HourFormatCheckBox->isChecked());
  m_Options.SetShowSecondsFlag(m_pShowSecondsCheckBox->isChecked());
  if (m_pStyleComboBox->count()>0)
    m_Options.SetUnitFormatIndex(m_pStyleComboBox->currentIndex());
  m_Options.SetLongMonthFormatFlag(m_pLongMonthFormatCheckBox->isChecked());
  m_Options.Set4DigitYearFlag(m_p4DigitYearCheckBox->isChecked());
  m_Options.SetShowDayOfWeekFlag(m_pShowDayOfWeekCheckBox->isChecked());
  if (m_Options.GetShowDayOfWeekFlag()==false)
  {
    m_Options.SetLongDayOfWeekFormatFlag(
        m_OriginalOptions.GetLongDayOfWeekFormatFlag());
    m_pLongDayOfWeekFormatCheckBox->setChecked(
        m_OriginalOptions.GetLongMonthFormatFlag());
  }
  m_Options.SetLongDayOfWeekFormatFlag(
      m_pLongDayOfWeekFormatCheckBox->isChecked());
  m_pLongDayOfWeekFormatCheckBox->setEnabled(m_Options.GetShowDayOfWeekFlag());

  /*
  ** Display group box.
  */
  m_pDisplaySampleTextLabel->setMargin(m_pMarginSpinBox->value());
  m_Options.SetMargin(m_pMarginSpinBox->value());
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
  m_pDisplaySampleTextLabel->setFont(m_Options.GetFont());
  UpdateSampleTextLabelStyleSheet();

  /* Set up a date/time. */
  memset(&Time,0,sizeof(Time));
  Time.tm_sec=45;
  Time.tm_min=23;
  Time.tm_hour=13;
  Time.tm_mday=24;
  Time.tm_mon=1-1;
  Time.tm_year=2019-1900;
  Time.tm_isdst=-1;

  /* Convert to time_t and then localtime. */
  TimeT=mktime(&Time);
  pTime=localtime(&TimeT);

  /* Copy the options,  */
  m_Options.Convert(&DTO);
  DateFormat="";
  if (m_Mode==EDITMODE_DATETIME)
    if (m_pStyleComboBox->currentIndex()!=-1)
      DateFormat=m_FormatList[m_pStyleComboBox->currentIndex()];
  if (DateTime_Print(
      (m_Mode==EDITMODE_DATETIME),pTime,qPrintable(DateFormat),&DTO,&pString)<0)
  {
    MESSAGELOG_Error("Print error. Buffer exceeded?");
    pString=strdup("Error");
  }
  m_pFormatSampleTextLabel->setText(pString);
  free(pString);

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
