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
#include "IpValidator.h"

namespace shshare::widgets
{

IpValidator::IpValidator(QObject *parent)
    : QValidator{parent}
{}

QValidator::State IpValidator::validate(QString& value, int& position) const
{
    if (!value.isEmpty())
    {
        if (value.length() > 3)
        {
            return State::Invalid;
        }

        bool isNumber = false;
        auto number = value.toUInt(&isNumber);
        if (!isNumber || number > 255)
        {
            return State::Invalid;
        }
    }

    return State::Acceptable;
}

}
