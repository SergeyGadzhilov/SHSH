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
#ifndef CONNECTION_H
#define CONNECTION_H

#include <QFile>
#include <QTcpSocket>
#include <QObject>

#include "core/Host.h"
#include "core/TransferInfo.h"

enum class PacketType : char
{
    Header = 0x01,
    Data,
    Finish,
    Cancel,
    Pause,
    Resume
};

class ConnectionInfo;

class Connection : public QObject
{
    Q_OBJECT

public:
    Connection(QTcpSocket* socket, QObject* parent = nullptr);

    inline ConnectionInfo* getConnectionInfo() const { return mInfo; }

    virtual void resume();
    virtual void pause();
    virtual void cancel();
    bool isFinished() const;

protected:
    void clearReadBuffer();
    void setSocket(QTcpSocket* socket);

    virtual void processPacket(QByteArray& data, PacketType type);
    virtual void processHeaderPacket(QByteArray& data);
    virtual void processDataPacket(QByteArray& data);
    virtual void processFinishPacket();
    virtual void processCancelPacket();
    virtual void processPausePacket();
    virtual void processResumePacket();

    virtual void writePacket(qint32 size, PacketType type, const QByteArray& data);

    QFile* mFile{nullptr};
    QTcpSocket* mSocket{nullptr};
    ConnectionInfo* mInfo{nullptr};

private Q_SLOTS:
    void onMessageReceived();

private:
    qint32 readSize(QByteArray& message);


    QByteArray m_buff;
    qint32 m_packetSize{-1};

    int m_headerSize{sizeof(PacketType) + sizeof(m_packetSize)};
};

#endif // CONNECTION_H
