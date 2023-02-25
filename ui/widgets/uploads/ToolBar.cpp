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
#include "ToolBar.h"
#include <QPushButton>

namespace shshare::widgets::uploads {

ToolBar::ToolBar(QWidget *parent)
    : QWidget{parent}
    , m_layout(this)
{
    addSpacer();
    addButton(QIcon(":/icons/addfolder.svg"), [this](){emit addFolder();});
    addButton(QIcon(":/icons/addfile.svg"), [this](){emit addFile();});
    addButton(QIcon(":/icons/clear.svg"), [this](){emit clear();});
}

void ToolBar::addSpacer()
{
    auto spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_layout.addWidget(spacer);
}

void ToolBar::addButton(const QIcon& icon, std::function<void ()> method)
{
    auto button = new QPushButton(this);
    button->setFlat(true);
    button->setIcon(icon);
    button->setCursor(QCursor(Qt::PointingHandCursor));
    connect(button, &QPushButton::clicked, this, method);
    m_layout.addWidget(button);
}

} //namespace shshare::widgets::uploads

