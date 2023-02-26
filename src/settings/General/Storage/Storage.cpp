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
#include "Storage.h"

Storage::Storage()
{
    add(&m_downloadDir);
    add(&m_replaceFile);
}

const char *Storage::name() const
{
    return "Storage";
}

const QString Storage::downloadDir() const
{
    return m_downloadDir;
}

void Storage::downloadDir(const QString& dir)
{
    m_downloadDir = dir;
}

bool Storage::replaceExisting() const
{
    return m_replaceFile;
}

void Storage::replaceExisting(bool value)
{
    m_replaceFile = value;
}
