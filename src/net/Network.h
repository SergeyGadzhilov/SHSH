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
#ifndef SHASHARE_NET_NETWORK_H
#define SHASHARE_NET_NETWORK_H

#include <QTcpServer>
#include <QObject>

#include "net/Download.h"
#include "Broadcaster.h"

class Network : public QObject
{
    Q_OBJECT

public:
    explicit Network(QObject *parent = nullptr);
    bool listen(const QHostAddress& addr = QHostAddress::Any);
    void Connect(const QHostAddress& addr);
    void Broadcast();

signals:
    void NewHost(const Host& host);
    void StartDownload(Download* receiver);

private Q_SLOTS:
    void onNewConnection();

private:
    QTcpServer m_server;
    Broadcaster m_broadcaster;
};

#endif // SHASHARE_NET_NETWORK_H
