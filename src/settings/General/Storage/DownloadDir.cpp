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
#include <QDir>
#include <QStandardPaths>

#include "DownloadDir.h"

DownloadDir::DownloadDir()
{
    m_dir.setPath(getDefaultDownloadPath());
}

const char* DownloadDir::name() const
{
    return "DownloadDir";
}

void DownloadDir::load(const QSettings &storage)
{
    const auto& dir = storage.value(name(), getDefaultDownloadPath()).toString();
    if (!dir.isEmpty() && QDir(dir).exists()) {
        m_dir.setPath(dir);
    }
}

void DownloadDir::save(QSettings &storage) const
{
    storage.setValue(name(), m_dir.absolutePath());
}

void DownloadDir::reset()
{
    m_dir.setPath(getDefaultDownloadPath());
}

DownloadDir::operator QString() const
{
    return QDir::toNativeSeparators(m_dir.absolutePath());
}

void DownloadDir::operator =(const QString &value)
{
    m_dir.setPath(value);
}

QString DownloadDir::getDefaultDownloadPath() const
{
    QString name("SHShare");

#if defined (Q_OS_WIN)
    return
        QStandardPaths::locate(QStandardPaths::DownloadLocation,
                               QString(),
                               QStandardPaths::LocateDirectory) + name;
#else
    return QDir::homePath() + QDir::separator() + name;
#endif
}
