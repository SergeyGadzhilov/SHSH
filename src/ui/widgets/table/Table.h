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
#ifndef WIDGETS_CONNECTIONS_TABLE_H
#define WIDGETS_CONNECTIONS_TABLE_H

#include <QTableView>
#include <QObject>

#include "TableModel.h"

namespace shshare::widgets::table {

class Table : public QTableView
{
    Q_OBJECT
public:
    explicit Table(QWidget *parent = nullptr);
    bool isAllFinished() const;
    bool isSelectedFinished() const;
    void insert(Connection* connection);
    void removeSelected();
    void removeCompleted();
    void cancelSelected();
    void pauseSelected();
    void resumeSelected();

    QString getSelectedFile();
    ConnectionInfo* getConnectionByPosition(const QPoint& pos);
    void setColumnName(int column, const QString& name);

signals:
    void onSelected(const ConnectionInfo* connection);
    void onDeselected(const ConnectionInfo* connection);

private slots:
    void onSelectionChanged(const QItemSelection& selected,
                            const QItemSelection& deselected);

private:
    ConnectionInfo *getConnection(const QItemSelection& selection) const;
    TableModel* m_model{nullptr};
};

} //namespace shshare::widgets::connections

#endif // WIDGETS_CONNECTIONS_TABLE_H
