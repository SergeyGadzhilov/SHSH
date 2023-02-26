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
#include <quuid.h>
#include <qhostinfo.h>
#include <qnetworkinterface.h>

#include "LocalHost.h"
#include "settings/Settings.h"

LocalHost::LocalHost()
{
    setId(QUuid::createUuid().toString().toStdString());
    setName(QHostInfo::localHostName().toStdString());
    setAddress(QHostAddress::LocalHost);
    setOSName(::shshare::Settings::Os());

    foreach (QHostAddress address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol &&
                address != QHostAddress::LocalHost) {
            setAddress(address);
            break;
        }
    }
}

void LocalHost::reset()
{
    setName(QHostInfo::localHostName().toStdString());
}

const char *LocalHost::name() const
{
    return "LocalHost";
}

void LocalHost::load(const QSettings &storage)
{
    setName(storage.value(name(), QHostInfo::localHostName()).toString().toStdString());
}

void LocalHost::save(QSettings &storage) const
{
    storage.setValue(name(), getName().c_str());
}
