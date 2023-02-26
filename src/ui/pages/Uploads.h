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
#ifndef PAGES_UPLOADS_H
#define PAGES_UPLOADS_H

#include <QVBoxLayout>

#include "net/Connection.h"
#include "ui/widgets/page/Page.h"
#include "ui/widgets/table/Table.h"
#include "ui/widgets/uploads/ToolBar.h"

namespace shshare::pages {

class Uploads : public widgets::page::Page
{
    Q_OBJECT
public:
    explicit Uploads(QWidget *parent = nullptr);
    bool isAllFinished() const;
    void insert(Connection *connection);

signals:
    void sendFile();
    void sendFolder();

private slots:
    void clear();

private:
    void initToolbar();

    QVBoxLayout m_layout;
    widgets::uploads::ToolBar m_toolBar;
    widgets::table::Table m_table;
};

}

#endif // PAGES_UPLOADS_H
