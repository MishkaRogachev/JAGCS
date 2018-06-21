#include "bluetooth_link.h"

// Qt
#include <QBluetoothSocket>
#include <QDebug>

using namespace comm;

class BluetoothLink::Impl
{
public:
    QString address;

    QBluetoothSocket* socket = nullptr;
};

BluetoothLink::BluetoothLink(const QString& address, QObject* parent):
    AbstractLink(parent),
    d(new Impl())
{
    d->address = address;

    d->socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);

    connect(d->socket, &QBluetoothSocket::readyRead, this, &BluetoothLink::onReadyRead);
    connect(d->socket, &QBluetoothSocket::connected, this, [this]() { emit connectedChanged(true); });
    connect(d->socket, &QBluetoothSocket::disconnected, this, [this]() { emit connectedChanged(false); });
    connect(d->socket, QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error),
            [this](QBluetoothSocket::SocketError error) {
        switch (error) {
        case QBluetoothSocket::HostNotFoundError:
            emit errored("Could not find the remote host");
            break;
        case QBluetoothSocket::ServiceNotFoundError:
            emit errored("Could not find the service UUID on remote host");
            break;
        case QBluetoothSocket::NetworkError:
            emit errored("Attempt to read or write from socket returned an error");
            break;
        case QBluetoothSocket::UnsupportedProtocolError:
            emit errored("The Protocol is not supported on this platform");
            break;
        case QBluetoothSocket::OperationError:
            emit errored("An operation was attempted while the socket was in a state that did not permit it");
            break;
// Qt 5.10
//        case QBluetoothSocket::RemoteHostClosedError:
//            emit errored("The remote host closed the connection");
//            break;
        default:
        case QBluetoothSocket::UnknownSocketError:
            emit errored("An unknown error has occurred");
            break;
        }
    });
}

BluetoothLink::~BluetoothLink()
{}

bool BluetoothLink::isConnected() const
{
    return d->socket->state() == QBluetoothSocket::ConnectedState;
}

QString BluetoothLink::address() const
{
    return d->address;
}

void BluetoothLink::connectLink()
{
    if (d->socket->state() != QBluetoothSocket::UnconnectedState) return;

    d->socket->connectToService(QBluetoothAddress(d->address),
                                QBluetoothUuid(QBluetoothUuid::SerialPort));
}

void BluetoothLink::disconnectLink()
{
    if (this->isConnected()) d->socket->disconnectFromService();
}

void BluetoothLink::setAddress(QString address)
{
    if (d->address == address) return;

    d->address = address;

    if (this->isConnected())
    {
        d->socket->disconnectFromService();
        this->connectLink();
    }

    emit addressChanged(address);
}

bool BluetoothLink::sendDataImpl(const QByteArray& data)
{
    if (d->socket->isWritable()) return d->socket->write(data) > 0;

    return false;
}

void BluetoothLink::onReadyRead()
{
    while (d->socket->bytesAvailable()) this->receiveData(d->socket->readAll());
}
