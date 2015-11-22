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
*** \file aboutwidgetplugin.cpp
*** \brief aboutwidgetplugin.h implementation file.
*** \details Implementation file for aboutplugin.h.
**/


/** Identifier for aboutwidgetplugin.cpp. **/
#define   ABOUTWIDGETPLUGIN_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "aboutwidgetplugin.h"
#include  "aboutwidget.h"
#include  "toolboxwidgetsinterface.h"

#include  <QtPlugin>


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

ABOUTWIDGETPLUGIN_C::ABOUTWIDGETPLUGIN_C(QObject *pParent)
    : QObject(pParent)
{
  m_InitializedFlag=false;

  return;
}

QWidget * ABOUTWIDGETPLUGIN_C::createWidget(QWidget *pParent)
{
  return(new ABOUTWIDGET_C(pParent));
}

QString ABOUTWIDGETPLUGIN_C::domXml(void) const
{
  QString XML;


  XML="<ui language=\"c++\">\n"
      " <widget class=\"ABOUTWIDGET_C\""
      " name=\"m_pAboutWidget\">\n"
      "  <property name=\"toolTip\" >\n"
      "   <string>Tool tip</string>\n"
      "  </property>\n"
      "  <property name=\"whatsThis\" >\n"
      "   <string>What's this?</string>\n"
      "  </property>\n"
      " </widget>\n"
      "</ui>\n";

  return(XML);
}

QString ABOUTWIDGETPLUGIN_C::group(void) const
{
  return(TOOLBOXWIDGETSINTERFACE_DESIGNER_GROUPNAME);
}

QIcon ABOUTWIDGETPLUGIN_C::icon(void) const
{
  return(QIcon());
}

QString ABOUTWIDGETPLUGIN_C::includeFile(void) const
{
  return("aboutwidget.h");
}

void ABOUTWIDGETPLUGIN_C::initialize(QDesignerFormEditorInterface *)
{
  if (m_InitializedFlag)
    return;

  m_InitializedFlag=true;
}

bool ABOUTWIDGETPLUGIN_C::isContainer(void) const
{
  return(false);
}

bool ABOUTWIDGETPLUGIN_C::isInitialized(void) const
{
  return(m_InitializedFlag);
}

QString ABOUTWIDGETPLUGIN_C::name(void) const
{
  return("ABOUTWIDGET_C");
}

QString ABOUTWIDGETPLUGIN_C::toolTip(void) const
{
  return("");
}

QString ABOUTWIDGETPLUGIN_C::whatsThis(void) const
{
  return("");
}


#undef    ABOUTWIDGETPLUGIN_CPP
