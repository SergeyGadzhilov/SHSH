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
#ifndef SENDER_H
#define SENDER_H

#include "core/Host.h"
#include "net/Connection.h"

class Upload : public Connection
{
public:
    Upload(const Host& receiver, const QString& folder, const QString& file, QObject* parent = nullptr);

    bool start();

    void resume() override;
    void pause() override;
    void cancel() override;

private Q_SLOTS:
    void onBytesWritten(qint64 bytes);
    void onConnected();
    void onDisconnected();

private:
    void connectToReceiver();
    bool openFile();
    void finish();
    void sendData();
    void sendHeader();

    void processCancelPacket() override;
    void processPausePacket() override;
    void processResumePacket() override;

    Host m_receiver;
    QString m_file;
    QString m_folder;
    qint64 m_size;
    qint64 m_bytesRemaining;

    QByteArray m_buffer;
    qint32 m_buffSize;

    bool m_cancelled;
    bool m_paused;
    bool m_pausedByReceiver;
    bool m_isHeaderSent;
};

#endif // SENDER_H
