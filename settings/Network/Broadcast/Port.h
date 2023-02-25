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
#ifndef BROADCASTPORT_H
#define BROADCASTPORT_H

#include "settings/Group.h"

class Port : public ISetting
{
public:
    explicit Port(Group* group = nullptr);

    // ISetting interface
    void reset() override;
    const char* name() const override;
    void load(const QSettings &storage) override;
    void save(QSettings &storage) const override;

    operator quint16() const;
    void operator =(quint16 value);

private:
    const quint16 DefaultPort{56780};
    quint16 m_Port{DefaultPort};
};

#endif // BROADCASTPORT_H
