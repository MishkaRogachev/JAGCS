#ifndef SERIAL_LINK_PROVIDER_H
#define SERIAL_LINK_PROVIDER_H

// Internal
#include "link_provider.h"

namespace domain
{
    class SerialPortService;
}

namespace presentation
{
    class SerialLinkProvider: public LinkProvider
    {
        Q_OBJECT

        Q_PROPERTY(QVariantList baudRates READ baudRates CONSTANT)
        Q_PROPERTY(QStringList availableDevices READ availableDevices
                   NOTIFY availableDevicesChanged)

    public:
        explicit SerialLinkProvider(QObject* parent = nullptr);

        QVariantList baudRates() const;
        QStringList availableDevices() const;

    signals:
        void availableDevicesChanged();

    private:
        domain::SerialPortService* const m_serialService;
    };
}

#endif // SERIAL_LINK_PROVIDER_H
