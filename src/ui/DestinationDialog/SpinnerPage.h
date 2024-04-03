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
#ifndef SHSHARE_UI_SPINNERPAGE_H
#define SHSHARE_UI_SPINNERPAGE_H

#include <QWidget>
#include <QVBoxLayout>

namespace shshare::ui
{

class SpinnerPage : public QWidget
{
    Q_OBJECT
public:
    explicit SpinnerPage(QWidget *parent = nullptr);

signals:
    void OnClose();

private:
    void initLayout();
    void initHeader();
    void initSpinner();
    void initFotter();

    QVBoxLayout* m_layout = nullptr;
};

}

#endif // SHSHARE_UI_SPINNERPAGE_H
