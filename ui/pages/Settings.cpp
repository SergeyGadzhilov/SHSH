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
#include "Settings.h"
#include "settings/Settings.h"
#include "ui/widgets/page/Title.h"
#include "ui/widgets/settings/Tab.h"
#include "ui/widgets/settings/Label.h"
#include "ui/widgets/settings/Spacer.h"
#include "ui/widgets/settings/Name.h"
#include "ui/widgets/settings/DownloadDir.h"
#include "ui/widgets/settings/TransferPort.h"
#include "ui/widgets/settings/BroadcastPort.h"
#include "ui/widgets/settings/OverwriteFiles.h"
#include "ui/widgets/settings/BroadcastInterval.h"
#include "ui/widgets/settings/TransferBufferSize.h"


namespace shshare::pages {
using namespace shshare::widgets::settings;

Settings::Settings(QWidget *parent) :
    widgets::page::Page{parent},
    m_layout{this}
{
    m_layout.setMargin(25);
    m_layout.addWidget(new widgets::page::Title("Settings"));
    m_layout.addWidget(tabs());
}

QWidget *Settings::tabGeneral()
{
    auto& settings = ::shshare::Settings::instance();
    auto localHost = settings.getLocalHost();

    auto general = new Tab();
    general->add(new Label("Id", localHost.getId().c_str()));
    general->add(new Label("Ip", localHost.getAddress().toString()));
    general->add(new Label("Os", localHost.getOSName().c_str()));
    general->add(new Name(general));
    general->add(new Spacer());
    return general;
}

QWidget *Settings::tabNetwork()
{
    auto network = new Tab();
    network->add(new BroadcastPort(network));
    network->add(new BroadcastInterval(network));
    network->add(new TransferPort(network));
    network->add(new TransferBufferSize(network));
    network->add(new Spacer());
    return network;
}

QWidget *Settings::tabStorage()
{
    auto storage = new Tab();
    storage->add(new DownloadDir(storage));
    storage->add(new OverwriteFiles(this));
    storage->add(new Spacer());
    return storage;
}

QTabWidget* Settings::tabs()
{
    auto tabs = new QTabWidget(this);
    tabs->addTab(tabGeneral(), tr("General"));
    tabs->addTab(tabStorage(), tr("Storage"));
    tabs->addTab(tabNetwork(), tr("Network"));
    return tabs;
}

} //namespace shshare::pages

