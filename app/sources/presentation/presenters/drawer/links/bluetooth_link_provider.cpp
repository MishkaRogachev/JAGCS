#include "bluetooth_link_provider.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "bluetooth_service.h"

using namespace presentation;

BluetoothLinkProvider::BluetoothLinkProvider(QObject* parent):
    LinkProvider(parent),
    m_bluetoothService(serviceRegistry->bluetoothService())
{}
