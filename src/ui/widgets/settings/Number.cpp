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
#include <QLabel>
#include <QSpinBox>
#include "Number.h"

namespace shshare::widgets::settings {

Number::Number(const QString& title, quint64 value, QWidget *parent) :
    StyledWidget{parent},
    m_value{this},
    m_layout{this}
{
    m_layout.setMargin(0);

    auto label = new QLabel(title);
    label->setMargin(10);
    m_layout.addWidget(label);

    m_value.setStyleSheet(
        "height: 40px;"
        "margin: 0px;"
        "font-size: 16px;"
    );

    m_value.setValue(value);
    m_layout.addWidget(&m_value);
    connect(&m_value, &QSpinBox::textChanged, this, [this](const QString &){
        emit onChanged(m_value.value());
    });
}

void Number::setValue(quint64 value)
{
    m_value.setValue(value);
}

void Number::setMinimum(int value)
{
    m_value.setMinimum(value);
}

void Number::setMaximum(int value)
{
    m_value.setMaximum(value);
}

void Number::setSingleStep(int value)
{
    m_value.setSingleStep(value);
}

void Number::setSuffix(const QString &suffix)
{
    m_value.setSuffix(suffix);
}

} //namespace shshare::widgets::settings
