#include "mavlink_serial_link.h"

// Qt
#include <QSerialPort>

using namespace data_source::mavlink;

SerialLink::SerialLink(const QString& portName, QObject* parent):
    AbstractLink(parent),
    m_port(new QSerialPort(portName, this))
{
    connect(m_port, &QSerialPort::readyRead, this, &SerialLink::readSerialData);
}

void SerialLink::sendData(const QByteArray& data)
{
    m_port->write(data.data(), data.size());
}

void SerialLink::readSerialData()
{
    this->resolveData(m_port->readAll());
}
