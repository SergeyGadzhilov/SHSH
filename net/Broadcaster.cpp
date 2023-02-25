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
#include "Broadcaster.h"

Broadcaster::Broadcaster(QObject *parent) :
    QObject(parent),
    m_localHost(::shshare::Settings::instance().getLocalHost()),
    m_settings(::shshare::Settings::instance().network().broadcast())
{
    connect(&m_Timer, &QTimer::timeout, this, &Broadcaster::send);
    connect(&m_Socket, &QUdpSocket::readyRead, this, &Broadcaster::receive);

    m_Socket.bind(m_settings.port(), QUdpSocket::ShareAddress);
}

void Broadcaster::start()
{
    send();
    if (!m_Timer.isActive()) {
        m_Timer.start(m_settings.interval());
    }
}

void Broadcaster::send()
{
    const auto message = buildMessage();
    QVector<QHostAddress> addresses = getAddress();
    foreach (QHostAddress address, addresses) {
        m_Socket.writeDatagram(message, address, m_settings.port());
    }
}

void Broadcaster::receive()
{
    while (m_Socket.hasPendingDatagrams()) {
        QHostAddress sender;
        QByteArray data(static_cast<int>(m_Socket.pendingDatagramSize()), 0);
        m_Socket.readDatagram(data.data(), data.size(), &sender);

        auto json = QJsonDocument::fromJson(data).object();
        if (json.keys().length() == 4 &&
            json.value("port").toVariant().value<quint16>() == m_settings.port())
        {
            emit received({
                json.value("id").toString().toStdString(),
                json.value("name").toString().toStdString(),
                json.value("os").toString().toStdString(),
                sender
            });
        }
    }
}

QByteArray Broadcaster::buildMessage() const
{
    auto port = static_cast<quint16>(m_settings.port());

    QJsonObject message(QJsonObject::fromVariantMap({
        {"id",   m_localHost.getId().c_str()},
        {"name", m_localHost.getName().c_str()},
        {"os",   m_localHost.getOSName().c_str()},
        {"port", port}
    }));

    return QJsonDocument(message).toJson(QJsonDocument::Compact);
}

QVector<QHostAddress> Broadcaster::getAddress()
{
    QVector<QHostAddress> addresses;
    foreach (QNetworkInterface iface, QNetworkInterface::allInterfaces()) {
        if (iface.flags() & QNetworkInterface::CanBroadcast) {
            foreach (QNetworkAddressEntry addressEntry, iface.addressEntries()) {
                if (!addressEntry.broadcast().isNull()) {
                    addresses.push_back(addressEntry.broadcast());
                }
            }
        }
    }
    return addresses;
}
