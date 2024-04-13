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
#include <sstream>
#include "HandShake.h"
#include "settings/Settings.h"

namespace shshare::net::messages
{

HandShake::HandShake()
{
    m_host = ::shshare::Settings::instance().getLocalHost();
}

HandShake::HandShake(QByteArray message)
{
    std::stringstream stream(message.data());
    m_host.setId(DeserializeString(stream));
    m_host.setName(DeserializeString(stream));
    m_host.setOSName(DeserializeString(stream));
    m_host.setAddress(DeserializeAddress(stream));
}

const Host& HandShake::GetHost() const
{
    return m_host;
}

const QByteArray HandShake::Serialize() const
{
    std::stringstream stream;

    SerializeString(stream, m_host.getId());
    SerializeString(stream, m_host.getName());
    SerializeString(stream, m_host.getOSName());
    SerializeAddress(stream, m_host.getAddress());

    return stream.str().c_str();
}

const PacketType HandShake::Type() const
{
    return PacketType::HandShake;
}

}
