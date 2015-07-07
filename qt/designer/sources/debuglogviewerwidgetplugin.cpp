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
*** \file debuglogviewerwidgetplugin.cpp
*** \brief debuglogviewerwidgetplugin.h implementation file.
*** \details Implementation file for debuglogviewerplugin.h.
**/


/** Identifier for debuglogviewerwidgetplugin.cpp. **/
#define   DEBUGLOGVIEWERWIDGETPLUGIN_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "debuglogviewerwidgetplugin.h"
#include  "debuglogviewerwidget.h"
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

DEBUGLOGVIEWERWIDGETPLUGIN_C::DEBUGLOGVIEWERWIDGETPLUGIN_C(QObject *pParent)
    : QObject(pParent)
{
  m_InitializedFlag=false;

  return;
}

QWidget * DEBUGLOGVIEWERWIDGETPLUGIN_C::createWidget(QWidget *pParent)
{
  return(new DEBUGLOGVIEWERWIDGET_C(pParent));
}

QString DEBUGLOGVIEWERWIDGETPLUGIN_C::domXml(void) const
{
  QString XML;


  XML="<ui language=\"c++\">\n"
      " <widget class=\"DEBUGLOGVIEWERWIDGET_C\""
      " name=\"m_pDebugLogViewerWidget\">\n"
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

QString DEBUGLOGVIEWERWIDGETPLUGIN_C::group(void) const
{
  return(TOOLBOXWIDGETSINTERFACE_DESIGNER_GROUPNAME);
}

QIcon DEBUGLOGVIEWERWIDGETPLUGIN_C::icon(void) const
{
  return(QIcon());
}

QString DEBUGLOGVIEWERWIDGETPLUGIN_C::includeFile(void) const
{
  return("debuglogviewerwidget.h");
}

void DEBUGLOGVIEWERWIDGETPLUGIN_C::initialize(QDesignerFormEditorInterface *)
{
  if (m_InitializedFlag)
    return;

  m_InitializedFlag=true;
}

bool DEBUGLOGVIEWERWIDGETPLUGIN_C::isContainer(void) const
{
  return(false);
}

bool DEBUGLOGVIEWERWIDGETPLUGIN_C::isInitialized(void) const
{
  return(m_InitializedFlag);
}

QString DEBUGLOGVIEWERWIDGETPLUGIN_C::name(void) const
{
  return("DEBUGLOGVIEWERWIDGET_C");
}

QString DEBUGLOGVIEWERWIDGETPLUGIN_C::toolTip(void) const
{
  return("");
}

QString DEBUGLOGVIEWERWIDGETPLUGIN_C::whatsThis(void) const
{
  return("");
}


#undef    DEBUGLOGVIEWERWIDGETPLUGIN_CPP
