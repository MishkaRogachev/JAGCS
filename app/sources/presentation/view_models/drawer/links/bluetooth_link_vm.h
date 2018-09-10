#ifndef BLUETOOTH_LINK_VM_H
#define BLUETOOTH_LINK_VM_H

// Internal
#include "link_vm.h"

namespace domain
{
    class BluetoothService;
}

namespace presentation
{
    class BluetoothLinkVm: public LinkVm
    {
        Q_OBJECT

    public:
        explicit BluetoothLinkVm(QObject* parent = nullptr);

    private:
        domain::BluetoothService* const m_bluetoothService;
    };
}

#endif // BLUETOOTH_LINK_VM_H
