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
#ifndef GENERAL_H
#define GENERAL_H

#include "settings/Group.h"
#include "Profile/Profile.h"
#include "Storage/Storage.h"

class General : public Group
{
public:
    General();

    // ISetting interface
    const char *name() const override;

    Profile& profile();
    const Profile& profile() const;

    Storage& storage();
    const Storage storage() const;

private:
    Profile m_profile;
    Storage m_storage;
};

#endif // GENERAL_H
