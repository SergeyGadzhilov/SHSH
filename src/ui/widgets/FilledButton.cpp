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
#include "FilledButton.h"

namespace shshare::widgets {

FilledButton::FilledButton(QString text, QWidget* parent) :
    QPushButton(text, parent)
{
    this->setStyleSheet(QString::fromUtf8(
        "height: 36px;"
        "min-width: 112px;"
        "padding: 2px;"
        "color: #1B293D;"
        "border: 1px solid #4DEB67;"
        "background-color: #4DEB67;"
        "border-radius: 5px;"
        "font-family: Roboto;"
        "font-size: 20px;"
        "font-weight: bold;"
    ));
    this->setCursor(Qt::PointingHandCursor);
}

}
