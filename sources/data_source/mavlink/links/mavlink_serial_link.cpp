#include "mavlink_serial_link.h"

// Qt
#include <QSerialPort>

using namespace data_source::mavlink;

SerialLink::SerialLink(const QString& portName, qint32 baudRate,
                       QObject* parent):
    AbstractLink(parent),
    m_port(new QSerialPort(portName, this))
{
    m_port->setBaudRate(baudRate);

    connect(m_port, &QSerialPort::readyRead, this, &SerialLink::readSerialData);
}

bool SerialLink::isUp() const
{
    return m_port->isOpen();
}

void SerialLink::up()
{
    if (this->isUp()) return;

    if (!m_port->open(QIODevice::ReadWrite))
    {
        qWarning("Serial port connection error: '%s'!",
                 qPrintable(m_port->errorString()));

        m_port->close();
    }
    else
    {
        emit upChanged(true);
    }
}

void SerialLink::down()
{
    if (!this->isUp()) return;

    m_port->close();
    emit upChanged(false);
}

void SerialLink::sendData(const QByteArray& data)
{
    m_port->write(data.data(), data.size());
}

void SerialLink::readSerialData()
{
    this->resolveData(m_port->readAll());
}
