#include "bluetooth_link_vm.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "bluetooth_service.h"
#include "communication_service.h"

using namespace presentation;

BluetoothLinkVm::BluetoothLinkVm(QObject* parent):
    LinkVm(parent),
    m_bluetoothService(serviceRegistry->bluetoothService())
{}

bool BluetoothLinkVm::isDiscoveryActive() const
{
    return m_bluetoothService->isDiscoveryActive();
}

QStringList BluetoothLinkVm::availableDevices() const
{
    return m_bluetoothService->discoveredDevices();
}

QString BluetoothLinkVm::device() const
{
    return m_description ? m_description->parameter(dto::LinkDescription::Device).toString() : QString();
}

QString BluetoothLinkVm::address() const
{
    return m_description ? m_description->parameter(dto::LinkDescription::Address).toString() : QString();
}

void BluetoothLinkVm::startBluetoothDiscovery()
{
    m_bluetoothService->startDiscovery();
}

void BluetoothLinkVm::stopBluetoothDiscovery()
{
    m_bluetoothService->stopDiscovery();
}

void BluetoothLinkVm::setDevice(QString device)
{
    if (m_description.isNull() ||
        m_description->parameter(dto::LinkDescription::Device) == device) return;

    m_description->setParameter(dto::LinkDescription::Device, device);
    if (m_commService->save(m_description)) emit deviceChanged();
}

void BluetoothLinkVm::setAddress(QString address)
{
    if (m_description.isNull() ||
        m_description->parameter(dto::LinkDescription::Address) == address) return;

    m_description->setParameter(dto::LinkDescription::Address, address);
    if (m_commService->save(m_description)) emit addressChanged();
}
