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
#include "BroadcastInterval.h"
#include "settings/Settings.h"

namespace shshare::widgets::settings {

BroadcastInterval::BroadcastInterval(QWidget *parent)
    : Interval{"Broadcast interval", 0, parent}
{
    setValue(::shshare::Settings::instance().getBroadcastInterval());
    connect(this, &BroadcastInterval::onChanged, this, [this](int value){
        ::shshare::Settings::instance().setBroadcastInterval(value);
    });
}

} //namespace shshare::widgets::settings
