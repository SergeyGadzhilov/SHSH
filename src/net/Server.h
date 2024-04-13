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
#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>

#include "net/Download.h"
#include "ui/models/HostList.h"

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(HostList* hosts, QObject *parent = nullptr);
    bool listen(const QHostAddress& addr = QHostAddress::Any);

Q_SIGNALS:
    void newReceiverAdded(Download* receiver);

private Q_SLOTS:
    void onNewConnection();

private:
    HostList* m_hosts{nullptr};
    QTcpServer m_server;
};

#endif // SERVER_H
