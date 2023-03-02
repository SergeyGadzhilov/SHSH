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
#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include <QApplication>
#include <QtNetwork/QLocalServer>
#include "ui/MainWindow.h"

class Launcher : public QObject
{
    Q_OBJECT

public:
    explicit Launcher(const QString& name);
    int startApplication(const QApplication& app);

private slots:
    void onConnect();

private:
    bool isAlreadyRunning() const;

    QString m_Name;
    QLocalServer m_Server;
    MainWindow m_mainWindow;
};

#endif // LAUNCHER_H
