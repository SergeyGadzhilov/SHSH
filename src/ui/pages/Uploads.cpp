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
#include <QFileDialog>

#include "Uploads.h"
#include "ui/widgets/page/Title.h"

namespace shshare::pages {

Uploads::Uploads(QWidget *parent)
    : widgets::page::Page{parent}
    , m_layout(this)
    , m_table(this)
{
    m_layout.setMargin(25);
    m_layout.addWidget(new widgets::page::Title("Uploads"));
    initToolbar();
    m_table.setColumnName(0, tr("Destination"));
    m_layout.addWidget(&m_table);
}

bool Uploads::isAllFinished() const
{
    return m_table.isAllFinished();
}

void Uploads::insert(Connection *connection)
{
    m_table.insert(connection);
}

void Uploads::clear()
{
    m_table.removeCompleted();
}

void Uploads::initToolbar()
{
    connect(&m_toolBar, &widgets::uploads::ToolBar::clear, this, &Uploads::clear);
    connect(&m_toolBar, &widgets::uploads::ToolBar::addFile, this, [this](){emit sendFile();});
    connect(&m_toolBar, &widgets::uploads::ToolBar::addFolder, this, [this](){emit sendFolder();});

    m_layout.addWidget(&m_toolBar);
}

} //namespace shshare::pages

