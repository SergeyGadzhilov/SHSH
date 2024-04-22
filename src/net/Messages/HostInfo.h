/*
 * SHShare - LAN file transfer application.
 * Copyright (C) 2024 Hadzhilov Serhii
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef HOSTINFO_H
#define HOSTINFO_H

#include "NetworkMessage.h"
#include <core/Host.h>

namespace shshare::net::messages
{

class HostInfo : public NetworkMessage
{
public:
    HostInfo();
    explicit HostInfo(QByteArray data);
    const Host& GetHost() const;

    virtual const PacketType Type() const override;
    virtual const QByteArray Serialize() const override;

private:
    Host m_host;
};

}

#endif // HOSTINFO_H
