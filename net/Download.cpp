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
#include <QJsonObject>
#include <QJsonDocument>

#include "Download.h"
#include "settings/Settings.h"

Download::Download(const Host& sender, QTcpSocket* socket, QObject* parent)
    : Connection(socket, parent)
{
    connect(mSocket, &QTcpSocket::disconnected, this, &Download::onDisconnected);
    mInfo->waiting();
    mInfo->setPeer(sender);
}

void Download::onDisconnected()
{
    mInfo->disconnect("Sender disconnected");
}

QString Download::getUniqueFileName(const QString& fileName, const QString& folderPath)
{
    int count = 1;
    QString originalFilePath = folderPath + QDir::separator() + fileName;
    QString fPath = originalFilePath;
    while (QFile::exists(fPath)) {
        QFileInfo fInfo(originalFilePath);
        QString baseName = fInfo.baseName() + " (" + QString::number(count) + ")";
        fPath = folderPath + QDir::separator() + baseName + "." + fInfo.completeSuffix();
        count++;
    }

    return fPath;
}

QString Download::getDestinationPath(const QString& folder, const QString& file)
{
    QString dstFolder = ::shshare::Settings::instance().getDownloadDir();
    if (!folder.isEmpty()) {
        dstFolder = dstFolder + QDir::separator() + folder;
    }

    QDir dir(dstFolder);
    if (!dir.exists()) {
        dir.mkpath(dstFolder);
    }

    QString dstFile = dstFolder + QDir::separator() + file;
    if (!::shshare::Settings::instance().getReplaceExistingFile()) {
        dstFile = getUniqueFileName(file, dstFolder);
    }

    mInfo->setFilePath(dstFile);
    return dstFile;
}

void Download::processHeaderPacket(QByteArray& data)
{
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    QString file = obj.value("name").toString();
    QString folder = obj.value("folder").toString();
    m_fileSize = obj.value("size").toVariant().value<qint64>();
    mInfo->setDataSize(m_fileSize);

    createFile(folder, file);
}

void Download::processDataPacket(QByteArray& data)
{
    if (mFile && m_bytesRead + data.size() <= m_fileSize) {
        mFile->write(data);
        m_bytesRead += data.size();

        mInfo->setProgress( (int)(m_bytesRead * 100 / m_fileSize) );
    }
}

void Download::processFinishPacket()
{
    mFile->close();
    mSocket->disconnectFromHost();
    mInfo->finish();
}

void Download::processCancelPacket()
{
    clearReadBuffer();
    mFile->remove();
    mSocket->disconnectFromHost();
    mInfo->cancel();
}

void Download::createFile(const QString& folder, const QString& file)
{
    const auto& path = getDestinationPath(folder, file);
    mFile = new QFile(path, this);

    if (mFile->open(QIODevice::WriteOnly)) {
        mInfo->transfer();
    }
    else {
        mInfo->error(mFile->errorString());
    }
}
