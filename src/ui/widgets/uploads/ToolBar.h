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
#ifndef WIDGETS_UPLOADS_TOOLBAR_H
#define WIDGETS_UPLOADS_TOOLBAR_H

#include <QWidget>
#include <QHBoxLayout>

namespace shshare::widgets::uploads {

class ToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit ToolBar(QWidget *parent = nullptr);

signals:
    void clear();
    void addFile();
    void addFolder();

private:
    void addSpacer();
    void addButton(const QIcon& icon, std::function<void ()> method);

    QHBoxLayout m_layout;
};

} //namespace shshare::widgets::uploads


#endif // WIDGETS_UPLOADS_TOOLBAR_H
