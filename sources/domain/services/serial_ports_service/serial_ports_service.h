#ifndef SERIAL_PORTS_SERVICE_H
#define SERIAL_PORTS_SERVICE_H

#include <QObject>

namespace domain
{
    class SerialPortService : public QObject
    {
        Q_OBJECT

    public:
        explicit SerialPortService(QObject* parent = nullptr);
        ~SerialPortService() override;

        static QList<qint32> availableBaudRates();
        QStringList availablePorts() const;

    public slots:
        void updateAvailablePorts();

    signals:
        void availablePortsChanged(QStringList availablePorts);

    protected:
        void timerEvent(QTimerEvent* event);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // SERIAL_PORTS_SERVICE_H
