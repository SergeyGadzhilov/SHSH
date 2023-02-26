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
#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include "core/Host.h"
#include "settings/General/General.h"
#include "settings/Network/Network.h"
#include "SettingsStorage.h"

namespace shshare {

class Settings
{
public:
    static Settings& instance();
    Settings(const Settings&) = delete;
    Settings(const Settings&&) = delete;
    void operator=(const Settings&) = delete;

    NetworkSettings& network();
    quint16 getBroadcastPort();
    quint16 getTransferPort();
    quint16 getBroadcastInterval();
    quint32 getFileBufferSize();
    QString getDownloadDir() const;

    const Host& getLocalHost() const;
    bool getReplaceExistingFile() const;

    void setHostName(const QString& name);
    void setBroadcastPort(quint16 port);
    void setTransferPort(quint16 port);
    void setBroadcastInterval(quint16 interval);
    void setFileBufferSize(qint32 size);
    void setDownloadDir(const QString& dir);
    void setReplaceExistingFile(bool replace);

    void saveSettings();
    void reset();

    static const char *Os();
    static const char* AppName();
    static const char* AppVersion();

private:
    Settings();
    ~Settings();

    SettingsStorage m_storage;
    General m_general;
    NetworkSettings m_network;
};

}


#endif // SETTINGS_H
