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

using namespace shshare::ui;

DestinationDialog::DestinationDialog(HostList* model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceiverSelectorDialog)
{
    ui->setupUi(this);
    ui->SelectReceiverPage->SetModel(model);
    connect(ui->SelectReceiverPage, &SelectReceiverPage::OnClose, this, &DestinationDialog::reject);
    connect(ui->SelectReceiverPage, &SelectReceiverPage::OnSend, this, &DestinationDialog::accept);
    connect(ui->SelectReceiverPage, &SelectReceiverPage::OnAddReceiver, this, [this](){
        ui->stackedWidget->setCurrentWidget(ui->EnterIp);
    });
    connect(ui->EnterIp, &EnterIpPage::OnClose, this, [this](){
        ui->stackedWidget->setCurrentWidget(ui->SelectReceiverPage);
    });
    connect(ui->EnterIp, &EnterIpPage::OnConnect, this, [this](){
        ui->stackedWidget->setCurrentWidget(ui->SpinnerPage);
    });
    connect(ui->SpinnerPage, &SpinnerPage::OnClose, this, [this](){
        ui->stackedWidget->setCurrentWidget(ui->EnterIp);
    });
    connect(ui->ErrorPage, &ErrorPage::OnClose, this, [this](){
        ui->stackedWidget->setCurrentWidget(ui->EnterIp);
    });
}

DestinationDialog::~DestinationDialog()
{
    delete ui;
}

QVector<Host> DestinationDialog::getSelectedHosts() const
{
    return ui->SelectReceiverPage->GetSelectedHosts();
}
