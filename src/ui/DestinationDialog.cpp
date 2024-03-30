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
#include <QMessageBox>
#include "DestinationDialog.h"
#include "ui_DestinationDialog.h"

#include "core/Host.h"
#include "ui/models/HostList.h"
#include "ui/widgets/FilledButton.h"
#include "ui/widgets/OutlinedButton.h"

using namespace shshare::widgets;

DestinationDialog::DestinationDialog(HostList* model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceiverSelectorDialog),
    mModel(model)
{
    ui->setupUi(this);

    ui->listView->setModel(mModel);
    ui->listView->setCurrentIndex(QModelIndex());
    ui->label->setStyleSheet(QString::fromUtf8(
        "font-family: Roboto;"
        "font-size: 20px;"
    ));

    auto sendButton = new FilledButton("Send", this);
    connect(sendButton, &FilledButton::clicked, this, &DestinationDialog::onSendClicked);
    ui->horizontalLayout->addWidget(sendButton);

    auto cancelButton = new OutlinedButton("Cancel", this);
    connect(cancelButton, &OutlinedButton::clicked, this, &DestinationDialog::reject);
    ui->horizontalLayout->addWidget(cancelButton);

    model->refresh();
}

DestinationDialog::~DestinationDialog()
{
    delete ui;
}

Host DestinationDialog::getSelectedHost() const
{
    QModelIndex currIndex = ui->listView->currentIndex();
    if (currIndex.isValid()) {
        return mModel->host(currIndex.row());
    }

    return Host();
}

QVector<Host> DestinationDialog::getSelectedHosts() const
{
    QVector<Host> hosts;
    QItemSelectionModel* selModel = ui->listView->selectionModel();
    if (selModel) {
        QModelIndexList selected = selModel->selectedIndexes();
        for (auto selectedIndex : selected) {
            if (selectedIndex.isValid()) {
                hosts.push_back(mModel->host(selectedIndex.row()));
            }
        }
    }

    return hosts;
}

void DestinationDialog::onSendClicked()
{
    QModelIndex currIndex = ui->listView->currentIndex();
    if (currIndex.isValid())
        accept();
    else
        QMessageBox::information(this, tr("Info"), tr("Please select receivers."));
}

void DestinationDialog::onRefreshClicked()
{
    mModel->refresh();
}
