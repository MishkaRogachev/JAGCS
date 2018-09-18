#ifndef SERIAL_DEVICE_MANAGER_H
#define SERIAL_DEVICE_MANAGER_H

#include <QObject>

namespace domain
{
    class SerialDeviceManager: public QObject
    {
        Q_OBJECT

    public:
        explicit SerialDeviceManager(QObject* parent = nullptr);
        ~SerialDeviceManager() override;

        static SerialDeviceManager* instance();

        static QList<qint32> availableBaudRates();

        QStringList busyDevices() const;
        QStringList availableDevices() const;
        QStringList allDevices() const;

    public slots:
        void discoverDevices();
        void setBusyDevices(const QStringList& busyDevices);
        void setAvailableDevices(const QStringList& availableDevices);

    signals:
        void devicesDiscovered(QStringList devices);
        void devicesChanged();

    protected:
        void timerEvent(QTimerEvent* event) override;

    private:
        int m_timerId;
        QStringList m_availableDevices;
        QStringList m_busyDevices;

        static SerialDeviceManager* lastCreatedManager;

        Q_DISABLE_COPY(SerialDeviceManager)
    };
}

#define serialDeviceManager (domain::SerialDeviceManager::instance())

#endif // SERIAL_DEVICE_MANAGER_H
