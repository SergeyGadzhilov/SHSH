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
#include "ui/widgets/FilledButton.h"
#include "ErrorPage.h"

using namespace shshare::widgets;
namespace shshare::ui
{

ErrorPage::ErrorPage(QWidget *parent)
    : QWidget{parent}
{
    initLayout();
    initTitle();
    initFooter();
}

void ErrorPage::initLayout()
{
    m_layout = new QVBoxLayout(this);
}

void ErrorPage::initTitle()
{
    auto title = new QLabel("Can't connect to the ip address:", this);
    title->setAlignment(Qt::AlignCenter);
    m_layout->addWidget(title);
}

void ErrorPage::initFooter()
{
    auto footer = new QHBoxLayout();
    footer->setSpacing(20);
    footer->setContentsMargins(100, 0, 100, 0);

    auto okButton = new FilledButton("Ok", this);
    connect(okButton, &FilledButton::clicked, this, [this](){
        emit OnClose();
    });
    footer->addWidget(okButton);
    m_layout->addLayout(footer);
}

}

