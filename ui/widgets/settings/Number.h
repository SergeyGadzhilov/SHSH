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
#ifndef WIDGETS_SETTINGS_NUMBER_H
#define WIDGETS_SETTINGS_NUMBER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QSpinBox>
#include "ui/widgets/StyledWidget.h"

namespace shshare::widgets::settings {

class Number : public StyledWidget
{
    Q_OBJECT
public:
    explicit Number(const QString& title, quint64 value, QWidget *parent = nullptr);
    void setValue(quint64 value);
    void setMinimum(int value);
    void setMaximum(int value);
    void setSingleStep(int value);
    void setSuffix(const QString& suffix);

signals:
    void onChanged(int value);

private:
    void init();
    QSpinBox m_value;
    QHBoxLayout m_layout;
};

} //namespace shshare::widgets::settings

#endif // WIDGETS_SETTINGS_NUMBER_H
