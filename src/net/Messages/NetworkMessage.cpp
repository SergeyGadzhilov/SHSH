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
#include "NetworkMessage.h"

namespace shshare::net::messages{

NetworkMessage::NetworkMessage()
{
}

void NetworkMessage::SerializeString(std::stringstream& stream, const std::string& data) const
{
    stream<<data.length()<<data;
}

void NetworkMessage::SerializeAddress(std::stringstream& stream, const QHostAddress& data) const
{
    stream<<data.toString().length()<<data.toString().toStdString();
}

const std::string NetworkMessage::DeserializeString(std::stringstream& stream) const
{
    size_t size = 0;
    stream>>size;

    auto payload = std::make_unique<char[]>(size);
    stream.getline(payload.get(), size);

    return payload.get();
}

const QHostAddress NetworkMessage::DeserializeAddress(std::stringstream& stream) const
{
    auto payload = DeserializeString(stream);
    return QHostAddress(payload.c_str());
}

}

