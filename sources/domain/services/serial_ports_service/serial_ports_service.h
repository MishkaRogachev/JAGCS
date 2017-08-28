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

        static QList<qint32> availableBaudRates();
        QStringList availablePorts() const;

    public slots:
        void updateAvailablePorts();

    signals:
        void availablePortsChanged(QStringList availablePorts);

    protected:
        void timerEvent(QTimerEvent* event);

    private:
        int m_timerId;
        QStringList m_availablePorts;
    };
}

#endif // SERIAL_PORTS_SERVICE_H
