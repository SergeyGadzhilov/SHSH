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
#include <QIntValidator>
#include <QKeyEvent>
#include "IpAddressItem.h"
#include "IpValidator.h"

namespace shshare::widgets {

IpAddressItem::IpAddressItem(QWidget* parent) :
    QLineEdit(parent)
{
    setValidator(new IpValidator(this));
    setAlignment(Qt::AlignCenter);
    Clear();
}

uint IpAddressItem::Value() const
{
    return text().toUInt();
}

bool IpAddressItem::IsValid() const
{
    return !text().isEmpty();
}

void IpAddressItem::Highlight()
{
    setStyleSheet(QString::fromUtf8(
        "font-family: Roboto;"
        "font-size: 20px;"
        "font-weight: bold;"
        "height: 36px;"
        "border-radius: 5px;"
        "background-color: red;"
    ));
}

void IpAddressItem::Clear()
{
    setStyleSheet(QString::fromUtf8(
        "font-family: Roboto;"
        "font-size: 20px;"
        "font-weight: bold;"
        "height: 36px;"
        "border-radius: 5px;"
        ));
}

void IpAddressItem::Reset()
{
    Clear();
    setText("");
}

void IpAddressItem::keyPressEvent(QKeyEvent* event)
{
    Clear();
    QLineEdit::keyPressEvent(event);
}

}

