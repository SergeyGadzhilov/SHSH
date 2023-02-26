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
#include <QCursor>
#include "Button.h"

namespace shshare::widgets::sidebar {

Button::Button(const QIcon& icon, const QString &text, QWidget *parent)
    : QPushButton(icon, text, parent)
{
    setMinimumWidth(100);
    setMinimumHeight(80);
    setCursor(QCursor(Qt::PointingHandCursor));
    setIconSize(QSize(32, 32));
}

void Button::activate()
{
    setStyleSheet("background-color: #1E293B");
}

void Button::disactivate()
{
    setStyleSheet("background-color: #0F172A");
}

}

