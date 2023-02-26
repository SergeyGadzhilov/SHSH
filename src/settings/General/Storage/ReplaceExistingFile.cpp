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
#include "ReplaceExistingFile.h"

void ReplaceExistingFile::reset()
{
    m_value = false;
}

const char* ReplaceExistingFile::name() const
{
    return "ReplaceExistingFile";
}

void ReplaceExistingFile::load(const QSettings &storage)
{
    m_value = storage.value(name(), false).toBool();
}

void ReplaceExistingFile::save(QSettings &storage) const
{
    storage.setValue(name(), m_value);
}

ReplaceExistingFile::operator bool() const
{
    return m_value;
}

void ReplaceExistingFile::operator =(bool value)
{
    m_value = value;
}
