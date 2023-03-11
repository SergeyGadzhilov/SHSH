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
#include <QApplication>
#include <QFontDatabase>
#include "settings/Settings.h"
#include "launcher/Launcher.h"

void loadStyleSheets(QApplication& app) {
    QFile style(":/styles/style.qss");
    style.open(QFile::ReadOnly);
    app.setStyleSheet(style.readAll());
}

void registerFonts() {
    QFontDatabase::addApplicationFont(":/fonts/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto-Bold.ttf");
}


int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);

    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    app.setApplicationName(::shshare::Settings::AppName());
    app.setApplicationDisplayName(::shshare::Settings::AppName());
    app.setApplicationVersion(::shshare::Settings::AppVersion());
    loadStyleSheets(app);
    registerFonts();

    Launcher launcher(::shshare::Settings::AppName());
    return launcher.startApplication(app);
}
