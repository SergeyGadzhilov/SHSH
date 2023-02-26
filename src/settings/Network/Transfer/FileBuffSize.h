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
#ifndef FILEBUFFSIZE_H
#define FILEBUFFSIZE_H

#include "settings/ISetting.h"

class FileBuffSize : public ISetting
{
public:
    // ISetting interface
    void reset() override;
    const char* name() const override;
    void load(const QSettings &storage) override;
    void save(QSettings &storage) const override;

    operator quint32() const;
    void operator =(quint32 value);
private:
    const quint32 DefaultFileBufferSize{98304}; // 96 KB
    quint32 m_bufferSize{DefaultFileBufferSize};
};

#endif // FILEBUFFSIZE_H
