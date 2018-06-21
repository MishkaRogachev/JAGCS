#ifndef BLUETOOTH_SERVICE_H
#define BLUETOOTH_SERVICE_H

#include <QObject>

namespace domain
{
    // TODO: serial device service
    class BluetoothService : public QObject
    {
        Q_OBJECT

    public:
        explicit BluetoothService(QObject* parent = nullptr);
        ~BluetoothService() override;

        QStringList devices() const;
        bool isDiscoveryActive() const;

    public:
        void startDiscovery();
        void stopDiscovery();

    signals:
        void deviceAdded(QString device);
        void stopped();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // BLUETOOTH_SERVICE_H
