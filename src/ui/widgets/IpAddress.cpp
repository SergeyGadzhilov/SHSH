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
#include <QLabel>
#include <QIntValidator>
#include "IpAddress.h"

namespace shshare::widgets
{

IpAddress::IpAddress(QWidget *parent):
    QWidget{parent}
{
    initLayout();
    initControls();
}

bool IpAddress::Validate()
{
    Clear();

    bool isValid = true;
    std::for_each(m_items.begin(), m_items.end(), [&isValid](IpAddressItem& item){
        if (!item.IsValid())
        {
            item.Highlight();
            isValid = false;
        }
    });

    return isValid;
}

void shshare::widgets::IpAddress::initLayout()
{
    m_layout = new QHBoxLayout(this);
    m_layout->setSizeConstraint(QLayout::SetMinimumSize);
}

void IpAddress::initControls()
{
    std::for_each(m_items.begin(), m_items.end(), [this](IpAddressItem& item){
        m_layout->addWidget(&item);
        if (&item != &m_items.back())
        {
            addDot();
        }
    });
}

void IpAddress::addDot()
{
    auto dot = new QLabel(".", this);
    dot->setAlignment(Qt::AlignBottom);
    dot->setFixedHeight(36);
    m_layout->addWidget(dot);
}

void IpAddress::Clear()
{
    std::for_each(m_items.begin(), m_items.end(), [](IpAddressItem& item){
        item.Clear();
    });
}

void IpAddress::Reset()
{
    std::for_each(m_items.begin(), m_items.end(), [](IpAddressItem& item){
        item.Reset();
    });
}

}
