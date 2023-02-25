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
#include <QMenu>

#include "Tray.h"
#include "settings/Settings.h"

Tray::Tray(QWidget* parent) :
    QSystemTrayIcon(parent),
    m_window(parent)
{
    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        setIcon(QIcon(":/icons/logo.svg"));
        setToolTip(::shshare::Settings::AppName());
        initMenu();
    }
}

void Tray::initMenu()
{
    auto menu = new QMenu(m_window);

    menu->addAction(createAction(tr("Open"), [this](){emit showMainWindow();}));
    menu->addSeparator();
    menu->addAction(createAction(QIcon(":/img/file.png"), tr("Send files..."), [this](){emit sendFiles();}));
    menu->addAction(createAction(QIcon(":/img/folder.png"), tr("Send folders..."), [this](){emit sendFolders();}));
    menu->addSeparator();
    menu->addAction(createAction(tr("Exit"), [this](){emit exit();}));

    setContextMenu(menu);
}

QAction *Tray::createAction(const QString& name, std::function<void()> method)
{
    auto action = new QAction(name, this);
    connect(action, &QAction::triggered, this, method);
    return action;
}

QAction *Tray::createAction(QIcon &icon, const QString &name, std::function<void ()> method)
{
    auto action = new QAction(icon, name, this);
    connect(action, &QAction::triggered, this, method);
    return action;
}
