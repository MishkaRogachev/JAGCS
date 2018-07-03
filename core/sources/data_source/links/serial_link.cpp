#include "serial_link.h"

// Qt
#include <QSerialPort>
#include <QDebug>

using namespace comm;

SerialLink::SerialLink(const QString& portName, qint32 baudRate,
                       QObject* parent):
    AbstractLink(parent),
    m_port(new QSerialPort(portName, this))
{
    m_port->setBaudRate(baudRate);

    connect(m_port, &QSerialPort::readyRead, this, &SerialLink::readSerialData);
    connect(m_port, static_cast<void(QSerialPort::*)
            (QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &SerialLink::onError);
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
    if (this->isConnected() || m_port->portName().isEmpty()) return;

    if (m_port->open(QIODevice::ReadWrite)) emit connectedChanged(true);
}

void SerialLink::disconnectLink()
{
    if (!this->isConnected()) return;

    m_port->close();
    emit connectedChanged(false);
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

bool SerialLink::sendDataImpl(const QByteArray& data)
{
    if (m_port->isWritable()) return m_port->write(data.data(), data.size()) > 0;

    return false;
}

void SerialLink::readSerialData()
{
    if (m_port->isReadable()) this->receiveData(m_port->readAll());
}

void SerialLink::onError(int error)
{
    switch (error)
    {
    case QSerialPort::NoError:
        break;
    case QSerialPort::DeviceNotFoundError:
        emit errored(tr("Attempting to open an non-existing device %1").arg(m_port->portName()));
        break;
    case QSerialPort::PermissionError:
        emit errored(tr("Attempting to open an already opened device %1 or a user not having enough"
                        " permission to open").arg(m_port->portName()));
        break;
    case QSerialPort::OpenError:
        emit errored(tr("Attempting to open an already opened device in this object"));
        break;
    case QSerialPort::NotOpenError:
        emit errored(tr("Operation is executed that can only be successfully performed "
                        "if the device is open"));
        break;
    case QSerialPort::WriteError:
        emit errored(tr("An I/O error occurred while writing the data"));
        break;
    case QSerialPort::ReadError:
        emit errored(tr("An I/O error occurred while reading the data"));
        break;
    case QSerialPort::ResourceError:
        emit errored(tr("An I/O error occurred when a resource becomes unavailable"));
        m_port->close();
        emit connectedChanged(false);
        break;
    case QSerialPort::UnsupportedOperationError:
        emit errored(tr("The requested device operation is not supported or prohibited "
                        "by the operating system"));
        break;
    case QSerialPort::TimeoutError:
        emit errored(tr("A timeout error occurred"));
        break;
    default:
    case QSerialPort::UnknownError:
        emit errored(tr("An unidentified error occurred"));
        qDebug() << error;
        break;
    }
}
