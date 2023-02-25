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
#include <QtNetwork/QLocalSocket>

#include "Launcher.h"

Launcher::Launcher(const QString& name):
    m_Name(name)
{
    connect(&m_Server, &QLocalServer::newConnection, this, &Launcher::onConnect);
}

int Launcher::startApplication(const QApplication& app)
{
    if (isAlreadyRunning()) {
        return EXIT_SUCCESS;
    }

    m_Server.removeServer(m_Name);
    if (m_Server.listen(m_Name)) {
        m_mainWindow.show();
        return app.exec();
    }
    else {
        qDebug() << m_Server.errorString();
        return EXIT_FAILURE;
    }
}

bool Launcher::isAlreadyRunning() const
{
    QLocalSocket socket;
    socket.connectToServer(m_Name);
    return socket.waitForConnected();
}

void Launcher::onConnect()
{
    m_mainWindow.setMainWindowVisibility(true);
}
