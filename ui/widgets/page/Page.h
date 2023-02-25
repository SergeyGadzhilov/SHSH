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
#ifndef WIDGETS_PAGE_PAGE_H
#define WIDGETS_PAGE_PAGE_H

#include "ui/widgets/StyledWidget.h"

namespace shshare::widgets::page {

class Page : public StyledWidget
{
    Q_OBJECT
public:
    explicit Page(QWidget *parent = nullptr);
};

} //namespace shshare::widgets::page



#endif // WIDGETS_PAGE_PAGE_H
