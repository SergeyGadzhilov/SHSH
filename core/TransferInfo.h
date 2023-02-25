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
#ifndef TRANSFERINFO_H
#define TRANSFERINFO_H

#include <QObject>
#include "Host.h"

enum class ConnectionStateID {
    Idle,
    Waiting,
    Disconnected,
    Paused,
    Cancelled,
    Transfering,
    Finish
};

class Connection;
class ConnectionInfo : public QObject
{
    Q_OBJECT

public:
    explicit ConnectionInfo(Connection* owner, QObject *parent = nullptr);

    const std::string& getPeerName() const;
    QString getProgress() const;
    ConnectionStateID getState() const;
    qint64 getDataSize() const;
    QString getFilePath() const;
    Connection* getOwner() const;

    bool canResume() const;
    bool canPause() const;
    bool canCancel() const;
    bool canRemove() const;

    void waiting();
    bool resume();
    bool pause();
    bool cancel();
    void disconnect(const QString& error);
    void finish();
    void transfer();
    void error(const QString& error);

    void setPeer(const Host& peer);
    void setState(ConnectionStateID state);
    void setProgress(int progress);
    void setDataSize(qint64 size);
    void setFilePath(const QString& fileName);
    void restoreLastState();

    bool isFinished() const;

signals:
    void done();
    void errorOcurred(const QString& errStr);
    void progressChanged(int progress);
    void fileOpened();
    void stateChanged(ConnectionStateID state);

private:
    void updateState(const ConnectionStateID& state);
    void updateIdle(const ConnectionStateID& state);
    void updateWaiting(const ConnectionStateID& state);
    void updateTransfering(const ConnectionStateID& state);
    void updatePaused(const ConnectionStateID& state);

    Host m_Peer;
    ConnectionStateID m_State;
    ConnectionStateID m_LastState;

    int m_Progress;
    qint64 m_DataSize;
    QString m_FilePath;

    Connection* m_Owner;
};

#endif // TRANSFERINFO_H
