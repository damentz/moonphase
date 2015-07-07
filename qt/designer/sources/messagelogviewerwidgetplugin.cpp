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
*** \file messagelogviewerwidgetplugin.cpp
*** \brief messagelogviewerwidgetplugin.h implementation file.
*** \details Implementation file for messagelogviewerplugin.h.
**/


/** Identifier for messagelogviewerwidgetplugin.cpp. **/
#define   MESSAGELOGVIEWERWIDGETPLUGIN_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "messagelogviewerwidgetplugin.h"
#include  "messagelogviewerwidget.h"
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

MESSAGELOGVIEWERWIDGETPLUGIN_C::MESSAGELOGVIEWERWIDGETPLUGIN_C(QObject *pParent)
    : QObject(pParent)
{
  m_InitializedFlag=false;

  return;
}

QWidget * MESSAGELOGVIEWERWIDGETPLUGIN_C::createWidget(QWidget *pParent)
{
  return(new MESSAGELOGVIEWERWIDGET_C(pParent));
}

QString MESSAGELOGVIEWERWIDGETPLUGIN_C::domXml(void) const
{
  QString XML;


  XML="<ui language=\"c++\">\n"
      " <widget class=\"MESSAGELOGVIEWERWIDGET_C\""
      " name=\"m_pMessageLogViewerWidget\">\n"
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

QString MESSAGELOGVIEWERWIDGETPLUGIN_C::group(void) const
{
  return(TOOLBOXWIDGETSINTERFACE_DESIGNER_GROUPNAME);
}

QIcon MESSAGELOGVIEWERWIDGETPLUGIN_C::icon(void) const
{
  return(QIcon());
}

QString MESSAGELOGVIEWERWIDGETPLUGIN_C::includeFile(void) const
{
  return("messagelogviewerwidget.h");
}

void MESSAGELOGVIEWERWIDGETPLUGIN_C::initialize(QDesignerFormEditorInterface *)
{
  if (m_InitializedFlag)
    return;

  m_InitializedFlag=true;
}

bool MESSAGELOGVIEWERWIDGETPLUGIN_C::isContainer(void) const
{
  return(false);
}

bool MESSAGELOGVIEWERWIDGETPLUGIN_C::isInitialized(void) const
{
  return(m_InitializedFlag);
}

QString MESSAGELOGVIEWERWIDGETPLUGIN_C::name(void) const
{
  return("MESSAGELOGVIEWERWIDGET_C");
}

QString MESSAGELOGVIEWERWIDGETPLUGIN_C::toolTip(void) const
{
  return("");
}

QString MESSAGELOGVIEWERWIDGETPLUGIN_C::whatsThis(void) const
{
  return("");
}


#undef    MESSAGELOGVIEWERWIDGETPLUGIN_CPP
