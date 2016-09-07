#ifndef MAVLINK_SERIAL_LINK_H
#define MAVLINK_SERIAL_LINK_H

#include "mavlink_abstract_link.h"

class QSerialPort;

namespace data_source
{
    namespace mavlink
    {
        class SerialLink: public AbstractLink
        {
            Q_OBJECT

            Q_PROPERTY(QString portName READ portName WRITE setPortName NOTIFY portNameChanged)
            Q_PROPERTY(qint32 baudRate READ baudRate WRITE setBaudRate NOTIFY baudRateChanged)

        public:
            SerialLink(const QString& portName, qint32 baudRate,
                       QObject* parent = nullptr);

            bool isUp() const override;

            QString portName() const;
            qint32 baudRate() const;

        public slots:
            void up() override;
            void down() override;

            void setPortName(QString portName);
            void setBaudRate(qint32 baudRate);

        signals:
            void portNameChanged(QString portName);
            void baudRateChanged(qint32 baudRate);

        protected:
            void sendData(const QByteArray& data) override;

        private slots:
            void readSerialData();

        private:
            QSerialPort* m_port;
        };
    }
}

#endif // MAVLINK_SERIAL_LINK_H
