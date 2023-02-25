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
#include <QLineEdit>
#include "TextEdit.h"
#include "Spacer.h"

namespace shshare::widgets::settings {

TextEdit::TextEdit(const QString& title, const QString& value, QWidget *parent):
    StyledWidget{parent}
  , m_title{title,this}
  , m_value{value, this}
  , m_layout{this}
{
    m_layout.setMargin(0);
    addLabel();
    m_layout.addWidget(new Spacer(QSizePolicy::Expanding, QSizePolicy::Preferred));
    addTextEdit();
}

void TextEdit::setTitle(const QString &title)
{
    m_title.setText(title);
}

void TextEdit::setValue(const QString &value)
{
    m_value.setText(value);
}

void TextEdit::addLabel()
{
    m_title.setMargin(10);
    m_layout.addWidget(&m_title);
}

void TextEdit::addTextEdit()
{
    m_value.setStyleSheet("\
        font-family: \"Roboto\"; \
        font-size: 16px; \
        height: 50px \
    ");
    connect(&m_value, &QLineEdit::textChanged, this, [this](const QString& value){emit onChanged(value);});
    m_layout.addWidget(&m_value);
}

} //namespace shshare::widgets::settings

