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
#include "OutlinedButton.h"

namespace shshare::widgets {

OutlinedButton::OutlinedButton(QString text, QWidget* parent) :
    QPushButton(text, parent)
{
    this->setStyleSheet(QString::fromUtf8(
        "height: 36px;"
        "min-width: 112px;"
        "padding: 2px;"
        "color: #FFFFFF;"
        "border: 1px solid #FFFFFF;"
        "background-color: transparent;"
        "border-radius: 5px;"
        "font-family: Roboto;"
        "font-size: 20px;"
        "font-weight: bold;"
        ));
    this->setCursor(Qt::PointingHandCursor);
}

}

