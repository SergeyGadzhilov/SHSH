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
#include <QPixmap>
#include "HostList.h"
#include "settings/Settings.h"

HostList::HostList(QObject* parent):
    QAbstractListModel(parent)
{
}

void HostList::AddHost(const Host& host)
{
    if (!isLocalHost(host)) {
        if (!GetHost(host.getId()).isValid()) {
            const auto size = static_cast<int>(m_Hosts.size());
            beginInsertRows(QModelIndex(), size, size);
            m_Hosts.push_back(host);
            endInsertRows();
        }
    }
}

bool HostList::isLocalHost(const Host &host) const
{
    const auto& localHost = ::shshare::Settings::instance().getLocalHost();
    return (host.getId() == localHost.getId());
}

QString HostList::displayName(const Host &host) const
{
    return (host.getName() + "  (" + host.getOSName() + ")").c_str();
}

QString HostList::toolTip(const Host &host) const
{
    return (host.getId() + "<br>" +
            host.getName() + " (" + host.getOSName() + ")<br>" +
            host.getAddress().toString().toStdString()).c_str();
}

QPixmap HostList::osImage(const Host &host) const
{
    const auto& os = host.getOSName();

    if (os == "Linux") {
        return QPixmap(":/img/linux.png");
    } else if (os == "Windows") {
        return QPixmap(":/img/windows.png");
    } else if (os == "Mac OSX") {
        return QPixmap(":/img/mac.png");
    }

    return QPixmap();
}

const std::vector<Host>& HostList::getHosts() const
{
    return m_Hosts;
}

void HostList::setHosts(const std::vector<Host> &hosts)
{
    beginResetModel();
    m_Hosts = hosts;
    endResetModel();
}

QVariant HostList::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        switch (role) {
            case Qt::DisplayRole:
                return displayName(m_Hosts[index.row()]);
            case Qt::ToolTipRole:
                return toolTip(m_Hosts[index.row()]);
            case Qt::DecorationRole :
                return osImage(m_Hosts[index.row()]);
        }
    }

    return QVariant();
}

int HostList::rowCount(const QModelIndex&) const
{
    return static_cast<int>(m_Hosts.size());
}

void HostList::refresh()
{
    beginResetModel();
    m_Hosts.clear();
    endResetModel();
}

Host HostList::GetHost(int index) const
{
    if (index < 0 || index >= m_Hosts.size()) {
        return Host();
    }

    return m_Hosts.at(index);
}

Host HostList::GetHost(const std::string& id) const
{
    for (auto& host : m_Hosts) {
        if (host.getId() == id) {
            return host;
        }
    }

    return Host();
}

Host HostList::GetHost(const QHostAddress &address) const
{
    for (auto& host : m_Hosts) {
        if (host.getAddress() == address) {
            return host;
        }
    }

    return Host();
}
