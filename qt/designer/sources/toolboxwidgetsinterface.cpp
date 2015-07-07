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
*** \file toolboxwidgetsinterface.cpp
*** \brief toolboxwidgetsinterface.h implementation file.
*** \details Implementation file for toolboxwidgetsinterface.h.
**/


/** Identifier for toolboxwidgetsinterface.cpp. **/
#define   TOOLBOXWIDGETSINTERFACE_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "toolboxwidgetsinterface.h"
#include  "debuglogviewerwidgetplugin.h"
#include  "messagelogviewerwidgetplugin.h"


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

TOOLBOXWIDGETSINTERFACE_C::TOOLBOXWIDGETSINTERFACE_C(QObject *parent)
    : QObject(parent)
{
  m_Widgets.append(new DEBUGLOGVIEWERWIDGETPLUGIN_C(this));
  m_Widgets.append(new MESSAGELOGVIEWERWIDGETPLUGIN_C(this));

  return;
}

QList<QDesignerCustomWidgetInterface*>
    TOOLBOXWIDGETSINTERFACE_C::customWidgets(void) const
{
  return(m_Widgets);
}

Q_EXPORT_PLUGIN2(plugins,TOOLBOXWIDGETSINTERFACE_C)


#undef    TOOLBOXWIDGETSINTERFACE_CPP
