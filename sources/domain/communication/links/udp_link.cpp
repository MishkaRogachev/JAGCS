#include "udp_link.h"

// Qt
#include <QUdpSocket>

using namespace domain;

UdpLink::UdpLink(int rxPort, const QString& address, int txPort,
                 QObject* parent):
    AbstractLink(parent),
    m_socket(new QUdpSocket(this)),
    m_rxPort(rxPort),
    m_address(address),
    m_txPort(txPort)
{
    QObject::connect(m_socket, &QUdpSocket::readyRead,
                     this, &UdpLink::readPendingDatagrams);
}

bool UdpLink::isUp() const
{
    return m_socket->state() == QAbstractSocket::BoundState;
}

int UdpLink::rxPort() const
{
    return m_rxPort;
}

QString UdpLink::address() const
{
    return m_address;
}

int UdpLink::txPort() const
{
    return m_txPort;
}

void UdpLink::up()
{
    if (this->isUp()) return;

    if (!m_socket->bind(m_rxPort))
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
    m_socket->writeDatagram(data, QHostAddress(m_address), m_txPort);
}

void UdpLink::setRxPort(int port)
{
    if (m_rxPort == port) return;

    m_rxPort = port;

    if (this->isUp())
    {
        this->down();
        this->up();
    }

    emit rxPortChanged(port);
}

void UdpLink::setAddress(const QString& address)
{
    if (m_address == address) return;

    m_address = address;
    emit addressChanged(address);
}

void UdpLink::setTxPort(int port)
{
    if (m_txPort == port) return;

    m_txPort = port;
    emit txPortChanged(port);
}

void UdpLink::readPendingDatagrams()
{
    while (m_socket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_socket->pendingDatagramSize());
        m_socket->readDatagram(datagram.data(), datagram.size());

        emit dataReceived(datagram);
    }
}
