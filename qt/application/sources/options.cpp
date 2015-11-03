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

  m_UnitIndex=0;
  m_Margin=0;
  m_UseSystemFontFlag=true;
  m_Font=QFont();
  m_UseSystemTextColorFlag=true;
  m_TextColor=QColor();
  m_UseSystemBackgroundColorFlag=true;
  m_BackgroundColor=QColor();

  DEBUGLOG_LogOut();
  return;
}

OPTIONS_C::OPTIONS_C(OPTIONS_C *pOptions)
{
  DEBUGLOG_Printf1("OPTIONS_C::OPTIONS_C(%p)",pOptions);
  DEBUGLOG_LogIn();

  m_UnitIndex=pOptions->m_UnitIndex;
  m_Margin=pOptions->m_Margin;
  m_UseSystemFontFlag=pOptions->m_UseSystemFontFlag;
  m_Font=pOptions->m_Font;
  m_UseSystemTextColorFlag=pOptions->m_UseSystemTextColorFlag;
  m_TextColor=pOptions->m_TextColor;
  m_UseSystemBackgroundColorFlag=pOptions->m_UseSystemBackgroundColorFlag;
  m_BackgroundColor=pOptions->m_BackgroundColor;

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

int OPTIONS_C::GetMargin(void) const
{
  DEBUGLOG_Printf0("OPTIONS_C::GetMargin()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_Margin);
}

QColor OPTIONS_C::GetTextColor(void) const
{
  DEBUGLOG_Printf0("OPTIONS_C::GetTextColor()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_TextColor);
}

int OPTIONS_C::GetUnitIndex(void) const
{
  DEBUGLOG_Printf0("OPTIONS_C::GetUnitIndex()");
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(m_UnitIndex);
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

void OPTIONS_C::SetMargin(int Margin)
{
  DEBUGLOG_Printf1("OPTIONS_C::SetMargin(%p)",&Margin);
  DEBUGLOG_LogIn();

  m_Margin=Margin;

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

void OPTIONS_C::SetUnitIndex(int Index)
{
  DEBUGLOG_Printf1("OPTIONS_C::SetUnitIndex(%d)",Index);
  DEBUGLOG_LogIn();

  m_UnitIndex=Index;

  DEBUGLOG_LogOut();
  return;
}

void OPTIONS_C::SetUseSystemBackgroundColorFlag(bool SystemFlag)
{
  DEBUGLOG_Printf1("OPTIONS_C::SetUseSystemBackgroundColorFlag(%u)",SystemFlag);
  DEBUGLOG_LogIn();

  m_UseSystemBackgroundColorFlag=SystemFlag;
  if (SystemFlag==true)
    SetBackgroundColor(QColor());

  DEBUGLOG_LogOut();
  return;
}

void OPTIONS_C::SetUseSystemFontFlag(bool SystemFlag)
{
  DEBUGLOG_Printf1("OPTIONS_C::SetUseSystemFontFlag(%u)",SystemFlag);
  DEBUGLOG_LogIn();

  m_UseSystemFontFlag=SystemFlag;
  if (SystemFlag==true)
    SetFont(QFont());

  DEBUGLOG_LogOut();
  return;
}

void OPTIONS_C::SetUseSystemTextColorFlag(bool SystemFlag)
{
  DEBUGLOG_Printf1("OPTIONS_C::SetUseSystemTextColorFlag(%u)",SystemFlag);
  DEBUGLOG_LogIn();

  m_UseSystemTextColorFlag=SystemFlag;
  if (SystemFlag==true)
    SetTextColor(QColor());

  DEBUGLOG_LogOut();
  return;
}

bool OPTIONS_C::operator==(OPTIONS_C const RHS) const
{
  bool Return;


  DEBUGLOG_Printf1("OPTIONS_C::operator==(%p)",&RHS);
  DEBUGLOG_LogIn();

  Return=(m_UnitIndex==RHS.m_UnitIndex) &&
     (m_Margin==RHS.m_Margin) &&
     (m_UseSystemFontFlag==RHS.m_UseSystemFontFlag) &&
     (m_Font==RHS.m_Font) &&
     (m_UseSystemTextColorFlag==RHS.m_UseSystemTextColorFlag) &&
     (m_TextColor==RHS.m_TextColor) &&
     (m_UseSystemBackgroundColorFlag==RHS.m_UseSystemBackgroundColorFlag) &&
     (m_BackgroundColor==RHS.m_BackgroundColor);

  DEBUGLOG_LogOut();
  return(Return);
}

bool OPTIONS_C::operator!=(OPTIONS_C const RHS) const
{
  DEBUGLOG_Printf1("OPTIONS_C::SetMargin(%p)",&RHS);
  DEBUGLOG_LogIn();

  DEBUGLOG_LogOut();
  return(!((*this)==RHS));
}


#undef    OPTIONS_CPP
