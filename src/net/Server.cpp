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
#include "Server.h"
#include "settings/Settings.h"

Server::Server(HostList* hosts, QObject *parent) :
    QObject(parent)
{
    m_hosts = hosts;
    connect(&m_server, &QTcpServer::newConnection, this, &Server::onNewConnection);
}

bool Server::listen(const QHostAddress &addr)
{
    return m_server.listen(addr, ::shshare::Settings::instance().getTransferPort());
}

void Server::onNewConnection()
{
    auto socket = m_server.nextPendingConnection();
    if (socket) {
        const auto host = m_hosts->host(socket->peerAddress());
        emit newReceiverAdded(new Download(host, socket));
    }
}
