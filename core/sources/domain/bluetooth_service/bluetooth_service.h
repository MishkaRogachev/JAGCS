#ifndef BLUETOOTH_SERVICE_H
#define BLUETOOTH_SERVICE_H

#include <QObject>

class QBluetoothDeviceInfo;

namespace domain
{
    class BluetoothService: public QObject
    {
        Q_OBJECT

    public:
        explicit BluetoothService(QObject* parent = nullptr);
        ~BluetoothService() override;

        QStringList discoveredDevices() const;
        bool isDiscoveryActive() const;

        QString deviceAddress(const QString& name) const;

    public:
        void startDiscovery();
        void stopDiscovery();

    signals:
        void deviceDiscovered(QString device);
        void stopped();

    private slots:
        void onDeviceDiscovered(const QBluetoothDeviceInfo& info);
        void onStopped();
        void onError(int error);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // BLUETOOTH_SERVICE_H
