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
#include "General.h"

General::General()
{
    add(&m_profile);
    add(&m_storage);
}

const char* General::name() const
{
    return "General";
}

Profile &General::profile()
{
    return m_profile;
}

const Profile &General::profile() const
{
    return m_profile;
}

Storage &General::storage()
{
    return m_storage;
}

const Storage General::storage() const
{
    return m_storage;
}

