#ifndef SERIAL_LINK_H
#define SERIAL_LINK_H

#include "mavlink_abstract_link.h"

class QSerialPort;

namespace data_source
{
    namespace mavlink
    {
        class SerialLink: public AbstractLink
        {
        public:
            SerialLink(const QString& portName, QObject* parent = nullptr);

        protected:
            void sendData(const QByteArray& data) override;

        private slots:
            void readSerialData();

        private:
            QSerialPort* m_port;
        };
    }
}

#endif // SERIAL_LINK_H
