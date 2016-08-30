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
        public:
            SerialLink(const QString& portName, qint32 baudRate,
                       QObject* parent = nullptr);

            bool isUp() const override;

        public slots:
            void up() override;
            void down() override;

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
