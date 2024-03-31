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
#ifndef SELECTRECEIVERPAGE_H
#define SELECTRECEIVERPAGE_H

#include <QObject>
#include <QListView>
#include <QVBoxLayout>
#include <ui/widgets/page/Page.h>
#include <ui/models/HostList.h>

using namespace shshare::widgets::page;

namespace shshare::ui
{

class SelectReceiverPage : public Page
{
    Q_OBJECT;

public:
    SelectReceiverPage(QWidget *parent = nullptr);
    void SetModel(HostList* model);
    QVector<Host> GetSelectedHosts() const;

signals:
    void OnClose();
    void OnSend();

private slots:
    void onRefreshClicked();
    void onSendClicked();

private:
    void initLayout();
    void initTitle();
    void initReceiversList();
    void initFooter();

    HostList* m_model = nullptr;
    QVBoxLayout* m_layout = nullptr;
    QListView* m_receivers = nullptr;
};

}

#endif // SELECTRECEIVERPAGE_H
