#ifndef SERIAL_LINK_VM_H
#define SERIAL_LINK_VM_H

// Internal
#include "link_vm.h"

namespace domain
{
    class SerialPortService;
}

namespace presentation
{
    class SerialLinkVm: public LinkVm
    {
        Q_OBJECT

        Q_PROPERTY(QVariantList baudRates READ baudRates CONSTANT)
        Q_PROPERTY(QStringList availableDevices READ availableDevices
                   NOTIFY availableDevicesChanged)

    public:
        explicit SerialLinkVm(QObject* parent = nullptr);

        QVariantList baudRates() const;
        QStringList availableDevices() const;

    signals:
        void availableDevicesChanged();

    private:
        domain::SerialPortService* const m_serialService;
    };
}

#endif // SERIAL_LINK_VM_H
