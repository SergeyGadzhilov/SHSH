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
#ifndef DESTINATION_DIALOG_H
#define DESTINATION_DIALOG_H

#include <QDialog>

class HostList;
class Host;

namespace Ui {
class ReceiverSelectorDialog;
}

class DestinationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DestinationDialog(HostList* model, QWidget *parent = nullptr);
    ~DestinationDialog() override;

    Host getSelectedHost() const;
    QVector<Host> getSelectedHosts() const;

private Q_SLOTS:
    void onSendClicked();
    void onRefreshClicked();

private:
    Ui::ReceiverSelectorDialog *ui;

    HostList* mModel;
};

#endif // DESTINATION_DIALOG_H
