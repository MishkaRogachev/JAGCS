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
{
    connect(this, &LinkVm::linkChanged, this, &BluetoothLinkVm::bluetoothLinkChanged);
}

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
    return m_description ? m_description->parameter(data_source::LinkDescription::Device).toString() : QString();
}

QString BluetoothLinkVm::address() const
{
    return m_description ? m_description->parameter(data_source::LinkDescription::Address).toString() : QString();
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
        m_description->parameter(data_source::LinkDescription::Device) == device) return;

    m_description->setParameter(data_source::LinkDescription::Device, device);
    m_commService->save(m_description);
}

void BluetoothLinkVm::setAddress(QString address)
{
    if (m_description.isNull() ||
        m_description->parameter(data_source::LinkDescription::Address) == address) return;

    m_description->setParameter(data_source::LinkDescription::Address, address);
    m_commService->save(m_description);
}
