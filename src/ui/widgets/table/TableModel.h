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
#ifndef WIDGETS_CONNECTIONS_TABLEMODEL_H
#define WIDGETS_CONNECTIONS_TABLEMODEL_H

#include <QMap>
#include <QColor>
#include <QAbstractTableModel>

#include "net/Connection.h"
#include "core/TransferInfo.h"

namespace shshare::widgets::table {

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent = nullptr);
    ~TableModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void insert(Connection* connection);
    void clearCompleted();
    QString sizeToString(qint64 size) const;

    Connection* getConnection(int index) const;
    ConnectionInfo* getConnectionInfo(int index) const;

    void remove(int index);
    bool isAllFinished()const;

    enum class Column : int {
        Peer = 0, Name, Size, Progress, State,
        Count
    };
    QModelIndex index(int row, Column col) const;
    void setColumnName(const Column& column, const QString& name);

private:
    QString getStateString(ConnectionStateID state) const;
    QColor getStateColor(ConnectionStateID state) const;

    QVector<Connection*> m_Connections;
    QMap<Column, QString> m_columns {
        {Column::Peer, tr("Source")},
        {Column::Name, tr("Name")},
        {Column::Size, tr("Size")},
        {Column::Progress, tr("Progress")},
        {Column::State, tr("Status")}
    };

};

} //namespace shshare::widgets::connections

#endif // WIDGETS_CONNECTIONS_TABLEMODEL_H
