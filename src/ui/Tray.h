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
#ifndef TRAY_H
#define TRAY_H

#include <QAction>
#include <QSystemTrayIcon>

class Tray : public QSystemTrayIcon
{
    Q_OBJECT

public:
    explicit Tray(QWidget *parent=nullptr);

signals:
    void exit();
    void sendFiles();
    void sendFolders();
    void showMainWindow();

private:
    void addAction();
    void initMenu();
    QAction* createAction(const QString& name, std::function<void()> method);
    QAction* createAction(QIcon& icon, const QString& name, std::function<void()> method);

    QWidget* m_window{nullptr};
};

#endif // TRAY_H
