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
#ifndef DEVICELISTMODEL_H
#define DEVICELISTMODEL_H

#include <vector>
#include <string>
#include <QAbstractListModel>

#include "core/Host.h"
#include "net/Broadcaster.h"

class HostList : public QAbstractListModel
{
public:
    HostList(Broadcaster& broadcast, QObject* parent = nullptr);

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    void refresh();

    Host host(int index) const;
    Host host(const std::string& id) const;
    Host host(const QHostAddress& address) const;

    const std::vector<Host>& getHosts() const;
    void setHosts(const std::vector<Host>& hosts);

private Q_SLOTS:
    void onBroadcastReceived(const Host &fromDevice);

private:
    bool isLocalHost(const Host& host) const;
    QString displayName(const Host& host) const;
    QString toolTip(const Host& host) const;
    QPixmap osImage(const Host& host) const;

    Broadcaster& m_Broadcast;
    std::vector<Host> m_Hosts;
};

#endif // DEVICELISTMODEL_H
