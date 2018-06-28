#include "tcp_link.h"

// Qt
#include <QTcpSocket>

using namespace comm;

TcpLink::TcpLink(const Endpoint& endpoint, QObject* parent):
    AbstractLink(parent),
    m_socket(new QTcpSocket(this)),
    m_endpoint(endpoint)
{
    connect(m_socket, &QTcpSocket::readyRead, this, &TcpLink::onReadyRead);
    // TODO: C++14 QOverload<QTcpSocket::SocketError>::of(&QTcpSocket::error),
    connect(m_socket, static_cast<void (QTcpSocket::*)
            (QTcpSocket::SocketError)>(&QTcpSocket::error),
            this, &AbstractLink::onSocketError);
}

bool TcpLink::isConnected() const
{
    return m_socket->state() == QTcpSocket::ConnectedState;
}

Endpoint TcpLink::endpoint() const
{
    return m_endpoint;
}

void TcpLink::connectLink()
{
    if (this->isConnected() || !m_endpoint.isValid()) return;

    m_socket->connectToHost(m_endpoint.address(), endpoint().port());
    emit connectedChanged(m_socket->waitForConnected());
}

void TcpLink::disconnectLink()
{
    if (!this->isConnected()) return;

    m_socket->disconnectFromHost();
    emit connectedChanged(!m_socket->waitForDisconnected());
}

void TcpLink::setEndpoint(const Endpoint& endpoint)
{
    if (m_endpoint == endpoint) return;

    m_endpoint = endpoint;

    if (this->isConnected())
    {
        this->disconnectLink();
        this->connectLink();
    }

    emit endpointChanged(endpoint);
}

bool TcpLink::sendDataImpl(const QByteArray& data)
{
    return m_socket->write(data) > 0;
}

void TcpLink::onReadyRead()
{
    while (m_socket->bytesAvailable()) this->receiveData(m_socket->readAll());
}
