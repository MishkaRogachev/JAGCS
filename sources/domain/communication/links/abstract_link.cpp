#include "abstract_link.h"

// Qt
#include <QTimerEvent>
#include <QDebug>

namespace
{
    const int second = 1000;
}

using namespace domain;

AbstractLink::AbstractLink(QObject* parent):
    QObject(parent),
    m_bytesReceivedSec(0),
    m_bytesReceived(0),
    m_bytesSentSec(0),
    m_bytesSent(0)
{
    m_statisticsTimer = this->startTimer(::second);
}

int AbstractLink::bytesReceivedSec() const
{
    return m_bytesReceivedSec;
}

int AbstractLink::bytesSentSec() const
{
    return m_bytesSentSec;
}

void AbstractLink::sendData(const QByteArray& data)
{
    m_bytesSent += data.size();
    this->sendDataImpl(data);
}

void AbstractLink::timerEvent(QTimerEvent* event)
{
    if (event->timerId() != m_statisticsTimer) return;

    m_bytesReceivedSec = m_bytesReceived;
    m_bytesSentSec = m_bytesSent;
    m_bytesReceived = 0;
    m_bytesSent = 0;

    emit statisticsChanged();
}

void AbstractLink::receiveData(const QByteArray& data)
{
    m_bytesReceived += data.size();
    emit dataReceived(data);
}
