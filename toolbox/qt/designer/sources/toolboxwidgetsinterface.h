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
*** \file toolboxwidgetsinterface.h
*** \brief Qt Designer custom widgets list interface.
*** \details An interface for Qt Designer to obtain a list of custom widgets.
**/


#ifndef   TOOLBOXWIDGETSINTERFACE_H
#define   TOOLBOXWIDGETSINTERFACE_H


/****
*****
***** INCLUDES
*****
****/

#include  <QtDesigner>


/****
*****
***** DEFINES
*****
****/

/**
*** \brief Custom widgets group name.
*** \details The custom widgets are placed under this group name.
**/
#define   TOOLBOXWIDGETSINTERFACE_DESIGNER_GROUPNAME  "Toolbox Widgets"


/****
*****
***** DATA TYPES
*****
****/

/**
*** \brief Qt Designer custom widgets list interface.
*** \details An interface for Qt Designer to obtain a list of custom widgets.
**/
class TOOLBOXWIDGETSINTERFACE_C :
    public QObject, public QDesignerCustomWidgetCollectionInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

  public:
    /**
    *** \brief Constructor.
    *** \details Constructor.
    *** \param pParent Pointer to parent object.
    **/
    TOOLBOXWIDGETSINTERFACE_C(QObject *pParent=NULL);
    /**
    *** \brief Returns the collection's custom widgets interface list.
    *** \details Returns a list of the collection's custom widgets interfaces.
    *** \returns The list of custom widget interface pointers.
    **/
    QList<QDesignerCustomWidgetInterface*> customWidgets(void) const;

  private:
    /**
    *** \brief Custom widget interface pointer list.
    *** \details The list of custom widget interface pointers.
    **/
    QList<QDesignerCustomWidgetInterface*> m_Widgets;
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


#endif    /* TOOLBOXWIDGETSINTERFACE_H */
