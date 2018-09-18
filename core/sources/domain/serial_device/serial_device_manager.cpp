#include "serial_device_manager.h"

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

SerialDeviceManager* SerialDeviceManager::lastCreatedManager = nullptr;

SerialDeviceManager::SerialDeviceManager(QObject* parent):
    QObject(parent)
{
    SerialDeviceManager::lastCreatedManager = this;

    m_timerId = this->startTimer(::interval);
    this->discoverDevices();
}

SerialDeviceManager::~SerialDeviceManager()
{
    if (SerialDeviceManager::lastCreatedManager == this)
    {
        SerialDeviceManager::lastCreatedManager = nullptr;
    }
}

SerialDeviceManager* SerialDeviceManager::instance()
{
    return SerialDeviceManager::lastCreatedManager;
}

QList<qint32> SerialDeviceManager::availableBaudRates()
{
    // return QSerialPortInfo::standardBaudRates(), if we need all
    return { QSerialPort::Baud9600,
                QSerialPort::Baud19200,
                QSerialPort::Baud38400,
                QSerialPort::Baud57600,
                QSerialPort::Baud115200 };
}

QStringList SerialDeviceManager::busyDevices() const
{
    return m_busyDevices;
}

QStringList SerialDeviceManager::availableDevices() const
{
    return m_availableDevices;
}

QStringList SerialDeviceManager::allDevices() const
{
    return m_busyDevices + m_availableDevices;
}

void SerialDeviceManager::discoverDevices()
{
    QStringList devices;
    for (const QSerialPortInfo& info: QSerialPortInfo::availablePorts())
    {
        if (info.description().isNull() || info.isBusy()) continue;
        devices.append(info.portName());
    }

    emit devicesDiscovered(devices);
}

void SerialDeviceManager::setBusyDevices(const QStringList& busyDevices)
{
    if (m_busyDevices == busyDevices) return;

    m_busyDevices = busyDevices;
    emit devicesChanged();
}

void SerialDeviceManager::setAvailableDevices(const QStringList& availableDevices)
{
    if (m_availableDevices == availableDevices) return;

    m_availableDevices = availableDevices;
    emit devicesChanged();
}

void SerialDeviceManager::timerEvent(QTimerEvent* event)
{
    if (event->timerId() != m_timerId) return QObject::timerEvent(event);

    this->discoverDevices();
}
