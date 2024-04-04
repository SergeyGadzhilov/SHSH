/*
 * SHShare - LAN file transfer application.
 * Copyright (C) 2024 Hadzhilov Serhii
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "IconButton.h"
namespace shshare::widgets {

IconButton::IconButton(uint icon, QWidget *parent) :
    QPushButton(QChar(icon), parent)
{
    this->setStyleSheet(QString::fromUtf8(
        "color: #FFFFFF;"
        "border: none;"
        "padding-top: 10px;"
        "background-color: transparent;"
        "font-family: MaterialIcons;"
        "font-size: 24px;"
        "font-weight: bold;"
        ));
    this->setCursor(Qt::PointingHandCursor);
}

}

