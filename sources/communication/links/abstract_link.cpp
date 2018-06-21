#include "abstract_link.h"

// Qt
#include <QAbstractSocket>
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
    if (!this->sendDataImpl(data)) return;

    m_bytesSent += data.size();
    emit dataSent();
}

void AbstractLink::receiveData(const QByteArray& data)
{
    m_bytesReceived += data.size();
    emit dataReceived(data);
}

void AbstractLink::onSocketError(int error)
{
    switch (error)
    {
    case QAbstractSocket::ConnectionRefusedError:
        emit errored("The connection was refused by the peer (or timed out)");
        break;
    case QAbstractSocket::RemoteHostClosedError:
        emit errored("The remote host closed the connection");
        break;
    case QAbstractSocket::HostNotFoundError:
        emit errored("The host address was not found");
        break;
    case QAbstractSocket::SocketAccessError:
        emit errored("The socket operation failed because the application lacked the required privileges");
        break;
    case QAbstractSocket::SocketResourceError:
        emit errored("The local system ran out of resources (e.g., too many sockets)");
        break;
    case QAbstractSocket::SocketTimeoutError:
        emit errored("The socket operation timed out");
        break;
    case QAbstractSocket::DatagramTooLargeError:
        emit errored("The datagram was larger than the operating system's limit");
        break;
    case QAbstractSocket::NetworkError:
        emit errored("An error occurred with the network");
        break;
    case QAbstractSocket::AddressInUseError:
        emit errored("The address specified is already in use and was set to be exclusive");
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        emit errored("The address specified does not belong to the host");
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        emit errored("The requested socket operation is not supported by the local operating system");
        break;
    case QAbstractSocket::OperationError:
        emit errored("An operation was attempted while the socket was in a state that did not permit it");
        break;
    case QAbstractSocket::TemporaryError:
        emit errored("A temporary error occurred");
        break;
    default:
    case QAbstractSocket::UnknownSocketError:
        qDebug() << QAbstractSocket::SocketError(error);
        emit errored("An unidentified error occurred");
        break;
    }
}
