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
#ifndef SHSHARE_WIDGETS_IPADDRESSITEM_H
#define SHSHARE_WIDGETS_IPADDRESSITEM_H

#include <QLineEdit>

namespace shshare::widgets {

class IpAddressItem : public QLineEdit
{
public:
    IpAddressItem(QWidget* parent = nullptr);
    uint Value() const;
    bool IsValid() const;
    void Highlight();
    void Clear();
    void Reset();
protected:
    void keyPressEvent(QKeyEvent *) override;
};

}

#endif // SHSHARE_WIDGETS_IPADDRESSITEM_H
