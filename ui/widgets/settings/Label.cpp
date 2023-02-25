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
#include "Label.h"

namespace shshare::widgets::settings {

Label::Label(const QString& title, const QString& value, QWidget *parent) :
    StyledWidget{parent},
    m_layout{this}
{
    m_layout.addWidget(new QLabel(title));

    auto v = new QLabel(value);
    v->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    m_layout.addWidget(v);
}

} //namespace shshare::widgets::settings

