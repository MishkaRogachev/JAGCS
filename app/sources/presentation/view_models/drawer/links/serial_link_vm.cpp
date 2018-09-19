#include "serial_link_vm.h"

// Qt
#include <QDebug>

// Internal
#include "communication_service.h"
#include "serial_device_manager.h"

using namespace presentation;

SerialLinkVm::SerialLinkVm(QObject* parent):
    LinkVm(parent)
{
    connect(this, &LinkVm::linkChanged, this, &SerialLinkVm::serialLinkChanged);
    connect(this, &LinkVm::linkChanged, this, &SerialLinkVm::devicesChanged);
    connect(serialDeviceManager, &domain::SerialDeviceManager::devicesChanged,
            this, &SerialLinkVm::devicesChanged);
}

QVariantList SerialLinkVm::baudRates() const
{
    QVariantList baudRates;

    for (qint32 rate: domain::SerialDeviceManager::availableBaudRates()) baudRates.append(rate);

    return baudRates;
}

int SerialLinkVm::baudRate() const
{
    return m_description ? m_description->parameter(data_source::LinkDescription::BaudRate).toInt() : 0;
}

QStringList SerialLinkVm::availableDevices() const
{
    QStringList devices;
    devices.append(QString());
    devices.append(serialDeviceManager->availableDevices());

    if (m_description)
    {
        QString device = m_description->parameter(data_source::LinkDescription::Device).toString();
        if (!devices.contains(device)) devices.append(device);
    }

    return devices;
}

QString SerialLinkVm::device() const
{
    return m_description ? m_description->parameter(data_source::LinkDescription::Device).toString() : QString();
}

void SerialLinkVm::setBaudRate(int baudRate)
{
    if (m_description.isNull() ||
        m_description->parameter(data_source::LinkDescription::BaudRate) == baudRate) return;

    m_description->setParameter(data_source::LinkDescription::BaudRate, baudRate);
    m_commService->save(m_description);
}

void SerialLinkVm::setDevice(const QString& device)
{
    if (m_description.isNull() ||
        m_description->parameter(data_source::LinkDescription::Device) == device) return;

    m_description->setParameter(data_source::LinkDescription::Device, device);
    m_commService->save(m_description);
}
