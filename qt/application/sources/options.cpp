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
*** \file options.cpp
*** \brief options.h implementation.
*** \details Implementation file for options.h.
***
**/


/** Identifier for options.cpp. **/
#define   OPTIONS_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "options.h"
#ifdef    DEBUG_OPTIONS_CPP
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_OPTIONS_CPP */
#include  "debuglog.h"
#include  "messagelog.h"


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

OPTIONS_C::OPTIONS_C(void)
{
  DEBUGLOG_Printf0("OPTIONS_C::OPTIONS_C()");
  DEBUGLOG_LogIn();

  m_BackgroundColor=QColor();
  m_DateTimeOptions.Flags=DATETIMEFLAG_4DIGITYEAR;
  m_DateTimeOptions.DateStyleIndex=-1;
  m_Font=QFont();
  m_Margin=0;
  m_TextColor=QColor();
  m_UnitFormatIndex=-1;
  m_UseSystemBackgroundColorFlag=true;
  m_UseSystemFontFlag=true;
  m_UseSystemTextColorFlag=true;

  DEBUGLOG_LogOut();
  return;
}

OPTIONS_C::OPTIONS_C(OPTIONS_C *pOptions)
{
  DEBUGLOG_Printf1("OPTIONS_C::OPTIONS_C(%p)",pOptions);
  DEBUGLOG_LogIn();

  *this=*pOptions;

  DEBUGLOG_LogOut();
  return;
}

