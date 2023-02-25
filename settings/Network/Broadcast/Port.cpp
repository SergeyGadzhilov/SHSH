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
#include "Port.h"

Port::Port(Group* group)
{
    if (group) {
        group->add(this);
    }
}

Port::operator quint16() const
{
    return m_Port;
}

void Port::operator =(quint16 value)
{
    m_Port = value;
}

const char* Port::name() const
{
    return "BroadcastPort";
}

void Port::load(const QSettings &storage)
{
    m_Port = storage.value(name(), DefaultPort).value<quint16>();
}

void Port::save(QSettings &storage) const
{
    storage.setValue(name(), m_Port);
}

void Port::reset()
{
    m_Port = DefaultPort;
}
