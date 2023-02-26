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
#ifndef STORAGE_H
#define STORAGE_H

#include "settings/Group.h"
#include "DownloadDir.h"
#include "ReplaceExistingFile.h"

class Storage : public Group
{
public:
    Storage();
    // ISetting interface
    const char *name() const override;

    const QString downloadDir() const;
    void downloadDir(const QString& dir);

    bool replaceExisting() const;
    void replaceExisting(bool value);

private:
    DownloadDir m_downloadDir;
    ReplaceExistingFile m_replaceFile;
};

#endif // STORAGE_H
