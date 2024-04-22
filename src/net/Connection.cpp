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
#include "Connection.h"
#include <net/Messages/GetHostInfo.h>
#include <net/Messages/HostInfo.h>

Connection::Connection(QTcpSocket* socket, QObject* parent) :
    QObject(parent)
{
    mInfo = new ConnectionInfo(this, this);
    setSocket(socket);
}

void Connection::resume()
{

}

void Connection::pause()
{

}

void Connection::cancel()
{

}

void Connection::sendMessage(const INetworkMessage& message)
{
    auto data = message.Serialize();
    writePacket(data.size(), message.Type(), data);
}

void Connection::GetHostInfo()
{
    shshare::net::messages::GetHostInfo message;
    sendMessage(message);
}

bool Connection::isFinished() const
{
    auto state = mInfo->getState();
    return state != ConnectionStateID::Paused &&
           state != ConnectionStateID::Transfering &&
           state != ConnectionStateID::Waiting;
}

void Connection::onMessageReceived()
{
    if (mInfo->getState() == ConnectionStateID::Cancelled)
        return;

    m_buff.append(mSocket->readAll());

    while (m_buff.size() >= m_headerSize) {
        if (m_packetSize < 0) {
            m_packetSize = readSize(m_buff);
        }

        if (m_buff.size() > m_packetSize) {
            PacketType type = static_cast<PacketType>(m_buff.at(0));
            QByteArray data = m_buff.mid(1, m_packetSize);

            processPacket(data, type);
            m_buff.remove(0, m_packetSize + 1);

            m_packetSize = -1;
        }
        else {
            break;
        }
    }
}

qint32 Connection::readSize(QByteArray &message)
{
    qint32 size = 0;

    memcpy(&size, message.constData(), sizeof(size));
    message.remove(0, sizeof(size));

    return size;
}

void Connection::writePacket(qint32 packetDataSize, PacketType type, const QByteArray &data)
{
    if (mSocket) {
        mSocket->write(reinterpret_cast<const char*>(&packetDataSize), sizeof(packetDataSize));
        mSocket->write(reinterpret_cast<const char*>(&type), sizeof(type));
        mSocket->write(data);
    }
}

void Connection::processPacket(QByteArray &data, PacketType type)
{
    switch (type) {
    case PacketType::Header : processHeaderPacket(data); break;
    case PacketType::Data : processDataPacket(data); break;
    case PacketType::Finish : processFinishPacket(); break;
    case PacketType::Cancel : processCancelPacket(); break;
    case PacketType::Pause : processPausePacket(); break;
    case PacketType::Resume : processResumePacket(); break;
    case PacketType::HostInfo: processHostInfo(data); break;
    case PacketType::GetHostInfo: processGetHostInfo(); break;
    }
}

void Connection::processHeaderPacket(QByteArray& data)
{
    Q_UNUSED(data);
}

void Connection::processDataPacket(QByteArray& data)
{
    Q_UNUSED(data);
}

void Connection::processFinishPacket()
{
}

void Connection::processCancelPacket()
{
}

void Connection::processPausePacket()
{
}

void Connection::processResumePacket()
{
}

void Connection::processGetHostInfo()
{
    sendMessage(shshare::net::messages::HostInfo{});
}

void Connection::processHostInfo(QByteArray& data)
{
    shshare::net::messages::HostInfo message(data);
    emit HostInfo(message.GetHost());
}

void Connection::clearReadBuffer()
{
    m_buff.clear();
    m_packetSize = -1;
}

void Connection::setSocket(QTcpSocket *socket)
{
    if (socket) {
        mSocket = socket;
        connect(mSocket, &QTcpSocket::readyRead, this, &Connection::onMessageReceived);
    }
}

