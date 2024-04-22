/*
 * SHShare - LAN file transfer application.
 * Copyright (C) 2024 Hadzhilov Serhii
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QLabel>
#include <QListView>
#include <QAbstractItemView>
#include <QMessageBox>
#include "SelectReceiverPage.h"
#include "ui/widgets/IconButton.h"
#include "ui/widgets/FilledButton.h"
#include "ui/widgets/OutlinedButton.h"

using namespace shshare::widgets;
namespace shshare::ui
{

SelectReceiverPage::SelectReceiverPage(QWidget *parent) :
    Page(parent)
{
    initLayout();
    initTitle();
    initReceiversList();
    initFooter();
}

void SelectReceiverPage::SetModel(HostList* model)
{
    if (m_model == model)
    {
        return;
    }

    if (m_receivers) {
        m_receivers->setModel(model);
    }

    m_model = model;
    m_model->refresh();
}

QVector<Host> SelectReceiverPage::GetSelectedHosts() const
{
    QVector<Host> hosts;

    QItemSelectionModel* selModel = m_receivers->selectionModel();
    if (selModel) {
        QModelIndexList selected = selModel->selectedIndexes();
        for (auto selectedIndex : selected) {
            if (selectedIndex.isValid()) {
                hosts.push_back(m_model->GetHost(selectedIndex.row()));
            }
        }
    }

    return hosts;
}

void SelectReceiverPage::onRefreshClicked()
{
    if (m_model)
    {
        m_model->refresh();
    }
}

void SelectReceiverPage::onSendClicked()
{
    QModelIndex currIndex = m_receivers->currentIndex();
    if (currIndex.isValid())
        emit OnSend();
    else
        QMessageBox::information(this, tr("Info"), tr("Please select receivers."));
}

void SelectReceiverPage::initLayout()
{
    this->m_layout = new QVBoxLayout(this);
    m_layout->setSpacing(20);
}

void SelectReceiverPage::initTitle()
{
    auto title = new QHBoxLayout();

    auto text = new QLabel("Select receivers", this);
    text->setStyleSheet(QString::fromUtf8(
        "font-family: Roboto;"
        "font-size: 24px;"
    ));
    title->addWidget(text);
    title->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    auto addReceiver = new IconButton(0xe05c);
    connect(addReceiver, &IconButton::clicked, this, [this](){emit OnAddReceiver();});
    title->addWidget(addReceiver);

    auto iconRefresh = new IconButton(0xe627);
    connect(iconRefresh, &IconButton::clicked, this, &SelectReceiverPage::onRefreshClicked);
    title->addWidget(iconRefresh);

    m_layout->addLayout(title);
}

void SelectReceiverPage::initReceiversList()
{
    m_receivers = new QListView(this);
    m_receivers->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_receivers->setCurrentIndex(QModelIndex());
    m_layout->addWidget(m_receivers);
}

void SelectReceiverPage::initFooter()
{
    auto footer = new QHBoxLayout();
    footer->setSpacing(20);
    footer->setContentsMargins(40, 0, 40, 0);
    footer->addItem(new QSpacerItem(342, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    auto sendButton = new FilledButton("Send", this);
    connect(sendButton, &FilledButton::clicked, this, &SelectReceiverPage::onSendClicked);
    footer->addWidget(sendButton);

    auto cancelButton = new OutlinedButton("Cancel", this);
    connect(cancelButton, &OutlinedButton::clicked, this, [this](){emit OnClose();});
    footer->addWidget(cancelButton);

    m_layout->addLayout(footer);
}

}
