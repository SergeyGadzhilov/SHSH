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
#ifndef HOST_H
#define HOST_H

#include <string>
#include <QtNetwork/QHostAddress>

class Host
{
public:
    Host() = default;
    Host(const std::string& id,
         const std::string& name,
         const std::string& osName,
         const QHostAddress &addr);

    const std::string& getId() const;
    const std::string& getName() const;
    const std::string& getOSName() const;
    const QHostAddress& getAddress() const;

    void setId(const std::string& id);
    void setName(const std::string& name);
    void setOSName(const std::string& osName);
    void setAddress(const QHostAddress& address);

    bool isValid() const;

    bool operator==(const Host& other) const;
    bool operator!=(const Host& other) const;

private:
    std::string m_Id;
    std::string m_Name;
    std::string m_OSName;
    QHostAddress m_Address;
};

#endif // HOST_H
