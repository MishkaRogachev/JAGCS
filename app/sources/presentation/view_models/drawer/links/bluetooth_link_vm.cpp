#include "bluetooth_link_vm.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "bluetooth_service.h"

using namespace presentation;

BluetoothLinkVm::BluetoothLinkVm(QObject* parent):
    LinkVm(parent),
    m_bluetoothService(serviceRegistry->bluetoothService())
{}
