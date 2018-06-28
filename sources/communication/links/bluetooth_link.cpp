#include "bluetooth_link.h"

// Qt
#include <QBluetoothSocket>
#include <QDebug>

using namespace comm;

BluetoothLink::BluetoothLink(const QString& address, QObject* parent):
    AbstractLink(parent),
    m_address(address),
    m_socket(new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this))
{
    connect(m_socket, &QBluetoothSocket::readyRead, this, &BluetoothLink::onReadyRead);
    connect(m_socket, &QBluetoothSocket::connected, this, [this]() { emit connectedChanged(true); });
    connect(m_socket, &QBluetoothSocket::disconnected, this, [this]() { emit connectedChanged(false); });
    // TODO: C++14 QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error)
    connect(m_socket, static_cast<void (QBluetoothSocket::*)
            (QBluetoothSocket::SocketError)>(&QBluetoothSocket::error),
            this, &BluetoothLink::onError);
}

bool BluetoothLink::isConnected() const
{
    return m_socket->state() == QBluetoothSocket::ConnectedState;
}

QString BluetoothLink::address() const
{
    return m_address;
}

void BluetoothLink::connectLink()
{
    if (m_socket->state() != QBluetoothSocket::UnconnectedState || m_address.isEmpty()) return;

    m_socket->connectToService(QBluetoothAddress(m_address), QBluetoothUuid::SerialPort);
}

void BluetoothLink::disconnectLink()
{
    if (this->isConnected()) m_socket->disconnectFromService();
}

void BluetoothLink::setAddress(const QString& address)
{
    if (m_address == address) return;

    m_address = address;

    if (this->isConnected())
    {
        m_socket->disconnectFromService();
        this->connectLink();
    }

    emit addressChanged(address);
}

bool BluetoothLink::sendDataImpl(const QByteArray& data)
{
    if (m_socket->isWritable()) return m_socket->write(data) > 0;

    return false;
}

void BluetoothLink::onReadyRead()
{
    if (!m_socket->isReadable()) return;

    while (m_socket->bytesAvailable()) this->receiveData(m_socket->readAll());
}

void BluetoothLink::onError(int error)
{
    switch (error)
    {
    case QBluetoothSocket::HostNotFoundError:
        emit errored(tr("Could not find the remote host"));
        break;
    case QBluetoothSocket::ServiceNotFoundError:
        emit errored(tr("Could not find the service UUID(%1) on remote host").arg(m_address));
        break;
    case QBluetoothSocket::NetworkError:
        emit errored(tr("Attempt to read or write from socket returned an error"));
        break;
    case QBluetoothSocket::UnsupportedProtocolError:
        emit errored(tr("The Protocol is not supported on this platform"));
        break;
    case QBluetoothSocket::OperationError:
        emit errored(tr("An operation was attempted while the socket "
                        "was in a state that did not permit it"));
        break;
// Qt 5.10
//        case QBluetoothSocket::RemoteHostClosedError:
//            emit errored(tr("The remote host closed the connection"));
//            break;
    default:
    case QBluetoothSocket::UnknownSocketError:
        qDebug() << QBluetoothSocket::SocketError(error);
        emit errored(tr("An unknown error has occurred"));
        break;
    }
}
