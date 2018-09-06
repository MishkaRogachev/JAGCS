#ifndef BLUETOOTH_LINK_PROVIDER_H
#define BLUETOOTH_LINK_PROVIDER_H

// Internal
#include "link_provider.h"

namespace domain
{
    class BluetoothService;
}

namespace presentation
{
    class BluetoothLinkProvider: public LinkProvider
    {
        Q_OBJECT

    public:
        explicit BluetoothLinkProvider(QObject* parent = nullptr);

    private:
        domain::BluetoothService* const m_bluetoothService;
    };
}

#endif // BLUETOOTH_LINK_PROVIDER_H
