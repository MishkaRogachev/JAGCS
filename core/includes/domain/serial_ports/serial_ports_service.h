#ifndef SERIAL_PORTS_SERVICE_H
#define SERIAL_PORTS_SERVICE_H

#include <QObject>

namespace domain
{
    // TODO: serial device service
    class SerialPortService : public QObject
    {
        Q_OBJECT

    public:
        explicit SerialPortService(QObject* parent = nullptr);
        ~SerialPortService() override;

        static QList<qint32> availableBaudRates();

        QStringList devices() const;
        QStringList busyDevices() const;
        QStringList availableDevices() const;

    public slots:
        void updateDevices();

        void holdDevice(const QString& port);
        void releaseDevice(const QString& port);

    signals:
        void devicesChanged();
        void availableDevicesChanged();

    protected:
        void timerEvent(QTimerEvent* event) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // SERIAL_PORTS_SERVICE_H
