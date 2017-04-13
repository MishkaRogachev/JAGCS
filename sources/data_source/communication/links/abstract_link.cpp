#include "abstract_link.h"

// Qt
#include <QTimerEvent>
#include <QDebug>

namespace
{
    const int second = 1000;
}

using namespace data_source;

AbstractLink::AbstractLink(QObject* parent):
    QObject(parent),
    m_bytesReceivedSec(0),
    m_bytesReceived(0),
    m_bytesSentSec(0),
    m_bytesSent(0),
    m_packetsReceived(0),
    m_packetsDrops(0)
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

int AbstractLink::packetsReceived() const
{
    return m_packetsReceived;
}

int AbstractLink::packetsDrops() const
{
    return m_packetsDrops;
}

void AbstractLink::setConnected(bool connected)
{
    connected ? this->connectLink() : this->disconnectLink();
}

void AbstractLink::sendData(const QByteArray& data)
{
    m_bytesSent += data.size();
    this->sendDataImpl(data);
}

void AbstractLink::setPacketsReceived(int packetsReceived)
{
    if (m_packetsReceived == packetsReceived) return;

    m_packetsReceived = packetsReceived;
    emit packetsReceivedChanged(packetsReceived);
}

void AbstractLink::setPacketsDrops(int packetsDrops)
{
    if (m_packetsDrops == packetsDrops) return;

    m_packetsDrops = packetsDrops;
    emit packetsDropsChanged(packetsDrops);
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
