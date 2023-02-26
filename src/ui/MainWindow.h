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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Tray.h"
#include "pages/Pages.h"
#include "net/Server.h"
#include "net/Broadcaster.h"
#include "ui/models/HostList.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent* event) override;

public Q_SLOTS:
    void setMainWindowVisibility(bool visible = true);

private Q_SLOTS:
    void onShowMainWindowTriggered();
    void onSendFilesActionTriggered();
    void onSendFolderActionTriggered();
    void openPage(shshare::pages::Page page);
    void quitApp();

private:
    void setupServer();
    void setupSidebar();
    void setupTrayIcon();

    void selectReceiversAndSendTheFiles(QVector<QPair<QString, QString> > dirNameAndFullPath);
    QVector< QPair<QString, QString> >getInnerDirNameAndFullFilePath(const QDir& startingDir,
                                                                     const QString& innerDirName);

    bool mForceQuit{false};
    Ui::MainWindow *ui{nullptr};
    Tray m_tray;

    HostList* m_hosts{nullptr};
    Broadcaster m_broadcaster;
    Server* m_server{nullptr};
};

#endif // MAINWINDOW_H
