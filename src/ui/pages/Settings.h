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
#ifndef PAGES_SETTIGNS_H
#define PAGES_SETTIGNS_H

#include <QTabWidget>
#include <QVBoxLayout>
#include "ui/widgets/page/Page.h"

namespace shshare::pages {

class Settings : public widgets::page::Page
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = nullptr);

private:
    QWidget* tabGeneral();
    QWidget* tabNetwork();
    QWidget* tabStorage();
    QTabWidget* tabs();

    QVBoxLayout m_layout;
};

} //namespace shshare::pages

#endif // PAGES_SETTIGNS_H
