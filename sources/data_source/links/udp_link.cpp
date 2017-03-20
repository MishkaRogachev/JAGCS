#include "udp_link.h"

// Qt
#include <QUdpSocket>

using namespace data_source;

UdpLink::UdpLink(int port, QObject* parent):
    AbstractLink(parent),
    m_socket(new QUdpSocket(this)),
    m_port(port),
    m_autoResponse(true)
{
    QObject::connect(m_socket, &QUdpSocket::readyRead,
                     this, &UdpLink::readPendingDatagrams);
}

bool UdpLink::isUp() const
{
    return m_socket->state() == QAbstractSocket::BoundState;
}

int UdpLink::port() const
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

void UdpLink::up()
{
    if (this->isUp()) return;

    if (!m_socket->bind(m_port))
    {
        qWarning("UDP connection error: '%s'!",
                 qPrintable(m_socket->errorString()));

        m_socket->close();
    }
    else
    {
        emit upChanged(true);
    }
}

void UdpLink::down()
{
    if (!this->isUp()) return;

    m_socket->close();
    emit upChanged(false);
}

void UdpLink::sendDataImpl(const QByteArray& data)
{
    for (const Endpoint& endpoint: m_endpoints)
        m_socket->writeDatagram(data, endpoint.address(), endpoint.port());
}

void UdpLink::setPort(int port)
{
    if (m_port == port) return;

    m_port = port;

    if (this->isUp())
    {
        this->down();
        this->up();
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

void UdpLink::setAutoResponse(bool autoResponse)
{
    if (m_autoResponse == autoResponse) return;

    m_autoResponse = autoResponse;
    emit autoResponseChanged(autoResponse);
}

void UdpLink::readPendingDatagrams()
{
    while (m_socket->hasPendingDatagrams())
    {
        QByteArray datagram;
        Endpoint endpoint;
        datagram.resize(m_socket->pendingDatagramSize());
        m_socket->readDatagram(datagram.data(), datagram.size(),
                               &endpoint.rAddress(), &endpoint.rPort());

        if (m_autoResponse && !m_endpoints.contains(endpoint))
            this->addEndpoint(endpoint);

        this->receiveData(datagram);
    }
}
