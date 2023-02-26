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
#ifndef WIDGETS_SETTINGS_TOGGLE_BUTTON_H
#define WIDGETS_SETTINGS_TOGGLE_BUTTON_H

#include <QAbstractButton>
#include <QPropertyAnimation>
#include "ui/widgets/StyledWidget.h"

namespace shshare::widgets::settings {

class ToggleButton : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(int offset READ offset WRITE setOffset CONSTANT)
public:
    explicit ToggleButton(QWidget *parent = nullptr);
    QSize sizeHint() const override;
    void setChecked(bool checked);

protected:
    int offset();
    void setOffset(int value);
    void paintEvent(QPaintEvent *) override;
    void enterEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent*) override;
    void mouseReleaseEvent(QMouseEvent *) override;

private:
    qreal m_offset;
    qreal m_baseOffset;
    qreal m_margin;
    qreal m_trackRadius{8};
    qreal m_thumbRadius{10};
    QPropertyAnimation m_animation;

    QHash<bool, qreal> m_endOffset;
    QHash<bool, QBrush> m_trackColor;
    QHash<bool, QBrush> m_thumbColor;
};

}

#endif // WIDGETS_SETTINGS_TOGGLE_BUTTON_H
