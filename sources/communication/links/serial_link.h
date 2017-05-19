#ifndef SERIAL_LINK_H
#define SERIAL_LINK_H

#include "abstract_link.h"

class QSerialPort;

namespace comm
{
    class SerialLink: public AbstractLink
    {
        Q_OBJECT

    public:
        SerialLink(const QString& device, qint32 baudRate,
                   QObject* parent = nullptr);

        bool isConnected() const override;

        QString device() const;
        qint32 baudRate() const;

    public slots:
        void connectLink() override;
        void disconnectLink() override;

        void sendDataImpl(const QByteArray& data) override;

        void setDevice(QString device);
        void setBaudRate(qint32 baudRate);

    signals:
        void deviceChanged(QString device);
        void baudRateChanged(qint32 baudRate);

    private slots:
        void readSerialData();

    private:
        QSerialPort* m_port;
    };
}

#endif // SERIAL_LINK_H
