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
#include <QMovie>
#include "SpinnerPage.h"
#include "ui/widgets/OutlinedButton.h"

using namespace shshare::widgets;
namespace shshare::ui
{

SpinnerPage::SpinnerPage(QWidget *parent)
    : QWidget{parent}
{
    initLayout();
    m_layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    initHeader();
    initSpinner();
    m_layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    initFotter();
}

void SpinnerPage::initLayout()
{
    m_layout = new QVBoxLayout(this);
}

void SpinnerPage::initHeader()
{
    auto text = new QLabel("Connecting...",this);
    text->setStyleSheet(QString::fromUtf8(
        "font-family: Roboto;"
        "color: #FFFFFF;"
        "font-size: 24px;"
    ));
    text->setAlignment(Qt::AlignCenter);
    m_layout->addWidget(text);
}

void SpinnerPage::initSpinner()
{
    auto movie = new QMovie(":/img/spinner.gif");
    movie->setScaledSize(QSize(100,70));
    auto spinner = new QLabel(this);
    spinner->setMovie(movie);
    spinner->setAlignment(Qt::AlignCenter);
    m_layout->addWidget(spinner);
    movie->start();
}

void SpinnerPage::initFotter()
{
    auto footer = new QHBoxLayout();
    footer->setSpacing(20);
    footer->setContentsMargins(100, 0, 100, 0);

    auto cancelButton = new OutlinedButton("Cancel", this);
    connect(cancelButton, &OutlinedButton::clicked, this, [this](){
        emit OnClose();
    });
    footer->addWidget(cancelButton);
    m_layout->addLayout(footer);
}

}
