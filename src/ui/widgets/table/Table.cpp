/*
    SHShare - LAN file transfer application.
    Copyright (C) 2023 Serhii Hadzhylov <gadzhilov.sergey@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <QHeaderView>
#include <QProgressBar>
#include "Table.h"

namespace shshare::widgets::table {

Table::Table(QWidget *parent) :
    QTableView(parent),
    m_model(new TableModel(this))
{
    setWordWrap(false);
    setFocusPolicy(Qt::NoFocus);
    verticalHeader()->setVisible(false);
    horizontalHeader()->setStretchLastSection(true);
    horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    setModel(m_model);
    connect(selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &Table::onSelectionChanged);
}

bool Table::isAllFinished() const
{
    return m_model->isAllFinished();
}

bool Table::isSelectedFinished() const
{
    const auto info = m_model->getConnectionInfo(currentIndex().row());
    return (info && info->isFinished());
}

void Table::insert(Connection *connection)
{
    m_model->insert(connection);
}

void Table::removeSelected()
{
    m_model->remove(currentIndex().row());
}

void Table::removeCompleted()
{
    m_model->clearCompleted();
}

void Table::cancelSelected()
{
    auto connection = m_model->getConnection(currentIndex().row());
    if (connection) {
        connection->cancel();
    }
}

void Table::pauseSelected()
{
    auto connection =  m_model->getConnection(currentIndex().row());
    if (connection) {
        connection->pause();
    }
}

void Table::resumeSelected()
{
    auto connection = m_model->getConnection(currentIndex().row());
    if (connection) {
        connection->resume();
    }
}

QString Table::getSelectedFile()
{
    const auto index = m_model->index(currentIndex().row(), TableModel::Column::Name);
    return m_model->data(index).toString();
}

ConnectionInfo *Table::getConnectionByPosition(const QPoint &pos)
{
    return m_model->getConnectionInfo(indexAt(pos).row());
}

void Table::setColumnName(int column, const QString &name)
{
    m_model->setColumnName(static_cast<TableModel::Column>(column), name);
}

void Table::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    auto connection = getConnection(selected);
    if (connection) {
        emit onSelected(connection);
    }

    connection = getConnection(deselected);
    if (connection) {
        emit onDeselected(connection);
    }
}

ConnectionInfo *Table::getConnection(const QItemSelection &selection) const
{
    ConnectionInfo* connection{nullptr};

    if (selection.size() > 0) {
        auto index = selection.indexes().first();
        connection = m_model->getConnectionInfo(index.row());
    }

    return connection;
}

} //namespace shshare::widgets::connections
