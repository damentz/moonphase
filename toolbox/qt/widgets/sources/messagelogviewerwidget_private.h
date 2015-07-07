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
*** \file messagelogviewerwidget_private.h
*** \brief Message log viewer private classes.
*** \details Private classes for the message log viewer widget.
**/


#ifndef   MESSAGELOGVIEWERWIDGET_PRIVATE_H
#define   MESSAGELOGVIEWERWIDGET_PRIVATE_H


/****
*****
***** INCLUDES
*****
****/


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

class QSortFilterProxyModel;

/**
*** \brief Message log table model.
*** \details Table model of the message log.
***/
class MESSAGESTABLEMODEL_C : public QAbstractTableModel
{
  public:
    /**
    *** \brief Column list.
    *** \details The list of columns in the widget.
    **/
    typedef enum enumCOLUMN
    {
      FIRST=0,
      FILENAME=0,
      LINENUMBER=1,
      TYPE=2,
      MESSAGE=3,
      LAST=3,
      COUNT=4
    } COLUMN_E;

    /**
    *** \brief Message contect.
    *** \details Contents of the message.
    ***/
    typedef struct structMESSAGE
    {
      /**
      *** \brief Message pathname.
      *** \details Pathname of the file that created the message.
      ***/
      QString Filename;
      /**
      *** \brief Message line number.
      *** \details Line number of the message.
      ***/
      int LineNumber;
      /**
      *** \brief Message type.
      *** \details Type of the message.
      ***/
      QString Type;
      /**
      *** \brief Message test.
      *** \details Content of the message.
      ***/
      QString Message;
    } MESSAGE_T;

  public:
    /**
    *** \brief Constructor.
    *** \details Constructor.
    *** \param pParent Pointer to parent object.
    **/
    MESSAGESTABLEMODEL_C(QObject *pParent=NULL);
    /**
    *** \brief Destructor.
    *** \details Destructor.
    **/
    ~MESSAGESTABLEMODEL_C(void);
    /**
    *** \brief Returns children column count.
    *** \details Returns the column count of the children.
    *** \param Parent Model index of the parent.
    *** \returns Column count.
    **/
    int columnCount(const QModelIndex &Parent) const;
    /**
    *** \brief Clear widget.
    *** \details Removes all message data from the widget.
    **/
    void clear(void);
    /**
    *** \brief Returns model item data.
    *** \details Returns the data stored in the model item.
    *** \param Index Model item.
    *** \param Role Model item role.
    *** \returns Model item data.
    **/
    QVariant data(const QModelIndex &Index,int Role) const;
    /**
    *** \brief Returns model item flags.
    *** \details Returns the flags for the model item.
    *** \param Index Model item.
    *** \returns Refer to Qt::ItemFlags.
    **/
    Qt::ItemFlags flags(const QModelIndex &Index) const;
    /**
    *** \brief Returns model header data.
    *** \details Returns the data in the model header.
    *** \param Section Header index.
    *** \param Orientation Header orientation.
    *** \param Role Header role.
    *** \returns Header data.
    **/
    QVariant headerData(
        int Section,Qt::Orientation Orientation,int Role) const;
    /**
    *** \brief Inserts rows.
    *** \details Inserts rows into the model.
    *** \param Position If 0, the rows are prepended. If rowCount(), rows are
    ***   appended. Otherwise, rows are inserted before this position.
    *** \param Rows Number of rows.
    *** \param Parent Model index of the parent.
    *** \retval 0 Failure.
    *** \retval !0 Success.
    **/
    bool insertRows(
        int Position,int Rows,const QModelIndex &Parent=QModelIndex());
    /**
    *** \brief Removes rows.
    *** \details Removes rows from the model.
    *** \param Position Starting row.
    *** \param Rows Number of rows.
    *** \param Parent Model index of the parent.
    *** \retval 0 Failure.
    *** \retval !0 Success.
    **/
    bool removeRows(
        int Position,int Rows,const QModelIndex &Parent=QModelIndex());
    /**
    *** \brief Returns children row count.
    *** \details Returns the row count of the children.
    *** \param Parent Model index of the parent.
    *** \returns Row count.
    **/
    int rowCount(const QModelIndex &Parent) const;
    /**
    *** \brief Sets model item data.
    *** \details Sets the data stored in the model item.
    *** \param Index Model item.
    *** \param Value Data for item.
    *** \param Role Model item role.
    *** \retval 0 Failure.
    *** \retval !0 Success.
    **/
    bool setData(
        const QModelIndex &Index,const QVariant &Value,int Role=Qt::EditRole);

  private:
    /**
    *** \brief Message list.
    *** \details The list of messages.
    **/
    QList<MESSAGE_T> m_Messages;
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


#endif    /* MESSAGELOGVIEWERWIDGET_PRIVATE_H */
