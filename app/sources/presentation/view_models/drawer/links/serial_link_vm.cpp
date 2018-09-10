#include "serial_link_vm.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "serial_ports_service.h"

using namespace presentation;

SerialLinkVm::SerialLinkVm(QObject* parent):
    LinkVm(parent),
    m_serialService(serviceRegistry->serialPortService())
{
    connect(m_serialService, &domain::SerialPortService::availableDevicesChanged,
            this, &SerialLinkVm::availableDevicesChanged);
}

QVariantList SerialLinkVm::baudRates() const
{
    QVariantList baudRates;

    for (qint32 rate: m_serialService->availableBaudRates()) baudRates.append(rate);

    return baudRates;
}

QStringList SerialLinkVm::availableDevices() const
{
    QStringList devices;
    devices.append(QString());

    for (const QString& device: m_serialService->availableDevices())
    {
        devices.append(device);
    }

    if (m_description)
    {
        QString device = m_description->parameter(dto::LinkDescription::Device).toString();
        if (!devices.contains(device)) devices.append(device);
    }

    return devices;
}
