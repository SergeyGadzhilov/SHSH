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
#include <QCursor>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>

#include "Path.h"
#include "Spacer.h"

namespace shshare::widgets::settings {

Path::Path(const QString& title, const QString& value, QWidget *parent)
    : StyledWidget{parent}
    , m_layout{this}
    , m_edit{value}
{
    m_layout.setMargin(0);
    m_layout.setSpacing(0);
    auto label = new QLabel(title);
    label->setMargin(10);
    m_layout.addWidget(label);
    m_layout.addWidget(new Spacer(QSizePolicy::Expanding, QSizePolicy::Preferred));

    addTextEdit();
    addButton();
}

void Path::setValue(const QString &value)
{
    m_edit.setText(value);
}

void Path::onOpen()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);

    if (dialog.exec()) {
        auto dir = dialog.selectedFiles();
        m_edit.setText(dir[0]);
    }
}

void Path::addButton()
{
    auto button = new QPushButton("...");
    button->setCursor(QCursor(Qt::PointingHandCursor));
    button->setStyleSheet(
        "height: 45px;"
        "width: 50px;"
        "border: none;"
        "line-height: 10px;"
        "font-size: 25px;"
        "background-color: #FFFFFF;"
    );
    m_layout.addWidget(button);
    connect(button, &QPushButton::clicked, this, &Path::onOpen);
}

void Path::addTextEdit()
{
    m_edit.setStyleSheet(
        "font-family: \"Roboto\";"
        "font-size: 16px;"
        "height: 45px;"
        "border: none;"
    );
    connect(&m_edit, &QLineEdit::textChanged, this, [this](const QString& value){emit onChanged(value);});
    m_layout.addWidget(&m_edit);
}

} //namespace shshare::widgets::settings
