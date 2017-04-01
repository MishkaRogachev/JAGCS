#ifndef SERIAL_LINK_H
#define SERIAL_LINK_H

#include "abstract_link.h"

class QSerialPort;

namespace data_source
{
    class SerialLink: public AbstractLink
    {
        Q_OBJECT

        Q_PROPERTY(QString device READ device WRITE setDevice NOTIFY deviceChanged)
        Q_PROPERTY(qint32 baudRate READ baudRate WRITE setBaudRate NOTIFY baudRateChanged)

    public:
        SerialLink(const QString& device, qint32 baudRate,
                   QObject* parent = nullptr);

        bool isUp() const override;

        QString device() const;
        qint32 baudRate() const;

    public slots:
        void up() override;
        void down() override;

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
