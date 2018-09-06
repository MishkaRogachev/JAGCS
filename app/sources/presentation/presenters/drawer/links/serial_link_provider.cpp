#include "serial_link_provider.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "link_statistics.h"

#include "service_registry.h"
#include "serial_ports_service.h"

using namespace presentation;

SerialLinkProvider::SerialLinkProvider(QObject* parent):
    LinkProvider(parent),
    m_serialService(serviceRegistry->serialPortService())
{
    connect(m_serialService, &domain::SerialPortService::availableDevicesChanged,
            this, &SerialLinkProvider::availableDevicesChanged);
}

QVariantList SerialLinkProvider::baudRates() const
{
    QVariantList baudRates;

    for (qint32 rate: m_serialService->availableBaudRates()) baudRates.append(rate);

    return baudRates;
}

QStringList SerialLinkProvider::availableDevices() const
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
