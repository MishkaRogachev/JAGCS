#include "serial_device_service.h"

// Qt
#include <QTimerEvent>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>

// Internal
#include "serial_device_pool.h"

namespace
{
    const int interval = 500;
}

using namespace domain;

SerialDeviceService::SerialDeviceService(QObject* parent):
    QObject(parent),
    m_pool(new data_source::SerialDevicePool(this))
{
    m_timerId = this->startTimer(::interval);
    this->discoverDevices();
}

QList<qint32> SerialDeviceService::availableBaudRates()
{
    // return QSerialPortInfo::standardBaudRates(), if we need all
    return { QSerialPort::Baud9600,
                QSerialPort::Baud19200,
                QSerialPort::Baud38400,
                QSerialPort::Baud57600,
                QSerialPort::Baud115200 };
}

data_source::SerialDevicePool*SerialDeviceService::pool() const
{
    return m_pool;
}

void SerialDeviceService::discoverDevices()
{
    QStringList devices;
    for (const QSerialPortInfo& info: QSerialPortInfo::availablePorts())
    {
        if (info.description().isNull() || info.isBusy()) continue;
        devices.append(info.portName());
    }

    m_pool->setDiscoveredDevices(devices);
}

void SerialDeviceService::timerEvent(QTimerEvent* event)
{
    if (event->timerId() != m_timerId) return QObject::timerEvent(event);

    this->discoverDevices();
}
