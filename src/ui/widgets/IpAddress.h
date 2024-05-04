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
#ifndef SHSHARE_WIDGETS_IPADDRESS_H
#define SHSHARE_WIDGETS_IPADDRESS_H

#include <array>
#include <QWidget>
#include <QHBoxLayout>
#include <QHostAddress>
#include "ui/widgets/IpAddress/IpAddressItem.h"

namespace shshare::widgets
{

class IpAddress : public QWidget
{
    Q_OBJECT
public:
    explicit IpAddress(QWidget *parent = nullptr);
    bool Validate();
    void Clear();
    void Reset();
    const QHostAddress GetHostAddress() const;

private:
    void initLayout();
    void initControls();
    void addDot();

    std::array<IpAddressItem, 4> m_items;
    QHBoxLayout* m_layout = nullptr;
};

}


#endif // SHSHARE_WIDGETS_IPADDRESS_H
