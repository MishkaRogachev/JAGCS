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

        Q_PROPERTY(bool discoveryActive READ isDiscoveryActive NOTIFY discoveryActiveChanged)
        Q_PROPERTY(QStringList availableDevices READ availableDevices NOTIFY availableDevicesChanged)
        Q_PROPERTY(QString device READ device WRITE setDevice NOTIFY bluetoothLinkChanged)
        Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY bluetoothLinkChanged)

    public:
        explicit BluetoothLinkVm(QObject* parent = nullptr);

        bool isDiscoveryActive() const;

        QStringList availableDevices() const;
        QString device() const;
        QString address() const;

    public slots:
        void startBluetoothDiscovery();
        void stopBluetoothDiscovery();

        void setDevice(QString device);
        void setAddress(QString address);

    signals:
        void discoveryActiveChanged();
        void availableDevicesChanged();
        void bluetoothLinkChanged();

    private:
        domain::BluetoothService* const m_bluetoothService;
    };
}

#endif // BLUETOOTH_LINK_VM_H
