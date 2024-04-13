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
#ifndef NETWORKMESSAGE_H
#define NETWORKMESSAGE_H

#include <sstream>
#include <QHostAddress>
#include "INetworkMessage.h"

namespace shshare::net::messages{

class NetworkMessage : public INetworkMessage
{
public:
    NetworkMessage();

    void SerializeString(std::stringstream& stream, const std::string& data) const;
    void SerializeAddress(std::stringstream& stream, const QHostAddress& data) const;

    const std::string DeserializeString(std::stringstream& stream) const;
    const QHostAddress DeserializeAddress(std::stringstream& stream) const;
};

}



#endif // NETWORKMESSAGE_H
