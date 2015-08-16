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
*** \file messagelogviewerwidgetplugin.h
*** \brief This module provides the Qt Designer plugin interface for
***   MESSAGELOGVIEWERWIDGET_C.
*** \details This module provides the Qt Designer plugin interface for
***   MESSAGELOGVIEWERWIDGET_C.
**/


#ifndef   MESSAGELOGVIEWERWIDGETPLUGIN_H
#define   MESSAGELOGVIEWERWIDGETPLUGIN_H


/****
*****
***** INCLUDES
*****
****/

#include  <QDesignerCustomWidgetInterface>


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
***** DATA
*****
****/

/**
*** \brief This class provides the Qt Designer plugin interface for
***   MESSAGELOGVIEWERWIDGET_C.
*** \details This class provides the Qt Designer plugin interface for
***   MESSAGELOGVIEWERWIDGET_C.
**/
class MESSAGELOGVIEWERWIDGETPLUGIN_C :
    public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)

  public:
    /**
    *** \brief Constructor.
    *** \details Constructor.
    *** \param pParent Pointer to parent object.
    **/
    MESSAGELOGVIEWERWIDGETPLUGIN_C(QObject *pParent=NULL);
    /**
    *** \brief Custom plugin new instance.
    *** \details Returns a new instance of the custom plugin.
    *** \param pParent Pointer to parent widget.
    *** \returns Pointer to a new instance of the custom plugin.
    **/
    QWidget * createWidget(QWidget *pParent);
    /**
    *** \brief Returns the custom widget's properties.
    *** \details Returns the XML that is used to describe the custom widget's
    ***   properties to Qt Designer.
    *** \returns Description of the custom widget's properties.
    **/
    QString domXml(void) const;
    /**
    *** \brief Returns the custom widget group name.
    *** \details Returns the name of the group to which the custom widget
    ***    belongs.
    *** \returns Name of the custom widget's group.
    **/
    QString group(void) const;
    /**
    *** \brief Returns the custom widget icon.
    *** \details Returns the icon used to represent the custom widget in
    ***   Qt Designer's widget box.
    *** \returns Icon used to represent the custom widget in Qt Designer's
    ***     widget box.
    **/
    QIcon icon(void) const;
    /**
    *** \brief Returns the include file path.
    *** \details Returns the path to the include file that uic uses when
    ***   creating code for the custom widget.
    *** \returns Path to include file.
    **/
    QString includeFile(void) const;
    /**
    *** \brief Initializes the custom widget.
    *** \details Initializes the custom widget for use with the specified
    ***   interface.
    *** \param pInterface Pointer to interface.
    **/
    void initialize(QDesignerFormEditorInterface *pInterface);
    /**
    *** \brief Returns container widget flag.
    *** \details Returns true if the custom widget is intended to be used as a
    ***   container; otherwise returns false.
    *** \retval 0 Widget is not a container.
    *** \retval !0 Widget is a container.
    **/
    bool isContainer(void) const;
    /**
    *** \brief Returns initialized flag.
    *** \details Returns true if the custom widget has been initialized;
    ***   otherwise returns false.
    *** \retval 0 Widget is not initialized.
    *** \retval !0 Widget is initialized.
    **/
    bool isInitialized(void) const;
    /**
    *** \brief Returns the custom plugin's class name.
    *** \details Returns the class name of the custom widget supplied by the
    ***   interface. The name returned must be identical to the class name used
    ***   for the custom widget.
    *** \returns Class name of custom widget.
    **/
    QString name(void) const;
    /**
    *** \brief Returns custom widget tool tip.
    *** \details Returns a short description of the custom widget that can be
    ***   used by Qt Designer in a tool tip.
    *** \returns A short description of the widget.
    **/
    QString toolTip(void) const;
    /**
    *** \brief Returns custom widget what's this.
    *** \details Returns a description of the widget that can be used by
    ***   Qt Designer in "What's This?" help for the widget.
    *** \returns A description of the widget.
    **/
    QString whatsThis(void) const;

  private:
    /**
    *** \brief Returns custom widget initialized flag.
    *** \brief Indicates if the custom widget has been initialized.\n
    ***   0 - Widget is not initialized.\n
    ***   !0 - Widget is initialized.
    **/
    bool m_InitializedFlag;
};

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


#endif    /* MESSAGELOGVIEWERWIDGETPLUGIN_H */
