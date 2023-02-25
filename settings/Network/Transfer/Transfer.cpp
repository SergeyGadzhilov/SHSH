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
#include "Transfer.h"

TransferGroup::TransferGroup(Group *parent) :
    Group(parent)
{
    add(&m_port);
    add(&m_bufferSize);
}

const char *TransferGroup::name() const
{
    return "Transfer";
}

TransferPort &TransferGroup::port()
{
    return m_port;
}

void TransferGroup::port(quint16 value)
{
    m_port = value;
}

FileBuffSize &TransferGroup::bufferSize()
{
    return m_bufferSize;
}

void TransferGroup::bufferSize(quint16 value)
{
    m_bufferSize = value;
}
