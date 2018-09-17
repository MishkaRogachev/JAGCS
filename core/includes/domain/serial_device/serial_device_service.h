#ifndef SERIAL_DEVICE_SERVICE_H
#define SERIAL_DEVICE_SERVICE_H

#include <QObject>

namespace data_source
{
    class SerialDevicePool;
}

namespace domain
{
    class SerialDeviceService: public QObject
    {
        Q_OBJECT

    public:
        explicit SerialDeviceService(QObject* parent = nullptr);

        static QList<qint32> availableBaudRates();

        data_source::SerialDevicePool* pool() const;

    public slots:
        void discoverDevices();

    protected:
        void timerEvent(QTimerEvent* event) override;

    private:
        int m_timerId;
        data_source::SerialDevicePool* m_pool;
    };
}

#endif // SERIAL_DEVICE_SERVICE_H
