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
#include <QDesktopServices>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QListView>
#include <QTreeView>
#include <QDirIterator>

#include "net/Upload.h"
#include "net/Download.h"
#include "settings/Settings.h"

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DestinationDialog.h"
#include "ui/pages/Uploads.h"
#include "ui/pages/Downloads.h"
#include "widgets/sidebar/SideBar.h"

using namespace shshare::widgets;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_broadcaster(this),
    m_tray(this)
{
    ui->setupUi(this);
    setWindowTitle(::shshare::Settings::AppName());

    setupServer();
    setupSidebar();
    setupTrayIcon();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //Hide to tray
    if (m_tray.isVisible() && !mForceQuit) {
        setMainWindowVisibility(false);
        event->ignore();
        return;
    }

    if (!ui->downloads->isAllFinished() ||
        !ui->uploads->isAllFinished()) {
        const auto title = tr("Confirm close");
        const auto description = tr("You are about to close & abort all transfers. Do you want to continue?");
        if (QMessageBox::question(this, title, description) == QMessageBox::No) {
            event->ignore();
            mForceQuit = false;
            return;
        }
    }

    event->accept();
    qApp->quit();
}

void MainWindow::setMainWindowVisibility(bool visible)
{
    if (visible) {
        showNormal();
        setWindowState(Qt::WindowNoState);
        qApp->processEvents();
        setWindowState(Qt::WindowActive);
        qApp->processEvents();
        qApp->setActiveWindow(this);
        qApp->processEvents();
    }
    else {
        hide();
    }
}

void MainWindow::setupServer()
{
    m_broadcaster.start();
    m_hosts = new HostList(m_broadcaster, this);
    m_server = new Server(m_hosts, this);
    m_server->listen();
    connect(m_server, &Server::newReceiverAdded, ui->downloads, &shshare::pages::Downloads::insert);
}

void MainWindow::selectReceiversAndSendTheFiles(const QStringList& paths)
{
    DestinationDialog dialog(m_hosts);
    if (dialog.exec() == QDialog::Accepted) {
        QVector<Host> receivers = dialog.getSelectedHosts();
        for (const auto& receiver : receivers) {
            if (receiver.isValid()) {
                m_broadcaster.send();
                for (const auto& path : paths) {
                    send(receiver, path);
                }
            }
        }
    }
}

void MainWindow::send(const Host &receiver, const QFileInfo path)
{
    if (path.isDir()) {
        const auto filter = QDir::NoDotAndDotDot | QDir::Files;
        QDirIterator it(path.absoluteFilePath(), filter, QDirIterator::Subdirectories);
        while(it.hasNext()) {
            const auto file = it.next();
            const QFileInfo dir{path.dir().relativeFilePath(file)};
            sendFile(receiver, dir.path(), file);
        }
    }
    else {
        sendFile(receiver, "", path.absoluteFilePath());
    }
}

void MainWindow::sendFile(const Host &receiver, const QString &folder, const QString &file)
{
    auto sender = new Upload(receiver, folder, file, this);
    sender->start();
    ui->uploads->insert(sender);
}

void MainWindow::onShowMainWindowTriggered()
{
    setMainWindowVisibility(true);
}

void MainWindow::onSendFilesActionTriggered()
{
    auto selected = QFileDialog::getOpenFileNames(this, tr("Select files"), QDir::homePath());
    if (!selected.empty()) {
        selectReceiversAndSendTheFiles(selected);
    }
}

void MainWindow::onSendFolderActionTriggered()
{
    QFileDialog fDialog(this);
    fDialog.setDirectory(QDir::homePath());
    fDialog.setFileMode(QFileDialog::Directory);
    fDialog.setOption(QFileDialog::ShowDirsOnly);

    QListView* lView = fDialog.findChild<QListView*>("listView");
    if (lView)
        lView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    QTreeView* tView = fDialog.findChild<QTreeView*>("treeView");
    if (tView)
        tView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    if (fDialog.exec()) {
        auto dirs = fDialog.selectedFiles();
        if (!dirs.empty()) {
            selectReceiversAndSendTheFiles(dirs);
        }
    }
}

void MainWindow::openPage(shshare::pages::Page page)
{
    ui->pages->setCurrentIndex(static_cast<int>(page));
}

void MainWindow::quitApp()
{
    mForceQuit = true;
    close();
}

void MainWindow::setupSidebar()
{
    connect(ui->sidebar, &SideBar::openPage, this, &MainWindow::openPage);
    connect(ui->uploads, &shshare::pages::Uploads::sendFile, this, &MainWindow::onSendFilesActionTriggered);
    connect(ui->uploads, &shshare::pages::Uploads::sendFolder, this, &MainWindow::onSendFolderActionTriggered);

}

void MainWindow::setupTrayIcon()
{
    connect(&m_tray, &Tray::exit,           this, &MainWindow::quitApp);
    connect(&m_tray, &Tray::sendFiles,      this, &MainWindow::onSendFilesActionTriggered);
    connect(&m_tray, &Tray::sendFolders,    this, &MainWindow::onSendFolderActionTriggered);
    connect(&m_tray, &Tray::showMainWindow, this, &MainWindow::onShowMainWindowTriggered);

    m_tray.show();
}