OPTIONS_C::~OPTIONS_C(void)
{
  DEBUGLOG_Printf0("OPTIONS_C::~OPTIONS_C()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return;
}

void OPTIONS_C::Convert(DATETIMEOPTIONS_T *pDateTimeOptions)
{
  DEBUGLOG_Printf1("OPTIONS_C::Convert(%p)",pDateTimeOptions);
  DEBUGLOG_LogIn();

  /* Parameter checking. */
  if (pDateTimeOptions!=NULL)
    memcpy(pDateTimeOptions,&m_DateTimeOptions,sizeof(*pDateTimeOptions));

  DEBUGLOG_LogOut();
  return;
}

QString OPTIONS_C::BuildStyleSheetString(void) const
{
  QString StyleSheetString;


  DEBUGLOG_Printf0("OPTIONS_C::BuildStyleSheetString()");
  DEBUGLOG_LogIn();

  /* Prepare the text color string. */
  if (GetTextColor()!=QColor())
    StyleSheetString=QString("color: rgb(%1,%2,%3")
        .arg(GetTextColor().red())
        .arg(GetTextColor().green())
        .arg(GetTextColor().blue())+");";

  /* Prepare the background color string. */
  if (GetBackgroundColor()!=QColor())
    StyleSheetString+=QString("background-color: rgb(%1,%2,%3")
      .arg(GetBackgroundColor().red())
      .arg(GetBackgroundColor().green())
      .arg(GetBackgroundColor().blue())+");";

  DEBUGLOG_LogOut();
  return(StyleSheetString);
}

bool OPTIONS_C::Get24HourFormatFlag(void) const
{
  DEBUGLOG_Printf0("OPTIONS_C::Get24HourFormatFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_DateTimeOptions.Flags&DATETIMEFLAG_24HOURFORMAT);
}

bool OPTIONS_C::Get4DigitYearFlag(void) const
{
  DEBUGLOG_Printf0("OPTIONS_C::Get4DigitYearFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_DateTimeOptions.Flags&DATETIMEFLAG_4DIGITYEAR);
}

QColor OPTIONS_C::GetBackgroundColor(void) const
{
  DEBUGLOG_Printf0("OPTIONS_C::GetBackgroundColor()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_BackgroundColor);
}

QFont OPTIONS_C::GetFont(void) const
{
  DEBUGLOG_Printf0("OPTIONS_C::GetFont()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_Font);
}

bool OPTIONS_C::GetLongDayOfWeekFormatFlag(void) const
{
  DEBUGLOG_Printf0("OPTIONS_C::GetLongDayOfWeekFormatFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_DateTimeOptions.Flags&DATETIMEFLAG_LONGDAYOFWEEKFORMAT);
}

bool OPTIONS_C::GetLongMonthFormatFlag(void) const
{
  DEBUGLOG_Printf0("OPTIONS_C::GetLongMonthFormatFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_DateTimeOptions.Flags&DATETIMEFLAG_LONGMONTHFORMAT);
}

int OPTIONS_C::GetMargin(void) const
{
  DEBUGLOG_Printf0("OPTIONS_C::GetMargin()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_Margin);
}

bool OPTIONS_C::GetShowDayOfWeekFlag(void) const
{
  DEBUGLOG_Printf0("OPTIONS_C::GetShowDayOfWeekFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_DateTimeOptions.Flags&DATETIMEFLAG_SHOWDAYOFWEEK);
}

bool OPTIONS_C::GetShowSecondsFlag(void) const
{
  DEBUGLOG_Printf0("OPTIONS_C::GetShowSecondsFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_DateTimeOptions.Flags&DATETIMEFLAG_SHOWSECONDS);
}

QColor OPTIONS_C::GetTextColor(void) const
{
  DEBUGLOG_Printf0("OPTIONS_C::GetTextColor()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_TextColor);
}

int OPTIONS_C::GetUnitFormatIndex(void) const
{
  DEBUGLOG_Printf0("OPTIONS_C::GetUnitFormatIndex()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_UnitFormatIndex);
}

bool OPTIONS_C::GetUseSystemBackgroundColorFlag(void) const
{
  DEBUGLOG_Printf0("OPTIONS_C::GetUseSystemBackgroundColorFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_UseSystemBackgroundColorFlag);
}

bool OPTIONS_C::GetUseSystemFontFlag(void) const
{
  DEBUGLOG_Printf0("OPTIONS_C::GetUseSystemFontFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_UseSystemFontFlag);
}

bool OPTIONS_C::GetUseSystemTextColorFlag(void) const
{
  DEBUGLOG_Printf0("OPTIONS_C::GetUseSystemTextColorFlag()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_UseSystemTextColorFlag);
}

void OPTIONS_C::Set24HourFormatFlag(bool Flag)
{
  DEBUGLOG_Printf1("OPTIONS_C::Set24HourFormatFlag(%u)",Flag);
  DEBUGLOG_LogIn();

  if (Flag==0)
    m_DateTimeOptions.Flags&=~DATETIMEFLAG_24HOURFORMAT;
  else
    m_DateTimeOptions.Flags|=DATETIMEFLAG_24HOURFORMAT;

  DEBUGLOG_LogOut();
  return;
}

void OPTIONS_C::Set4DigitYearFlag(bool Flag)
{
  DEBUGLOG_Printf1("OPTIONS_C::Set4DigitYearFlag(%u)",Flag);
  DEBUGLOG_LogIn();

  if (Flag==0)
    m_DateTimeOptions.Flags&=~DATETIMEFLAG_4DIGITYEAR;
  else
    m_DateTimeOptions.Flags|=DATETIMEFLAG_4DIGITYEAR;

  DEBUGLOG_LogOut();
  return;
}

void OPTIONS_C::SetBackgroundColor(QColor Color)
{
  DEBUGLOG_Printf1("OPTIONS_C::SetBackgroundColor(%p)",&Color);
  DEBUGLOG_LogIn();

  m_BackgroundColor=Color;

  DEBUGLOG_LogOut();
  return;
}

void OPTIONS_C::SetFont(QFont Font)
{
  DEBUGLOG_Printf1("OPTIONS_C::SetFont(%p)",&Font);
  DEBUGLOG_LogIn();

  m_Font=Font;

  DEBUGLOG_LogOut();
  return;
}

void OPTIONS_C::SetLongDayOfWeekFormatFlag(bool Flag)
{
  DEBUGLOG_Printf1("OPTIONS_C::SetLongDayOfWeekFormatFlag(%u)",Flag);
  DEBUGLOG_LogIn();

  if (Flag==0)
    m_DateTimeOptions.Flags&=~DATETIMEFLAG_LONGDAYOFWEEKFORMAT;
  else
    m_DateTimeOptions.Flags|=DATETIMEFLAG_LONGDAYOFWEEKFORMAT;

  DEBUGLOG_LogOut();
  return;
}

void OPTIONS_C::SetLongMonthFormatFlag(bool Flag)
{
  DEBUGLOG_Printf1("OPTIONS_C::SetLongMonthFormatFlag(%u)",Flag);
  DEBUGLOG_LogIn();

  if (Flag==0)
    m_DateTimeOptions.Flags&=~DATETIMEFLAG_LONGMONTHFORMAT;
  else
    m_DateTimeOptions.Flags|=DATETIMEFLAG_LONGMONTHFORMAT;

  DEBUGLOG_LogOut();
  return;
}

void OPTIONS_C::SetMargin(int Margin)
{
  DEBUGLOG_Printf1("OPTIONS_C::SetMargin(%p)",&Margin);
  DEBUGLOG_LogIn();

  m_Margin=Margin;

  DEBUGLOG_LogOut();
  return;
}

void OPTIONS_C::SetShowDayOfWeekFlag(bool Flag)
{
  DEBUGLOG_Printf1("OPTIONS_C::SetShowDayOfWeekFlag(%u)",Flag);
  DEBUGLOG_LogIn();

  if (Flag==0)
    m_DateTimeOptions.Flags&=~DATETIMEFLAG_SHOWDAYOFWEEK;
  else
    m_DateTimeOptions.Flags|=DATETIMEFLAG_SHOWDAYOFWEEK;

  DEBUGLOG_LogOut();
  return;
}

void OPTIONS_C::SetShowSecondsFlag(bool Flag)
{
  DEBUGLOG_Printf1("OPTIONS_C::SetShowSecondsFlag(%u)",Flag);
  DEBUGLOG_LogIn();

  if (Flag==0)
    m_DateTimeOptions.Flags&=~DATETIMEFLAG_SHOWSECONDS;
  else
    m_DateTimeOptions.Flags|=DATETIMEFLAG_SHOWSECONDS;

  DEBUGLOG_LogOut();
  return;
}

void OPTIONS_C::SetTextColor(QColor Color)
{
  DEBUGLOG_Printf1("OPTIONS_C::SetTextColor(%p)",&Color);
  DEBUGLOG_LogIn();

  m_TextColor=Color;

  DEBUGLOG_LogOut();
  return;
}

void OPTIONS_C::SetUnitFormatIndex(int Index)
{
  DEBUGLOG_Printf1("OPTIONS_C::SetUnitFormatIndex(%d)",Index);
  DEBUGLOG_LogIn();

  m_UnitFormatIndex=Index;

  DEBUGLOG_LogOut();
  return;
}

void OPTIONS_C::SetUseSystemBackgroundColorFlag(bool Flag)
{
  DEBUGLOG_Printf1("OPTIONS_C::SetUseSystemBackgroundColorFlag(%u)",Flag);
  DEBUGLOG_LogIn();

  m_UseSystemBackgroundColorFlag=Flag;
  if (Flag==true)
    SetBackgroundColor(QColor());

  DEBUGLOG_LogOut();
  return;
}

void OPTIONS_C::SetUseSystemFontFlag(bool Flag)
{
  DEBUGLOG_Printf1("OPTIONS_C::SetUseSystemFontFlag(%u)",Flag);
  DEBUGLOG_LogIn();

  m_UseSystemFontFlag=Flag;
  if (Flag==true)
    SetFont(QFont());

  DEBUGLOG_LogOut();
  return;
}

void OPTIONS_C::SetUseSystemTextColorFlag(bool Flag)
{
  DEBUGLOG_Printf1("OPTIONS_C::SetUseSystemTextColorFlag(%u)",Flag);
  DEBUGLOG_LogIn();

  m_UseSystemTextColorFlag=Flag;
  if (Flag==true)
    SetTextColor(QColor());

  DEBUGLOG_LogOut();
  return;
}

bool OPTIONS_C::operator==(OPTIONS_C const RHS) const
{
  bool Return;


  DEBUGLOG_Printf1("OPTIONS_C::operator==(%p)",&RHS);
  DEBUGLOG_LogIn();

  Return=
      (m_BackgroundColor==RHS.m_BackgroundColor) &&
      (m_DateTimeOptions.DateStyleIndex==RHS.m_DateTimeOptions.DateStyleIndex) &&
      (m_DateTimeOptions.Flags==RHS.m_DateTimeOptions.Flags) &&
      (m_Font==RHS.m_Font) &&
      (m_Margin==RHS.m_Margin) &&
      (m_TextColor==RHS.m_TextColor) &&
      (m_UnitFormatIndex==RHS.m_UnitFormatIndex) &&
      (m_UseSystemBackgroundColorFlag==RHS.m_UseSystemBackgroundColorFlag) &&
      (m_UseSystemFontFlag==RHS.m_UseSystemFontFlag) &&
      (m_UseSystemTextColorFlag==RHS.m_UseSystemTextColorFlag);

  DEBUGLOG_LogOut();
  return(Return);
}

bool OPTIONS_C::operator!=(OPTIONS_C const RHS) const
{
  DEBUGLOG_Printf1("OPTIONS_C::operator!=(%p)",&RHS);
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(!((*this)==RHS));
}

OPTIONS_C & OPTIONS_C::operator=(OPTIONS_C const &RHS)
{
  m_BackgroundColor=RHS.m_BackgroundColor;
  m_DateTimeOptions=RHS.m_DateTimeOptions;
  m_Font=RHS.m_Font;
  m_Margin=RHS.m_Margin;
  m_TextColor=RHS.m_TextColor;
  m_UnitFormatIndex=RHS.m_UnitFormatIndex;
  m_UseSystemBackgroundColorFlag=RHS.m_UseSystemBackgroundColorFlag;
  m_UseSystemFontFlag=RHS.m_UseSystemFontFlag;
  m_UseSystemTextColorFlag=RHS.m_UseSystemTextColorFlag;

  return(*this);
}


#undef    OPTIONS_CPP
