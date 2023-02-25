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
#ifndef RECEIVER_H
#define RECEIVER_H

#include "core/Host.h"
#include "net/Connection.h"

class Download : public Connection
{
public:
    Download(const Host& sender, QTcpSocket* socket, QObject* parent = nullptr);

private Q_SLOTS:
    void onDisconnected();

private:
    void processHeaderPacket(QByteArray& data) override;
    void processDataPacket(QByteArray& data) override;
    void processFinishPacket() override;
    void processCancelPacket() override;

    void createFile(const QString& folderName, const QString& fileName);
    QString getUniqueFileName(const QString& fileName, const QString& folderPath);
    QString getDestinationPath(const QString& folderName, const QString& fileName);

    qint64 m_fileSize{0};
    qint64 m_bytesRead{0};
};

#endif // RECEIVER_H
