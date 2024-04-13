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
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>

#include "Upload.h"
#include "net/Messages/HandShake.h"
#include "settings/Settings.h"

Upload::Upload(const Host& receiver, const QString& folder, const QString& file, QObject* parent) :
    Connection(nullptr, parent),
    m_receiver(receiver),
    m_file(file),
    m_folder(folder)
{
    m_size = -1;
    m_bytesRemaining = -1;

    m_buffSize = ::shshare::Settings::instance().getFileBufferSize();
    m_buffer.resize(m_buffSize);

    m_cancelled = false;
    m_paused = false;
    m_pausedByReceiver = false;
    m_isHeaderSent = false;
    mInfo->setPeer(receiver);
}

bool Upload::start()
{
    mInfo->setFilePath(m_file);

    auto isOpened = openFile();
    if (isOpened && m_size > 0) {
        connectToReceiver();
    }

    return isOpened && mSocket;
}

void Upload::resume()
{
    if (mInfo->resume()) {
        m_paused = false;
        sendData();
    }
}

void Upload::pause()
{
    if (mInfo->pause()) {
        m_paused = true;
    }
}

void Upload::cancel()
{
    if (mInfo->cancel()) {
        writePacket(0, PacketType::Cancel, QByteArray());
        m_cancelled = true;
    }
}

void Upload::onConnected()
{
    mInfo->transfer();
    sendHandShake();
    sendHeader();
}

void Upload::onDisconnected()
{
    mInfo->disconnect(tr("Receiver disconnected"));
}

void Upload::connectToReceiver()
{
    setSocket(new QTcpSocket(this));
    mSocket->connectToHost(m_receiver.getAddress(),
                           ::shshare::Settings::instance().getTransferPort(),
                           QAbstractSocket::ReadWrite);
    mInfo->waiting();
    connect(mSocket, &QTcpSocket::bytesWritten, this, &Upload::onBytesWritten);
    connect(mSocket, &QTcpSocket::connected, this, &Upload::onConnected);
    connect(mSocket, &QTcpSocket::disconnected, this, &Upload::onDisconnected);
}

bool Upload::openFile()
{
    mInfo->setFilePath(m_file);

    mFile = new QFile(m_file, this);
    bool isOpened = mFile->open(QIODevice::ReadOnly);
    if (isOpened) {
        m_size = mFile->size();
        mInfo->setDataSize(m_size);
        m_bytesRemaining = m_size;
    }

    return isOpened;
}

void Upload::onBytesWritten(qint64)
{
    if (!mSocket->bytesToWrite()) {
        sendData();
    }
}

void Upload::finish()
{
    mFile->close();
    mInfo->finish();
    writePacket(0, PacketType::Finish, QByteArray());
}

void Upload::sendData()
{
    if (!m_bytesRemaining || m_cancelled || m_pausedByReceiver || m_paused)
        return;

    if (m_bytesRemaining < m_buffSize) {
        m_buffer.resize(m_bytesRemaining);
        m_buffSize = m_buffer.size();
    }

    qint64 bytesRead = mFile->read(m_buffer.data(), m_buffSize);
    if (bytesRead == -1) {
        mInfo->error(tr("Error while reading file."));
        return;
    }

    m_bytesRemaining -= bytesRead;
    if (m_bytesRemaining < 0) {
        m_bytesRemaining = 0;
    }

    mInfo->setProgress(static_cast<int>((m_size - m_bytesRemaining) * 100 / m_size));

    writePacket(m_buffSize, PacketType::Data, m_buffer);

    if (!m_bytesRemaining) {
        finish();
    }
}

void Upload::sendHandShake()
{
    HandShake message;
    sendMessage(message);
}

void Upload::sendHeader()
{
    QString fName = QDir(mFile->fileName()).dirName();

    QJsonObject obj( QJsonObject::fromVariantMap({
                                    {"name", fName},
                                    {"folder", m_folder },
                                    {"size", m_size}
                                }));

    QByteArray headerData( QJsonDocument(obj).toJson() );

    writePacket(headerData.size(), PacketType::Header, headerData);
    m_isHeaderSent = true;
}

void Upload::processCancelPacket()
{
    mInfo->cancel();
    mSocket->disconnectFromHost();
    m_cancelled = true;
}

void Upload::processPausePacket()
{
    m_pausedByReceiver = true;
}

void Upload::processResumePacket()
{
    m_pausedByReceiver = false;
    if (m_isHeaderSent) {
        sendData();
    }
    else {
        sendHeader();
    }
}

