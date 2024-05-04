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
#include "Network.h"
#include "Messages/GetHostInfo.h"
#include "settings/Settings.h"
#include <iostream>

Network::Network(QObject *parent) :
    QObject(parent),
    m_broadcaster(this)
{
    connect(&m_server, &QTcpServer::newConnection, this, &Network::onNewConnection);
    connect(&m_broadcaster, &Broadcaster::received, this, [this](const Host host){
        emit NewHost(host);
    });
}

bool Network::listen(const QHostAddress &addr)
{
    return m_server.listen(addr, ::shshare::Settings::instance().getTransferPort());
}

void Network::Connect(const QHostAddress& addr)
{
    std::cout<<"Network::Connect: Connecting to "<<addr.toIPv4Address()<<std::endl;
    auto connection = new Connection();
    connect(connection, &Connection::Connected, this, [&connection](){
        connection->sendMessage(GetHostInfo{});
    });
    connection->Connect(addr, ::shshare::Settings::instance().getTransferPort());
}

void Network::Broadcast()
{
    m_broadcaster.start();
}

void Network::onNewConnection()
{
    auto socket = m_server.nextPendingConnection();
    if (socket) {
        auto connection = new Connection(socket, this);
        connect(connection, &Connection::HostInfo, this, [](Host host){
            std::cout<<"Received host = "<<host.getId()<<std::endl;
        });
        //emit StartDownload(new Download(socket));
    }
}
