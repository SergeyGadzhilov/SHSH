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
#include <QAction>
#include <QLabel>
#include <QToolButton>
#include "Button.h"
#include "SideBar.h"

namespace shshare::widgets {

SideBar::SideBar(QWidget *parent)
    : StyledWidget{parent}
    , m_about(QIcon(":/icons/about.svg"), tr(""), this)
    , m_uploads(QIcon(":/icons/upload.svg"), tr(""), this)
    , m_settings(QIcon(":/icons/settings.svg"), tr(""), this)
    , m_downloads(QIcon(":/icons/download.svg"), tr(""), this)
{
    addLogo();
    m_downloads.activate();
    addButton(m_downloads, pages::Page::Downloads);
    addButton(m_uploads, pages::Page::Uploads);
    addButton(m_settings, pages::Page::Settings);
    addSpacer();
    addButton(m_about, pages::Page::About);
    m_layout.setSpacing(0);
    m_layout.setMargin(0);
    setLayout(&m_layout);
}

void SideBar::addLogo()
{
    auto logo = new QLabel(this);
    logo->setMargin(25);
    logo->setPixmap(QPixmap(":/icons/logo.svg"));
    m_layout.addWidget(logo);
}

void SideBar::addSpacer()
{
    auto spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    m_layout.addWidget(spacer);
}

void SideBar::resetAllButtons()
{
    m_about.disactivate();
    m_uploads.disactivate();
    m_settings.disactivate();
    m_downloads.disactivate();
}

void SideBar::addButton(sidebar::Button& button, pages::Page page)
{
    connect(&button, &sidebar::Button::clicked, this, [this, &button, page](){
        activateButton(button, page);
        emit openPage(page);
    });
    m_layout.addWidget(&button);
}

void SideBar::activateButton(sidebar::Button &button, pages::Page page)
{
    resetAllButtons();
    button.activate();
}

} //namespace shshare::widgets
