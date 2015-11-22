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
*** \file messagelogviewerwidget.cpp
*** \brief messagelogviewerwidget.h implementation file.
*** \details Implementation file for messagelogviewerwidget.h.
**/


/** Identifier for messagelogviewerwidget.cpp. **/
#define   MESSAGELOGVIEWERWIDGET_CPP


/****
*****
***** INCLUDES
*****
****/

#include  "messagelogviewerwidget.h"
#include  "messagelogviewerwidget_private.h"

#include  <QPushButton>
#include  <QSortFilterProxyModel>
#include  <QFileInfo>


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

MESSAGELOGVIEWERWIDGET_C::MESSAGELOGVIEWERWIDGET_C(QWidget *pParent)
    : QWidget(pParent)
{
  QPushButton *pRefreshButton;


  /* Setup the user interface. */
  setupUi(this);

  /* Initialize members. */
  m_pMessageLogTableModel=new MESSAGESTABLEMODEL_C(this);
  if (m_pMessageLogTableModel!=NULL)
  {
    m_pSortFilterProxyModel=new QSortFilterProxyModel(this);
    if (m_pMessageLogTableModel!=NULL)
    {
      m_pSortFilterProxyModel->setSourceModel(m_pMessageLogTableModel);
      m_pSortFilterProxyModel->setDynamicSortFilter(true);

      m_pTableView->setModel(m_pSortFilterProxyModel);
      m_pTableView->setSortingEnabled(true);
      m_pTableView->sortByColumn(0,Qt::AscendingOrder);
      m_pTableView->resizeColumnsToContents();
      m_pTableView->resizeRowsToContents();
      m_pTableView->horizontalHeader()->setStretchLastSection(true);
//      m_pTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    }
  }

  /* Add/create a "Refresh" button. */
  pRefreshButton=m_pButtonBox->button(QDialogButtonBox::Apply);
  if (pRefreshButton!=NULL)
  {
    pRefreshButton->setText("&Refresh");
    pRefreshButton->setIcon(QIcon(":/DebugConsole/RefreshIcon"));
  }

  /* Initialize members. */
  m_Pathname=QString();
  m_AutoRefreshFlag=0;
  m_MergeDuplicatesFlag=0;
  m_RemovePathsFlag=0;
#ifdef    BUILD_PLUGIN
  QModelIndex Index;

  /* Provide some dummy text for the plugin. */
  m_pMessageLogTableModel->insertRows(
      m_pMessageLogTableModel->rowCount(QModelIndex()),2);
  Index=m_pMessageLogTableModel->index(0,0,QModelIndex());
  m_pMessageLogTableModel->setData(Index,QVariant("foo.c"));
  Index=m_pMessageLogTableModel->index(0,1,QModelIndex());
  m_pMessageLogTableModel->setData(Index,QVariant(205));
  Index=m_pMessageLogTableModel->index(0,2,QModelIndex());
  m_pMessageLogTableModel->setData(Index,QVariant("Error"));
  Index=m_pMessageLogTableModel->index(0,3,QModelIndex());
  m_pMessageLogTableModel->setData(Index,QVariant("NULL pointer"));
  Index=m_pMessageLogTableModel->index(1,0,QModelIndex());
  m_pMessageLogTableModel->setData(Index,QVariant("bar.c"));
  Index=m_pMessageLogTableModel->index(1,1,QModelIndex());
  m_pMessageLogTableModel->setData(Index,QVariant(59));
  Index=m_pMessageLogTableModel->index(1,2,QModelIndex());
  m_pMessageLogTableModel->setData(Index,QVariant("Todo"));
  Index=m_pMessageLogTableModel->index(1,3,QModelIndex());
  m_pMessageLogTableModel->setData(
      Index,QVariant("Clear unused fields in structure"));
#endif    /* BUILD_PLUGIN */

  /* Disable the "Refresh" button and the "Disable autorefresh" checkbox. */
  m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
  m_pDisableAutoRefreshCheckBox->setEnabled(false);

  return;
}

MESSAGELOGVIEWERWIDGET_C::~MESSAGELOGVIEWERWIDGET_C(void)
{
  delete m_pSortFilterProxyModel;

  return;
}

void MESSAGELOGVIEWERWIDGET_C::LoadMessageLog(void)
{
  QFile File;
  QString Data;
  QStringList Lines;
  QStringList Fields;
  QFileInfo FileInfo;
  QModelIndex Index;


  /* Make sure there is a pathname. */
  if (m_Pathname.isEmpty()==0)
  {
    /* Reset the model. */
    m_pMessageLogTableModel->clear();

    /* Open the message log file. */
    File.setFileName(m_Pathname);
    if (File.open(QFile::ReadOnly)==true)
    {
      /* Read the message log file. */
      Data=File.readAll();
      File.close();
      if (Data.isEmpty()==0)
      {
        /* Split the file into lines. */
        Lines=Data.split('\n');
        Lines.removeAt(0);  /* Remove the date/time header. */
        for(int Temp=0;Temp<Lines.count();Temp++)
        {
          QString Trimmed=Lines[Temp].trimmed();  /* Remove extra whitespace. */
          if (Trimmed.isEmpty()!=0)   /* Blank line now? */
          {
            Lines.removeAt(Temp);   /* Remove blank line. */
            Temp--;
          }
        }

        /* Remove duplicates if so desired. */
        if (m_MergeDuplicatesFlag!=0)
          Lines.removeDuplicates();

        m_pMessageLogTableModel->insertRows(
            m_pMessageLogTableModel->rowCount(QModelIndex()),Lines.count());
        for(int Temp=0;Temp<Lines.count();Temp++)
        {
          /* Split each line into fields. */
          Fields=Lines[Temp].split('\t');
          if (Fields.count()==4)  /* Ignore malformed lines. */
          {
            /* Remove full pathname, yielding only filename, if so desired.*/
            if (m_RemovePathsFlag!=0)
            {
              FileInfo.setFile(Fields[0]);
              Fields[0]=FileInfo.fileName();
            }

                /* Add the line to the model. */
            for(int Test=0;Test<Fields.count();Test++)
            {
              Index=m_pMessageLogTableModel->index(Temp,Test,QModelIndex());
              m_pMessageLogTableModel->setData(Index,QVariant(Fields[Test]));
            }
          }
        }
        m_pTableView->resizeColumnsToContents();
        m_pTableView->resizeRowsToContents();

        /* Get and save the "last modified" date/time. */
        FileInfo.setFile(File);
        m_LastModifiedDateTime=FileInfo.lastModified();

        /* Disable the "Refresh" button. */
        m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
      }
    }
  }

  return;
}

void MESSAGELOGVIEWERWIDGET_C::SetAutoRefreshFlag(bool AutoRefreshFlag)
{
  m_AutoRefreshFlag=AutoRefreshFlag;
  UpdateWidgets();
  m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(false);

  return;
}

void MESSAGELOGVIEWERWIDGET_C::SetMergeDuplicatesFlag(bool MergeDuplicatesFlag)
{
  m_MergeDuplicatesFlag=MergeDuplicatesFlag;
  UpdateWidgets();
  LoadMessageLog();
  m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(false);

  return;
}

void MESSAGELOGVIEWERWIDGET_C::SetRemovePathsFlag(bool RemovePathsFlag)
{
  m_RemovePathsFlag=RemovePathsFlag;
  UpdateWidgets();
  LoadMessageLog();
  m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(false);

  return;
}

void MESSAGELOGVIEWERWIDGET_C::SetMessageLogPathname(QString Pathname)
{
  if (Pathname.isEmpty()==0)
    m_Pathname=Pathname;

  return;
}

void MESSAGELOGVIEWERWIDGET_C::UpdateWidgets(void)
{
  m_pDisableAutoRefreshCheckBox->setEnabled(m_AutoRefreshFlag!=0);
  m_pButtonBox->button(QDialogButtonBox::Apply)->setEnabled(
      (m_AutoRefreshFlag==0) ||
      (m_pDisableAutoRefreshCheckBox->isChecked()!=0));

  return;
}

void MESSAGELOGVIEWERWIDGET_C::CheckFileDateTimeSlot(void)
{
  QFileInfo FileInfo;


  /* Make sure there is a pathname. */
  if (m_Pathname.isEmpty()==0)
  {
    /* Get info about the file. */
    FileInfo.setFile(m_Pathname);

    /* If the file has been modified since last read. */
    if (m_LastModifiedDateTime!=FileInfo.lastModified())
    {
      /* Enable/disable button and checkbox depending on settings. */
      UpdateWidgets();

      /* Reload message log only if autorefresh is active and
          "Disable autorefresh" is not checked. */
      if ( (m_AutoRefreshFlag!=0) &&
          (m_pDisableAutoRefreshCheckBox->isChecked()==0) )
        LoadMessageLog();
    }
  }

  return;
}

void MESSAGELOGVIEWERWIDGET_C::ButtonBoxButtonClickedSlot(
    QAbstractButton *pButton)
{
  switch(m_pButtonBox->standardButton(pButton))
  {
    case QDialogButtonBox::Apply:
      LoadMessageLog();
      break;
    default:
      break;
  }

  return;
}

MESSAGESTABLEMODEL_C::MESSAGESTABLEMODEL_C(QObject *pParent)
    : QAbstractTableModel(pParent)
{
  return;
}

MESSAGESTABLEMODEL_C::~MESSAGESTABLEMODEL_C(void)
{
  return;
}

int MESSAGESTABLEMODEL_C::columnCount(const QModelIndex &Parent) const
{
  Q_UNUSED(Parent)

  return(COUNT);
}

void MESSAGESTABLEMODEL_C::clear(void)
{
  removeRows(0,rowCount(QModelIndex()));
  m_Messages.clear();

  return;
}

QVariant MESSAGESTABLEMODEL_C::data(const QModelIndex &Index,int Role) const
{
  QVariant Return;


  Return=QVariant();
  if (Index.isValid()!=0)
  {
    if ( Index.row()<m_Messages.count() )
    {
      if (Role==Qt::DisplayRole)
      {
        switch (Index.column())
        {
          case FILENAME:
            Return=QVariant(m_Messages[Index.row()].Filename);
            break;
          case LINENUMBER:
            Return=QVariant(m_Messages[Index.row()].LineNumber);
            break;
          case TYPE:
            Return=QVariant(m_Messages[Index.row()].Type);
            break;
          case MESSAGE:
            Return=QVariant(m_Messages[Index.row()].Message);
            break;
          default:
            Return=QVariant();
            break;
        }
      }
    }
  }

  return(Return);
}

QVariant MESSAGESTABLEMODEL_C::headerData(
    int Section, Qt::Orientation Orientation, int Role) const
{
  QVariant Return;


  Return=QVariant();
  if (Role==Qt::DisplayRole)
  {
    if (Orientation==Qt::Horizontal)
    {
      switch (Section)
      {
        case FILENAME:
          Return="Filename";
          break;
        case LINENUMBER:
          Return="Line";
          break;
        case TYPE:
          Return="Type";
          break;
        case MESSAGE:
          Return="Message";
          break;
        default:
          Return="";
          break;
      }
    }
  }

  return(Return);
}

bool MESSAGESTABLEMODEL_C::insertRows(
    int Position,int Rows,const QModelIndex &Parent)
{
  Q_UNUSED(Parent);
  MESSAGE_T Temp;


  beginInsertRows(QModelIndex(),Position,Position+Rows-1);
  for (int Row=0;Row<Rows;Row++)
  {
    Temp.Filename="";
    Temp.LineNumber=0;
    Temp.Type="";
    Temp.Message="";
    m_Messages.insert(Position+Row,Temp);
  }
  endInsertRows();

  return(true);
}

bool MESSAGESTABLEMODEL_C::removeRows(
    int Position,int Rows,const QModelIndex &Parent)
{
  Q_UNUSED(Parent);
  int Row;


  beginRemoveRows(QModelIndex(),Position,Position+Rows-1);
  for (Row=0;Row<Rows;Row++)
    m_Messages.removeAt(Position);
  endRemoveRows();

  return(true);
 }

int MESSAGESTABLEMODEL_C::rowCount(const QModelIndex &Parent) const
{
  Q_UNUSED(Parent);

  return(m_Messages.count());
}

bool MESSAGESTABLEMODEL_C::setData(
    const QModelIndex &Index,const QVariant &Value,int Role)
{
  bool Return;
  QString Attribute;
  MESSAGE_T Temp;


  Return=false;
  if (Index.isValid()!=0)
  {
    if (Role==Qt::EditRole)
    {
      if (Index.column()==FILENAME)
      {
        m_Messages[Index.row()].Filename=Value.toString();
        emit(dataChanged(Index,Index));
        Return=true;
      }
      else if (Index.column()==LINENUMBER)
      {
        m_Messages[Index.row()].LineNumber=Value.toUInt();
        emit(dataChanged(Index,Index));
        Return=true;
      }
      else if (Index.column()==TYPE)
      {
        m_Messages[Index.row()].Type=Value.toString();
        emit(dataChanged(Index,Index));
        Return=true;
      }
      else if (Index.column()==MESSAGE)
      {
        m_Messages[Index.row()].Message=Value.toString();
        emit(dataChanged(Index,Index));
        Return=true;
      }

      switch(Index.column())
      {
        case FILENAME:
          break;
        case LINENUMBER:
          break;
        case TYPE:
          break;
        case MESSAGE:
          break;
        default:
          break;
      }
    }
  }

  return(Return);
}

Qt::ItemFlags MESSAGESTABLEMODEL_C::flags(const QModelIndex &Index) const
{
  Qt::ItemFlags Flags;


  Flags=Qt::ItemIsEnabled|Qt::ItemIsSelectable;

  return(Flags);
}


#undef    MESSAGELOGVIEWERWIDGET_CPP
