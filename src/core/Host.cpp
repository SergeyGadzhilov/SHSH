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
#include "Host.h"

Host::Host(const std::string& id,
           const std::string& name,
           const std::string& osName,
           const QHostAddress& address):
    m_Id{id},
    m_Name{name},
    m_OSName{osName},
    m_Address{address}
{
}

bool Host::isValid() const
{
    return (!m_Id.empty() &&
            !m_Name.empty() &&
            !m_OSName.empty() &&
            !m_Address.isNull());
}

const std::string& Host::getId() const
{
    return m_Id;
}

const std::string& Host::getName() const
{
    return m_Name;
}

const std::string& Host::getOSName() const
{
    return m_OSName;
}

const QHostAddress& Host::getAddress() const
{
    return m_Address;
}

void Host::setId(const std::string& id)
{
    m_Id = id;
}

void Host::setName(const std::string& name)
{
    m_Name = name;
}

void Host::setOSName(const std::string& osName)
{
    m_OSName = osName;
}

void Host::setAddress(const QHostAddress& address)
{
    m_Address = address;
}

bool Host::operator==(const Host& other) const
{
    return (m_Id == other.getId() &&
            m_Name == other.getName() &&
            m_Address == other.getAddress());
}

bool Host::operator!=(const Host& other) const
{
    return !((*this) == other);
}
