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
#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <QObject>
#include <QTimer>
#include <QtNetwork>

#include "core/Host.h"
#include "settings/Settings.h"

class Broadcaster : public QObject
{
    Q_OBJECT

public:
    explicit Broadcaster(QObject *parent = nullptr);

Q_SIGNALS:
    void received(const Host& host);

public Q_SLOTS:
    void start();
    void send();

private Q_SLOTS:
    void receive();

private:
    QByteArray buildMessage() const;
    QVector<QHostAddress> getAddress();

    QTimer m_Timer;
    QUdpSocket m_Socket;
    const Host& m_localHost;
    BroadcastSettings& m_settings;
};

#endif // BROADCASTER_H
