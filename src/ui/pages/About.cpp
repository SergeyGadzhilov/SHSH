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
#include <QLabel>
#include <QFile>
#include <QHBoxLayout>

#include "About.h"
#include "settings/Settings.h"
#include "ui/widgets/page/Title.h"

namespace shshare::pages {

About::About(QWidget *parent)
    : widgets::page::Page{parent}
{
    auto content = new QVBoxLayout();
    content->addWidget(appName());
    content->addWidget(description());
    content->addWidget(author());
    content->setMargin(0);

    m_layout.addWidget(new widgets::page::Title("About", this));
    m_layout.addLayout(content);
    m_layout.addWidget(license());
    m_layout.setMargin(25);
    setLayout(&m_layout);
}

QLabel* About::appName()
{
    auto appName = new QLabel(this);
    appName->setText(QString("%1 version %2").arg(Settings::AppName(), Settings::AppVersion()));
    return appName;
}

QLabel* About::description()
{
    auto description = new QLabel(this);
    description->setText("SHShare is a file sharing application to transfer files over local network.");

    return description;
}

QLabel* About::author()
{
    auto author = new QLabel(this);
    author->setText("Author: Hadzhilov Serhii (gadzhilovsergey@gmail.com)");
    return author;
}

QTextEdit* About::license()
{
    QFile file(":/text/gpl-3.0.txt");
    file.open(QIODevice::ReadOnly);
    auto license = new QTextEdit(this);
    license->setText(file.readAll());

    return license;
}

QWidget* About::spacer()
{
    auto spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    return spacer;
}

} //shshare::pages
