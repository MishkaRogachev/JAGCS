#include "serial_ports_service.h"

// Qt
#include <QTimerEvent>
#include <QSerialPortInfo>

namespace
{
    const int interval = 500;
}

using namespace domain;

SerialPortService::SerialPortService(QObject* parent):
    QObject(parent)
{
    this->updateAvailablePorts(); // TODO: serialPorts pool
    m_timerId = this->startTimer(::interval);
}

QList<qint32> SerialPortService::availableBaudRates()
{
    // return QSerialPortInfo::standardBaudRates(), if we need all
    return { 9600, 19200, 38400, 57600, 115200};
}

QStringList SerialPortService::availablePorts() const
{
    return m_availablePorts;
}

void SerialPortService::updateAvailablePorts()
{
    QStringList availablePorts;
    for (const QSerialPortInfo& info: QSerialPortInfo::availablePorts())
    {
        availablePorts.append(info.portName());
    }

    if (m_availablePorts == availablePorts) return;

    m_availablePorts = availablePorts;
    emit availablePortsChanged(availablePorts);
}

void SerialPortService::timerEvent(QTimerEvent* event)
{
    if (event->timerId() != m_timerId) return QObject::timerEvent(event);

    this->updateAvailablePorts();
}
