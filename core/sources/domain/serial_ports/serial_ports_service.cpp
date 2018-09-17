#include "serial_ports_service.h"

// Qt
#include <QTimerEvent>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>

namespace
{
    const int interval = 500;
}

using namespace domain;

class SerialPortService::Impl
{
public:
    int timerId;
    QStringList devices;
    QStringList busyDevices;
};

SerialPortService::SerialPortService(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    this->updateDevices();
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

QStringList SerialPortService::devices() const
{
    return d->devices;
}

QStringList SerialPortService::busyDevices() const
{
    return d->busyDevices;
}

QStringList SerialPortService::availableDevices() const
{
    QStringList availableDevices;

    for (const QString& device: d->devices)
    {
        if (d->busyDevices.contains(device)) continue;

        availableDevices.append(device);
    }

    return availableDevices;
}

void SerialPortService::updateDevices()
{
    QStringList devices;
    for (const QSerialPortInfo& info: QSerialPortInfo::availablePorts())
    {
        if (info.description().isNull() || info.isBusy()) continue;
        devices.append(info.portName());
    }

    if (d->devices == devices) return;

    d->devices = devices;

    emit devicesChanged();
    emit availableDevicesChanged();
}

void SerialPortService::holdDevice(const QString& port)
{
    if (d->busyDevices.contains(port)) return;

    d->busyDevices.append(port);
    emit availableDevicesChanged();
}

void SerialPortService::releaseDevice(const QString& port)
{
    if (!d->busyDevices.contains(port)) return;

    d->busyDevices.removeOne(port);
    emit availableDevicesChanged();
}

void SerialPortService::timerEvent(QTimerEvent* event)
{
    if (event->timerId() != d->timerId) return QObject::timerEvent(event);

    this->updateDevices();
}
