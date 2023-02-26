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
#include "TransferInfo.h"

ConnectionInfo::ConnectionInfo(Connection* owner, QObject *parent) :
    QObject(parent),
    m_State(ConnectionStateID::Idle),
    m_LastState(ConnectionStateID::Idle),
    m_Progress(0),
    m_DataSize(0),
    m_Owner(owner)
{
}

const std::string& ConnectionInfo::getPeerName() const
{
    return m_Peer.getName();
}

QString ConnectionInfo::getProgress() const
{
    return QString("%1 %").arg(m_Progress);
}

ConnectionStateID ConnectionInfo::getState() const
{
    return m_State;
}

qint64 ConnectionInfo::getDataSize() const
{
    return m_DataSize;
}

QString ConnectionInfo::getFilePath() const
{
    return m_FilePath;
}

Connection *ConnectionInfo::getOwner() const
{
    return m_Owner;
}

bool ConnectionInfo::canResume() const
{
    return m_State == ConnectionStateID::Paused;
}

bool ConnectionInfo::canPause() const
{
    return m_State == ConnectionStateID::Waiting ||
           m_State == ConnectionStateID::Transfering;
}

bool ConnectionInfo::canCancel() const
{
    return m_State == ConnectionStateID::Waiting ||
           m_State == ConnectionStateID::Transfering ||
           m_State == ConnectionStateID::Paused;
}

bool ConnectionInfo::canRemove() const
{
    return m_State == ConnectionStateID::Finish ||
           m_State == ConnectionStateID::Cancelled ||
           m_State == ConnectionStateID::Disconnected ||
           m_State == ConnectionStateID::Idle;
}

void ConnectionInfo::waiting()
{
    setState(ConnectionStateID::Waiting);
}

bool ConnectionInfo::resume()
{
    bool result = false;

    if (canResume()) {
        restoreLastState();
        result = true;
    }

    return result;
}

bool ConnectionInfo::pause()
{
    bool result = false;

    if (canPause()) {
        setState(ConnectionStateID::Paused);
        result = true;
    }

    return result;
}

bool ConnectionInfo::cancel()
{
    bool result = false;

    if (canCancel()) {
        setState(ConnectionStateID::Cancelled);
        setProgress(0);
        result = true;
    }

    return result;
}

void ConnectionInfo::disconnect(const QString& error)
{
    setState(ConnectionStateID::Disconnected);
    emit errorOcurred(error);
}

void ConnectionInfo::finish()
{
    setState(ConnectionStateID::Finish);
    emit done();
}

void ConnectionInfo::transfer()
{
    setState(ConnectionStateID::Transfering);
    emit fileOpened();
}

void ConnectionInfo::error(const QString &error)
{
    emit errorOcurred(error);
}

void ConnectionInfo::setPeer(const Host& peer)
{
    m_Peer = std::move(peer);
}

void ConnectionInfo::setState(ConnectionStateID state)
{
    if (state != m_State) {
        switch (m_State) {
        case ConnectionStateID::Idle:
            updateIdle(state);
            break;
        case ConnectionStateID::Waiting:
            updateWaiting(state);
            break;
        case ConnectionStateID::Transfering:
            updateTransfering(state);
            break;
        case ConnectionStateID::Paused:
            updatePaused(state);
            break;
        default:
            break;
        }
    }
}

void ConnectionInfo::setProgress(int newProgress)
{
    if (newProgress != m_Progress) {
        m_Progress = newProgress;
        emit progressChanged(m_Progress);
    }
}

void ConnectionInfo::setDataSize(qint64 size)
{
    m_DataSize = size;
}

void ConnectionInfo::setFilePath(const QString &fileName)
{
    m_FilePath = fileName;
}

void ConnectionInfo::restoreLastState()
{
    setState(m_LastState);
}

bool ConnectionInfo::isFinished() const
{
    return getState() == ConnectionStateID::Finish;
}

void ConnectionInfo::updateState(const ConnectionStateID &state)
{
    if (m_State != state) {
        m_LastState = m_State;
        m_State = state;
        emit stateChanged(m_State);
    }
}

void ConnectionInfo::updateIdle(const ConnectionStateID &state)
{
    if (state == ConnectionStateID::Waiting) {
        updateState(state);
    }
}

void ConnectionInfo::updateWaiting(const ConnectionStateID &state)
{
    if (state == ConnectionStateID::Transfering ||
        state == ConnectionStateID::Cancelled ||
        state == ConnectionStateID::Paused) {
        updateState(state);
    }
}

void ConnectionInfo::updateTransfering(const ConnectionStateID &state)
{
    if (state == ConnectionStateID::Disconnected ||
        state == ConnectionStateID::Finish ||
        state == ConnectionStateID::Cancelled ||
        state == ConnectionStateID::Paused) {
        updateState(state);
    }
}

void ConnectionInfo::updatePaused(const ConnectionStateID &state)
{
    switch(state) {
        case ConnectionStateID::Waiting:
        case ConnectionStateID::Transfering:
            updateState(m_LastState);
            break;
        case ConnectionStateID::Cancelled:
        case ConnectionStateID::Disconnected:
            updateState(state);
            break;
        default:
            break;
    }
}
