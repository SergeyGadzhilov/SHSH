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
#ifndef BROADCAST_H
#define BROADCAST_H

#include "settings/Group.h"
#include "Port.h"
#include "Interval.h"

class BroadcastSettings : public Group
{
public:
    BroadcastSettings(Group* parent = nullptr);

    // ISetting interface
    const char *name() const override;

    const Port& port() const;
    void port(quint16 value);

    const Interval& interval() const;
    void interval(quint16 value);

private:
    Port m_port{this};
    Interval m_interval{this};
};

#endif // BROADCAST_H
