#include "bluetooth_link.h"

// Qt
#include <QtBluetooth/QBluetoothSocket>
#include <QDebug>

// TODO: QBluetoothDeviceDiscoveryAgent service

using namespace comm;

BluetoothLink::BluetoothLink(const QString& address, QObject* parent):
    AbstractLink(parent),
    m_address(address),
    m_socket(new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this))
{
    connect(m_socket, &QBluetoothSocket::readyRead, this, &BluetoothLink::onReadyRead);

    connect(m_socket, &QBluetoothSocket::connected, this, [this]() { emit connectedChanged(true); });
    connect(m_socket, &QBluetoothSocket::disconnected, this, [this]() { emit connectedChanged(false); });

// TODO: AbstractSocketLink
//    connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
//         [=](QAbstractSocket::SocketError socketError){
//    });
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
    if (this->isConnected()) return;

    m_socket->connectToService(QBluetoothAddress(m_address),
                               QBluetoothUuid(QBluetoothUuid::SerialPort));
}

void BluetoothLink::disconnectLink()
{
    if (!this->isConnected()) return;

    m_socket->disconnectFromService();
}

void BluetoothLink::setAddress(QString address)
{
    if (m_address == address) return;

    m_address = address;

    if (this->isConnected())
    {
        m_socket->disconnectFromService();
        m_socket->connectToService(QBluetoothAddress(m_address),
                                   QBluetoothUuid(QBluetoothUuid::SerialPort));
    }

    emit addressChanged(address);
}

bool BluetoothLink::sendDataImpl(const QByteArray& data)
{
    return m_socket->write(data) > 0;
}

void BluetoothLink::onReadyRead()
{
    while (m_socket->bytesAvailable()) this->receiveData(m_socket->readAll());
}
