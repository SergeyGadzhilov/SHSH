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
#include "Settings.h"
#include <config.h>

namespace shshare {

Settings::Settings()
{
    m_storage.add(&m_general);
    m_storage.add(&m_network);

    m_storage.load();
}

Settings::~Settings()
{
    saveSettings();
}

NetworkSettings& Settings::network()
{
    return m_network;
}

const char* Settings::AppVersion()
{
    return SHSHARE_VERSION;
}

const char* Settings::AppName()
{
    return "SHShare";
}

void Settings::setHostName(const QString &name)
{
    auto& localHost = m_general.profile().localHost();
    localHost.setName(name.toStdString());
}

void Settings::setBroadcastPort(quint16 port)
{
    m_network.broadcast().port(port);
}

void Settings::setBroadcastInterval(quint16 interval)
{
    m_network.broadcast().interval(interval);
}

void Settings::setTransferPort(quint16 port)
{
    m_network.transfer().port(port);
}

void Settings::setFileBufferSize(qint32 size)
{
    m_network.transfer().bufferSize(size);
}

void Settings::setDownloadDir(const QString& dir)
{
    m_general.storage().downloadDir(dir);
}

void Settings::setReplaceExistingFile(bool replace)
{
    m_general.storage().replaceExisting(replace);
}

void Settings::saveSettings()
{
    m_storage.save();
}

void Settings::reset()
{
    m_storage.reset();
}

const char* Settings::Os()
{
#if defined (Q_OS_WIN)
    return "Windows";
#elif defined (Q_OS_OSX)
    return "Mac OSX";
#elif defined (Q_OS_LINUX)
    return "Linux";
#else
    return "Unknown";
#endif

}

Settings& Settings::instance()
{
    static Settings instance;
    return instance;
}

quint16 Settings::getBroadcastPort()
{
    return m_network.broadcast().port();
}

quint16 Settings::getTransferPort()
{
    return m_network.transfer().port();
}

quint16 Settings::getBroadcastInterval()
{
    return m_network.broadcast().interval();
}

quint32 Settings::getFileBufferSize()
{
    return m_network.transfer().bufferSize();
}

QString Settings::getDownloadDir() const
{
    return m_general.storage().downloadDir();
}

const Host& Settings::getLocalHost() const
{
    return m_general.profile().localHost();
}

bool Settings::getReplaceExistingFile() const
{
    return m_general.storage().replaceExisting();
}

} //namespace shshare
