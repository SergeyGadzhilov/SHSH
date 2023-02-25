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
#ifndef WIDGETS_SIDEBAR_BUTTON_H
#define WIDGETS_SIDEBAR_BUTTON_H

#include <QPushButton>

namespace shshare::widgets::sidebar {

class Button : public QPushButton
{
    Q_OBJECT
public:
    Button(const QIcon& icon, const QString &text, QWidget *parent = nullptr);
    void activate();
    void disactivate();
};

}

#endif // WIDGETS_SIDEBAR_BUTTON_H
