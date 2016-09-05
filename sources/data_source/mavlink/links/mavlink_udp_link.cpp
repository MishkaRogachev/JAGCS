#include "mavlink_udp_link.h"

// Qt
#include <QUdpSocket>

using namespace data_source::mavlink;

UdpLink::UdpLink(int hostPort, const QHostAddress& address, int port,
                 QObject* parent):
    AbstractLink(parent),
    m_socket(new QUdpSocket(this)),
    m_hostPort(hostPort),
    m_address(address),
    m_port(port)
{
    QObject::connect(m_socket, &QUdpSocket::readyRead,
                     this, &UdpLink::readPendingDatagrams);
}

bool UdpLink::isUp() const
{
    return m_socket->state() == QAbstractSocket::BoundState;
}

void UdpLink::up()
{
    if (this->isUp()) return;

    if (!m_socket->bind(m_hostPort))
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

void UdpLink::sendData(const QByteArray& data)
{
    m_socket->writeDatagram(data, m_address, m_port);
}

void UdpLink::readPendingDatagrams()
{
    while (m_socket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_socket->pendingDatagramSize());
        m_socket->readDatagram(datagram.data(), datagram.size());

        this->resolveData(datagram);
    }
}
