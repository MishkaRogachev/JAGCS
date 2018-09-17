#ifndef SERIAL_DEVICE_POOL_H
#define SERIAL_DEVICE_POOL_H

// Qt
#include <QObject>

namespace data_source
{
    class SerialLink;

    class SerialDevicePool: public QObject
    {
        Q_OBJECT

    public:
        explicit SerialDevicePool(QObject* parent = nullptr);
        ~SerialDevicePool() override;

        QStringList allDevices() const;
        QStringList busyDevices() const;
        QStringList availableDevices() const;

    public slots:
        void setDiscoveredDevices(const QStringList& newDevices);

        void updateLink(SerialLink* link);
        void removeLink(SerialLink* link);

    signals:
        void devicesChanged();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // SERIAL_DEVICE_POOL_H
