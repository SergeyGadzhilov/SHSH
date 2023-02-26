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
#include "TableModel.h"

namespace shshare::widgets::table {

TableModel::TableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

TableModel::~TableModel()
{
    for (const auto& connection : qAsConst(m_Connections)) {
        delete connection;
    }
}

int TableModel::rowCount(const QModelIndex&) const
{
    return m_Connections.size();
}

int TableModel::columnCount(const QModelIndex &) const
{
    return static_cast<int>(Column::Count);
}

QString TableModel::sizeToString(qint64 size) const
{
    int count = 0;
    double f_size = size;
    while (f_size >= 1024) {
        f_size /= 1024;
        count++;
    }

    QString suffix;
    switch (count) {
    case 0 : suffix = " B"; break;
    case 1 : suffix = " KB"; break;
    case 2 : suffix = " MB"; break;
    case 3 : suffix = " GB"; break;
    case 4 : suffix = " TB"; break;
    }

    return QString::number(f_size, 'f', 2).append(suffix);
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        auto info = getConnectionInfo(index.row());
        if (info) {
            Column col = static_cast<Column>(index.column());
            if (role == Qt::DisplayRole) {
                switch (col) {
                case Column::Peer : return info->getPeerName().c_str();
                case Column::FileName : return info->getFilePath();
                case Column::FileSize : return sizeToString(info->getDataSize());
                case Column::State : return getStateString(info->getState());
                case Column::Progress : return info->getProgress();
                default : break;
                }
            }
            else if (role == Qt::ForegroundRole) {
                return getStateColor(info->getState());
            }
        }
    }

    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (static_cast<Column>(section)) {
        case Column::Peer : return tr("Source");
        case Column::FileName : return tr("Name");
        case Column::FileSize : return tr("Size");
        case Column::Progress : return tr("Progress");
        case Column::State : return tr("");
        default : break; 
        }
    }

    return QVariant();
}

void TableModel::insert(Connection* connection)
{
    if (connection) {
        beginInsertRows(QModelIndex(), 0, 0);
        m_Connections.prepend(connection);
        endInsertRows();
        emit dataChanged(QAbstractTableModel::index(1, 0), index(m_Connections.size() - 1, Column::Count));

        auto info = connection->getConnectionInfo();
        connect(info, &ConnectionInfo::fileOpened, this, [=]() {
            int idx = m_Connections.indexOf(info->getOwner());
            auto fNameIdx = index(idx, Column::FileName);
            auto fSizeIdx = index(idx, Column::FileSize);
            emit dataChanged(fNameIdx, fSizeIdx);
        });

        connect(info, &ConnectionInfo::stateChanged, this, [=](ConnectionStateID state) {
            Q_UNUSED(state);
            int idx = m_Connections.indexOf(info->getOwner());
            auto stateIdx = index(idx, Column::State);
            emit dataChanged(stateIdx, stateIdx);
        });
    }
}

void TableModel::clearCompleted()
{
    for (int i = 0; i < m_Connections.size(); i++) {
        auto transfer = m_Connections.at(i);
        auto state = transfer->getConnectionInfo()->getState();
        if (state == ConnectionStateID::Idle ||
            state == ConnectionStateID::Finish ||
            state == ConnectionStateID::Disconnected ||
            state == ConnectionStateID::Cancelled) {
            remove(i);
            i--;
        }
    }
}

Connection* TableModel::getConnection(int index) const
{
    if (index < 0 || index >= m_Connections.size()) {
        return nullptr;
    }

    return m_Connections.at(index);
}

ConnectionInfo* TableModel::getConnectionInfo(int index) const
{
    auto transfer = getConnection(index);
    if (transfer) {
        return transfer->getConnectionInfo();
    }
    else {
        return nullptr;
    }
}

void TableModel::remove(int index)
{
    if (index < 0 || index >= m_Connections.size()) {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    m_Connections.at(index)->deleteLater();
    m_Connections.remove(index);
    endRemoveRows();
}

bool TableModel::isAllFinished() const
{
    for (int i = 0; i < rowCount(); ++i) {
        auto connection = getConnection(i);
        if (connection && !connection->isFinished()) {
            return false;
        }
    }

    return true;
}

QString TableModel::getStateString(ConnectionStateID state) const
{
    switch (state) {
    case ConnectionStateID::Idle : return tr("Idle");
    case ConnectionStateID::Waiting : return tr("Waiting");
    case ConnectionStateID::Disconnected : return tr("Disconnected");
    case ConnectionStateID::Paused : return tr("Paused");
    case ConnectionStateID::Cancelled : return tr("Cancelled");
    case ConnectionStateID::Transfering : return tr("Transfering");
    case ConnectionStateID::Finish : return tr("Finished");
    }

    return QString();
}

QColor TableModel::getStateColor(ConnectionStateID state) const
{
    switch (state) {
    case ConnectionStateID::Idle : return QColor("black");
    case ConnectionStateID::Waiting : return QColor("orange");
    case ConnectionStateID::Disconnected : return QColor("red");
    case ConnectionStateID::Paused : return QColor("orange");
    case ConnectionStateID::Cancelled : return QColor("red");
    case ConnectionStateID::Transfering : return QColor("blue");
    case ConnectionStateID::Finish : return QColor("#22C55E");
    }

    return QColor();
}

QModelIndex TableModel::index(int row, Column col) const
{
    return QAbstractTableModel::index(row, static_cast<int>(col));
}

}// namespace shshare::widgets::connections
