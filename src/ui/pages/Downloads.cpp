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

#include "Downloads.h"
#include "ui/widgets/page/Title.h"

namespace shshare::pages {

Downloads::Downloads(QWidget *parent)
    : widgets::page::Page{parent}
    , m_layout(this)
{
    m_layout.setMargin(25);
    m_layout.addWidget(new widgets::page::Title("Downloads", this));
    initToolbar();
    m_layout.addWidget(&m_table);
}

bool Downloads::isAllFinished() const
{
    return m_table.isAllFinished();
}

void Downloads::insert(Connection *connection)
{
    m_table.insert(connection);
}

void Downloads::clear()
{
    m_table.removeCompleted();
}

void Downloads::initToolbar()
{
    connect(&m_toolBar, &widgets::downloads::ToolBar::clear, this, &Downloads::clear);
    m_layout.addWidget(&m_toolBar);
}

} //namespace shshare::pages
