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
#ifndef SHSHARE_WIDGETS_IPVALIDATOR_H
#define SHSHARE_WIDGETS_IPVALIDATOR_H

#include <QValidator>

namespace shshare::widgets
{

class IpValidator : public QValidator
{
public:
    explicit IpValidator(QObject *parent = nullptr);
    QValidator::State validate(QString &, int &) const override;
};

}

#endif // SHSHARE_WIDGETS_IPVALIDATOR_H
