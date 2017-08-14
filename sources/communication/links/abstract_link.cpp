#include "abstract_link.h"

// Qt
#include <QDebug>

using namespace comm;

AbstractLink::AbstractLink(QObject* parent):
    QObject(parent)
{}

int AbstractLink::takeBytesReceived()
{
    int value = m_bytesReceived;
    m_bytesReceived = 0;
    return value;
}

int AbstractLink::takeBytesSent()
{
    int value = m_bytesSent;
    m_bytesSent = 0;
    return value;
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

void AbstractLink::receiveData(const QByteArray& data)
{
    m_bytesReceived += data.size();
    emit dataReceived(data);
}
