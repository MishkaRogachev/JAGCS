#include "udp_link.h"

// Qt
#include <QUdpSocket>

using namespace comm;

UdpLink::UdpLink(quint16 port, QObject* parent):
    AbstractLink(parent),
    m_socket(new QUdpSocket(this)),
    m_port(port),
    m_autoResponse(true)
{
    QObject::connect(m_socket, &QUdpSocket::readyRead, this, &UdpLink::onReadyRead);
    // TODO: QOverload<QUdpSocket::SocketError>::of(&QUdpSocket::error),
    connect(m_socket, static_cast<void (QUdpSocket::*)
            (QUdpSocket::SocketError)>(&QUdpSocket::error),
            this, &AbstractLink::onSocketError);
}

bool UdpLink::isConnected() const
{
    return m_socket->state() == QAbstractSocket::BoundState;
}

quint16 UdpLink::port() const
{
    return m_port;
}

EndpointList UdpLink::endpoints() const
{
    return m_endpoints;
}

bool UdpLink::autoResponse() const
{
    return m_autoResponse;
}

int UdpLink::count() const
{
    return m_endpoints.count();
}

Endpoint UdpLink::endpoint(int index) const
{
    return m_endpoints.at(index);
}

void UdpLink::connectLink()
{
    if (this->isConnected() || m_port == 0) return;

    if (!m_socket->bind(m_port))
    {
        m_socket->close();
    }
    else
    {
        emit connectedChanged(true);
    }
}

void UdpLink::disconnectLink()
{
    if (!this->isConnected()) return;

    m_socket->close();
    emit connectedChanged(false);
}

void UdpLink::setPort(quint16 port)
{
    if (m_port == port) return;

    m_port = port;

    if (this->isConnected())
    {
        this->disconnectLink();
        this->connectLink();
    }

    emit portChanged(port);
}

void UdpLink::addEndpoint(const Endpoint& endpoint)
{
    m_endpoints.append(endpoint);
    emit endpointsChanged(m_endpoints);
}

void UdpLink::removeEndpoint(const Endpoint& endpoint)
{
    m_endpoints.removeOne(endpoint);
    emit endpointsChanged(m_endpoints);
}

void UdpLink::clearEndpoints()
{
    m_endpoints.clear();
    emit endpointsChanged(m_endpoints);
}

void UdpLink::setAutoResponse(bool autoResponse)
{
    if (m_autoResponse == autoResponse) return;

    m_autoResponse = autoResponse;
    emit autoResponseChanged(autoResponse);
}

bool UdpLink::sendDataImpl(const QByteArray& data)
{
    bool ok = false;
    for (const Endpoint& endpoint: m_endpoints)
    {
         if (m_socket->writeDatagram(data, endpoint.address(), endpoint.port()) > 0) ok = true;
    }
    return ok;
}

void UdpLink::onReadyRead()
{
    while (m_socket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_socket->pendingDatagramSize());

        QHostAddress address;
        quint16 port;
        m_socket->readDatagram(datagram.data(), datagram.size(), &address, &port);

        Endpoint endpoint(address, port);
        if (m_autoResponse && !m_endpoints.contains(endpoint))
        {
            this->addEndpoint(endpoint);
        }

        this->receiveData(datagram);
    }
}
