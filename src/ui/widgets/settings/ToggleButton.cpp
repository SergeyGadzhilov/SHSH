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
#include <QEvent>
#include <QCoreApplication>

#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include "ToggleButton.h"

namespace shshare::widgets::settings {

ToggleButton::ToggleButton(QWidget *parent)
    : QAbstractButton{parent}
    , m_animation{this}
{
    setCheckable(true);
    setSizePolicy(QSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed));
    m_animation.setTargetObject(this);

    m_margin = 0 > (m_thumbRadius - m_trackRadius) ? 0 : (m_thumbRadius - m_trackRadius);
    m_baseOffset = m_thumbRadius > m_trackRadius ? m_thumbRadius : m_trackRadius;
    m_endOffset.insert(true, 4 * m_trackRadius + 2 * m_margin - m_baseOffset); // width - offset
    m_endOffset.insert(false, m_baseOffset);
    m_offset = m_baseOffset;
    QPalette palette = this->palette();
    palette.setColor(QPalette::ColorRole::Highlight, QColor(34,197,94));

    m_trackColor.insert(true, palette.highlight());
    m_trackColor.insert(false, palette.dark());
    m_thumbColor.insert(true, palette.highlight());
    m_thumbColor.insert(false, palette.light());
}

QSize ToggleButton::sizeHint() const
{
    int w = 4 * m_trackRadius + 2 * m_margin;
    int h = 2 * m_trackRadius + 2 * m_margin;

    return QSize(w, h);
}

void ToggleButton::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    auto m_paintFlags = QPainter::RenderHints(QPainter::Antialiasing |
                                              QPainter::TextAntialiasing);
    p.setRenderHints(m_paintFlags, true);
    p.setPen(Qt::NoPen);
    qreal trackOpacity = 0.5;

    QBrush trackBrush;
    QBrush thumbBrush;

    if (this->isEnabled())
    {
        trackBrush = m_trackColor[isChecked()];
        thumbBrush = m_thumbColor[isChecked()];
    }
    else
    {
        trackOpacity *= 0.8;
        trackBrush = this->palette().shadow();
        thumbBrush = this->palette().mid();
    }

    p.setBrush(trackBrush);
    p.setOpacity(trackOpacity);
    p.drawRoundedRect(m_margin, m_margin, width() - 2 * m_margin, height() - 2 * m_margin, m_trackRadius, m_trackRadius);

    p.setBrush(thumbBrush);
    p.setOpacity(1.0);
    p.drawEllipse(m_offset - m_thumbRadius, m_baseOffset - m_thumbRadius, 2 * m_thumbRadius, 2 * m_thumbRadius);
}

void ToggleButton::resizeEvent(QResizeEvent* e)
{
    QAbstractButton::resizeEvent(e);
    m_offset = m_endOffset.value(isChecked());
}

void ToggleButton::mouseReleaseEvent(QMouseEvent  *e)
{
    QAbstractButton::mouseReleaseEvent(e);
    if (e->button() == Qt::LeftButton)
    {
        m_animation.setDuration(120);
        m_animation.setPropertyName("offset");
        m_animation.setStartValue(m_offset);
        m_animation.setEndValue(m_endOffset[isChecked()]);
        m_animation.start();
    }
}

void ToggleButton::enterEvent(QEvent * event)
{
    setCursor(Qt::PointingHandCursor);
    QAbstractButton::enterEvent(event);
}

void ToggleButton::setChecked(bool checked)
{
    QAbstractButton::setChecked(checked);
    m_offset = m_endOffset.value(checked);
}

int ToggleButton::offset()
{
    return m_offset;
}

void ToggleButton::setOffset(int value)
{
    m_offset = value;
    update();
}

} //namespace shshare::widgets::settings

