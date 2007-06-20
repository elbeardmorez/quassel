/***************************************************************************
 *   Copyright (C) 2005-07 by The Quassel Team                             *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "bufferview.h"

/*****************************************
* The TreeView showing the Buffers
*****************************************/
// Please be carefull when reimplementing methods which are used to inform the view about changes to the data
// to be on the safe side: call QTreeView's method aswell
BufferView::BufferView(QWidget *parent) : QTreeView(parent) {
}

void BufferView::init() {
  setIndentation(10);
  header()->hide();
  header()->hideSection(1);
  expandAll();
  
  setDragEnabled(true);
  setAcceptDrops(true);
  setDropIndicatorShown(true);
  
  connect(selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), model(), SLOT(changeCurrent(const QModelIndex &, const QModelIndex &)));
  connect(this, SIGNAL(doubleClicked(const QModelIndex &)), model(), SLOT(doubleClickReceived(const QModelIndex &)));
  connect(model(), SIGNAL(updateSelection(const QModelIndex &, QItemSelectionModel::SelectionFlags)), selectionModel(), SLOT(select(const QModelIndex &, QItemSelectionModel::SelectionFlags)));

}

void BufferView::setFilteredModel(QAbstractItemModel *model, BufferViewFilter::Modes mode, QStringList nets) {
  BufferViewFilter *filter = new BufferViewFilter(model, mode, nets);
  setModel(filter);
}

void BufferView::setModel(QAbstractItemModel *model) {
  QTreeView::setModel(model);
  init();
}

void BufferView::dragEnterEvent(QDragEnterEvent *event) {
  // not yet needed... this will be usefull to keep track of the active view when customizing them with drag and drop
  QTreeView::dragEnterEvent(event);
}

void BufferView::rowsInserted(const QModelIndex & parent, int start, int end) {
  if(parent.parent() == QModelIndex()) setExpanded(parent, true);
  QTreeView::rowsInserted(parent, start, end);
}
