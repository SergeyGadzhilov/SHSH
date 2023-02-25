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
#include "Toggle.h"
#include "Spacer.h"
#include "ToggleButton.h"

namespace shshare::widgets::settings {

Toggle::Toggle(const QString& title, bool value, QWidget *parent)
    : StyledWidget{parent}
    , m_layout{this}
    , m_button{this}
{
    m_layout.setSpacing(0);
    m_layout.setMargin(10);
    m_layout.addWidget(new QLabel(title));
    m_layout.addWidget(new Spacer(QSizePolicy::Expanding, QSizePolicy::Preferred));

    m_button.setChecked(value);
    addButton();
}

void Toggle::setValue(bool value)
{
    m_button.setChecked(value);
}

void Toggle::addButton()
{
    connect(&m_button, &ToggleButton::clicked, this, [this](bool checked){
        emit onChanged(checked);
    });
    m_layout.addWidget(&m_button);
}

} //namespace shshare::widgets::settings
