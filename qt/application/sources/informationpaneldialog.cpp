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
*** \file informationpaneldialog.cpp
*** \brief informationpaneldialog.h implementation.
*** \details Implementation file for informationpaneldialog.h.
***
**/


/** Identifier for informationpaneldialog.cpp. **/
#define   INFORMATIONPANELDIALOG_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "informationpaneldialog.h"
#ifdef    DEBUG_INFORMATIONPANELDIALOG_CPP
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_INFORMATIONPANELDIALOG_CPP */
#include  "debuglog.h"
#include  "messagelog.h"

#include  "config.h"

#include  <QCloseEvent>
#include  <QLabel>


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

INFORMATIONPANELDIALOG_C::INFORMATIONPANELDIALOG_C(QWidget *pParent)
    : QDialog(pParent)
{
  DEBUGLOG_Printf1(
      "INFORMATIONPANELDIALOG_C::INFORMATIONPANELDIALOG_C(%p)",pParent);
  DEBUGLOG_LogIn();

  /* Set up the user interface. */
  setupUi(this);

  /* Set window title. */
  setWindowTitle(windowTitle()+tr(" - ")+tr(MOONPHASEQT_DISPLAYNAME));

  /* Want a panel entry. */
  setWindowFlags(Qt::Window);

  DEBUGLOG_LogOut();
  return;
}

INFORMATIONPANELDIALOG_C::~INFORMATIONPANELDIALOG_C(void)
{
  DEBUGLOG_Printf0("INFORMATIONPANELDIALOG_C::~INFORMATIONPANELDIALOG_C()");
  DEBUGLOG_LogIn();

  /* Delete all labels. */
  SetLineCount(0);

  DEBUGLOG_LogOut();
  return;
}

void INFORMATIONPANELDIALOG_C::closeEvent(QCloseEvent *pEvent)
{
  DEBUGLOG_Printf1("INFORMATIONPANELDIALOG_C::closeEvent(%p)",pEvent);
  DEBUGLOG_LogIn();

  /* Ignore the close event and fake an Ok button clicked signal. */
  pEvent->ignore();
  CloseButtonClickedSlot();

  DEBUGLOG_LogOut();
  return;
}

void INFORMATIONPANELDIALOG_C::CloseButtonClickedSlot(void)
{
  DEBUGLOG_Printf0("INFORMATIONPANELDIALOG_C::CloseButtonClickedSlot()");
  DEBUGLOG_LogIn();

  setVisible(false);

  DEBUGLOG_LogOut();
  return;
}

void INFORMATIONPANELDIALOG_C::SetLine(
    int Index,QString const Text,OPTIONS_C const &Options)
{
  QLabel *pLabel;
  QString StyleSheetString;


  DEBUGLOG_Printf4("INFORMATIONPANELDIALOG_C::SetLine(%d,%p(%s),%p)",
      Index,&Text,qPrintable(Text),&Options);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if ( (Index<0) || (Index>=m_pLabelVLayout->count()) )
  {
    MESSAGELOG_Error("Invalid index.");
  }
  else
  {
    pLabel=dynamic_cast<QLabel*>(m_pLabelVLayout->itemAt(Index)->widget());
    if (pLabel==NULL)
    {
      MESSAGELOG_Error("NULL label.");
    }
    else
    {
      pLabel->setText(Text);
      pLabel->setMargin(Options.GetMargin());
      pLabel->setFont(Options.GetFont());
      StyleSheetString=Options.BuildStyleSheetString();
      pLabel->setStyleSheet(StyleSheetString);
    }
  }

  DEBUGLOG_LogOut();
  return;
}

void INFORMATIONPANELDIALOG_C::SetLineCount(int Count)
{
  QLabel *pLabel;


  DEBUGLOG_Printf1("INFORMATIONPANELDIALOG_C::SetLineCount(%d)",Count);
  DEBUGLOG_LogIn();

  if (Count>m_pLabelVLayout->count())
  {
    while(Count>m_pLabelVLayout->count())   // Should always be one, but...
    {
      /* Add line. */
      pLabel=new QLabel(this);
      m_pLabelVLayout->insertWidget(-1,pLabel);   // -1 == end of list.
      pLabel->setAlignment(Qt::AlignHCenter);
    }
  }
  else if (Count<m_pLabelVLayout->count())
  {
    /* Clear the line. */
    dynamic_cast <QLabel*>(m_pLabelVLayout->itemAt(0)->widget())->setText("");

    /* Remove lines. */
    m_pLabelVLayout->removeItem(m_pLabelVLayout->itemAt(0));
  }

  DEBUGLOG_LogOut();
  return;
}


#undef    INFORMATIONPANELDIALOG_CPP
