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
        Q_PROPERTY(int baudRate READ baudRate WRITE setBaudRate NOTIFY baudRateChanged)
        Q_PROPERTY(QStringList availableDevices READ availableDevices NOTIFY availableDevicesChanged)
        Q_PROPERTY(QString device READ device WRITE setDevice NOTIFY deviceChanged)

    public:
        explicit SerialLinkVm(QObject* parent = nullptr);

        QVariantList baudRates() const;
        int baudRate() const;

        QStringList availableDevices() const;
        QString device() const;

    public slots:
        void setBaudRate(int baudRate);
        void setDevice(const QString& device);

    signals:
        void baudRateChanged();
        void availableDevicesChanged();
        void deviceChanged();

    private:
        domain::SerialPortService* const m_serialService;
    };
}

#endif // SERIAL_LINK_VM_H
