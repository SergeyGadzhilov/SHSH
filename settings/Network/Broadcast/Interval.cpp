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
#include "Interval.h"

Interval::Interval(Group* group)
{
    if (group) {
        group->add(this);
    }
}

const char* Interval::name() const
{
    return "Interval";
}

void Interval::load(const QSettings& storage)
{
    m_interval = storage.value(name(), DefaultBroadcastInterval).value<quint16>();
}

void Interval::save(QSettings &storage) const
{
    storage.setValue(name(), m_interval);
}

void Interval::reset()
{
    m_interval = DefaultBroadcastInterval;
}

Interval::operator quint16() const
{
    return m_interval;
}

void Interval::operator =(quint16 value)
{
    m_interval = value;
}
