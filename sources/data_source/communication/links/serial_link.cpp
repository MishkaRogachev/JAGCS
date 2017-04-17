#include "serial_link.h"

// Qt
#include <QSerialPort>
#include <QDebug>

using namespace data_source;

SerialLink::SerialLink(const QString& portName, qint32 baudRate,
                       QObject* parent):
    AbstractLink(parent),
    m_port(new QSerialPort(portName, this))
{
    m_port->setBaudRate(baudRate);

    connect(m_port, &QSerialPort::readyRead, this, &SerialLink::readSerialData);
}

bool SerialLink::isConnected() const
{
    return m_port->isOpen();
}

QString SerialLink::device() const
{
    return m_port->portName();
}

qint32 SerialLink::baudRate() const
{
    return m_port->baudRate();
}

void SerialLink::connectLink()
{
    if (this->isConnected()) return;

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

    AbstractLink::connectLink();
}

void SerialLink::disconnectLink()
{
    if (!this->isConnected()) return;

    m_port->close();
    emit upChanged(false);
    AbstractLink::disconnectLink();
}

void SerialLink::sendDataImpl(const QByteArray& data)
{
    m_port->write(data.data(), data.size());
}

void SerialLink::setDevice(QString device)
{
    if (m_port->portName() == device) return;

    m_port->setPortName(device);
    emit deviceChanged(m_port->portName());
}

void SerialLink::setBaudRate(qint32 baudRate)
{
    if (m_port->baudRate() == baudRate) return;

    m_port->setBaudRate(baudRate);
    emit baudRateChanged(m_port->baudRate());
}

void SerialLink::readSerialData()
{
    this->receiveData(m_port->readAll());
}
