#include "serial_ports_service.h"

// Qt
#include <QTimerEvent>
#include <QSerialPortInfo>
#include <QSerialPort>

namespace
{
    const int interval = 500;
}

using namespace domain;

class SerialPortService::Impl
{
public:
    int timerId;
    QStringList availablePorts;
};

SerialPortService::SerialPortService(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    this->updateAvailablePorts(); // TODO: serialPorts pool
    d->timerId = this->startTimer(::interval);
}

SerialPortService::~SerialPortService()
{}

QList<qint32> SerialPortService::availableBaudRates()
{
    // return QSerialPortInfo::standardBaudRates(), if we need all
    return { QSerialPort::Baud9600,
             QSerialPort::Baud19200,
             QSerialPort::Baud38400,
             QSerialPort::Baud57600,
             QSerialPort::Baud115200 };
}

QStringList SerialPortService::availablePorts() const
{
    return d->availablePorts;
}

void SerialPortService::updateAvailablePorts()
{
    QStringList availablePorts;
    for (const QSerialPortInfo& info: QSerialPortInfo::availablePorts())
    {
        availablePorts.append(info.portName());
    }

    if (d->availablePorts == availablePorts) return;

    d->availablePorts = availablePorts;
    emit availablePortsChanged(availablePorts);
}

void SerialPortService::timerEvent(QTimerEvent* event)
{
    if (event->timerId() != d->timerId) return QObject::timerEvent(event);

    this->updateAvailablePorts();
}
