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
#include "EnterIpPage.h"

#include "ui/widgets/FilledButton.h"
#include "ui/widgets/OutlinedButton.h"

using namespace shshare::widgets;
namespace shshare::ui
{

EnterIpPage::EnterIpPage(QWidget *parent)
    : QWidget{parent}
{
    initLayout();
    initTitle();
    initIpAddress();
    m_layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    initFooter();
}

void EnterIpPage::initLayout()
{
    m_layout = new QVBoxLayout(this);
    m_layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void EnterIpPage::initTitle()
{
    auto label = new QLabel("Enter ip address:", this);
    label->setAlignment(Qt::AlignCenter);
    m_layout->addWidget(label);
}

void EnterIpPage::initIpAddress()
{
    m_address = new IpAddress(this);
    m_layout->addWidget(m_address);
}

void EnterIpPage::initFooter()
{
    auto footer = new QHBoxLayout();
    footer->setSpacing(20);
    footer->setContentsMargins(40, 0, 40, 0);

    auto sendButton = new FilledButton("Connect", this);
    connect(sendButton, &FilledButton::clicked, this, [this](){
        if (m_address->Validate())
        {
            m_address->Reset();
            emit OnConnect();
        }
    });
    footer->addWidget(sendButton);

    auto cancelButton = new OutlinedButton("Cancel", this);
    connect(cancelButton, &OutlinedButton::clicked, this, [this](){
        m_address->Reset();
        emit OnClose();
    });
    footer->addWidget(cancelButton);

    m_layout->addLayout(footer);
}

}
