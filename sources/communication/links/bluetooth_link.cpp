#include "bluetooth_link.h"

// Qt
#include <QBluetoothServiceDiscoveryAgent> // TODO: to service bluetooth service
#include <QBluetoothSocket>
#include <QDebug>

using namespace comm;

class BluetoothLink::Impl
{
public:
    QString address;

    QBluetoothServiceDiscoveryAgent* discovery;
    QBluetoothSocket* socket = nullptr;
};

BluetoothLink::BluetoothLink(const QString& address, QObject* parent):
    AbstractLink(parent),
    d(new Impl())
{
    d->address = address;

    d->discovery = new QBluetoothServiceDiscoveryAgent(this);
    QObject::connect(d->discovery, &QBluetoothServiceDiscoveryAgent::serviceDiscovered,
                     this, [this](const QBluetoothServiceInfo& info) {
        if (d->address == info.device().name()) d->socket->connectToService(info);
    });

    d->socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);

    connect(d->socket, &QBluetoothSocket::readyRead, this, &BluetoothLink::onReadyRead);
    connect(d->socket, &QBluetoothSocket::connected, this, [this]() { emit connectedChanged(true); });
    connect(d->socket, &QBluetoothSocket::disconnected, this, [this]() { emit connectedChanged(false); });

// TODO: AbstractSocketLink
//    connect(d->socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
//         [=](QAbstractSocket::SocketError socketError){
//    });
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
    if (d->discovery->isActive()) d->discovery->stop();
    d->discovery->start();
}

void BluetoothLink::disconnectLink()
{
    if (this->isConnected()) d->socket->disconnectFromService();

    if (d->discovery->isActive()) d->discovery->stop();
}

void BluetoothLink::setAddress(QString address)
{
    if (d->address == address) return;

    d->address = address;

    if (this->isConnected())
    {
        d->socket->disconnectFromService();
        if (d->discovery->isActive()) d->discovery->stop();
        d->discovery->start();
    }

    emit addressChanged(address);
}

bool BluetoothLink::sendDataImpl(const QByteArray& data)
{
    return d->socket->write(data) > 0;
}

void BluetoothLink::onReadyRead()
{
    while (d->socket->bytesAvailable()) this->receiveData(d->socket->readAll());
}
