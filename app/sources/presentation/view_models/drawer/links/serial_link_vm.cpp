#include "serial_link_vm.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "serial_ports_service.h"
#include "communication_service.h"

using namespace presentation;

SerialLinkVm::SerialLinkVm(QObject* parent):
    LinkVm(parent),
    m_serialService(serviceRegistry->serialPortService())
{
    connect(this, &LinkVm::linkChanged, this, &SerialLinkVm::serialLinkChanged);
    connect(this, &LinkVm::linkChanged, this, &SerialLinkVm::availableDevicesChanged);
    connect(m_serialService, &domain::SerialPortService::availableDevicesChanged,
            this, &SerialLinkVm::availableDevicesChanged);
}

QVariantList SerialLinkVm::baudRates() const
{
    QVariantList baudRates;

    for (qint32 rate: m_serialService->availableBaudRates()) baudRates.append(rate);

    return baudRates;
}

int SerialLinkVm::baudRate() const
{
    return m_description ? m_description->parameter(dto::LinkDescription::BaudRate).toInt() : 0;
}

QStringList SerialLinkVm::availableDevices() const
{
    QStringList devices;
    devices.append(QString());
    devices.append(m_serialService->availableDevices());

    if (m_description)
    {
        QString device = m_description->parameter(dto::LinkDescription::Device).toString();
        if (!devices.contains(device)) devices.append(device);
    }

    return devices;
}

QString SerialLinkVm::device() const
{
    return m_description ? m_description->parameter(dto::LinkDescription::Device).toString() : QString();
}

void SerialLinkVm::setBaudRate(int baudRate)
{
    if (m_description.isNull() ||
        m_description->parameter(dto::LinkDescription::BaudRate) == baudRate) return;

    m_description->setParameter(dto::LinkDescription::BaudRate, baudRate);
    m_commService->save(m_description);
}

void SerialLinkVm::setDevice(const QString& device)
{
    if (m_description.isNull() ||
        m_description->parameter(dto::LinkDescription::Device) == device) return;

    m_description->setParameter(dto::LinkDescription::Device, device);
    m_commService->save(m_description);
}
