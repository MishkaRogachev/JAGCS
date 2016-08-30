#ifndef MAVLINK_UDP_LINK_H
#define MAVLINK_UDP_LINK_H

#include "mavlink_abstract_link.h"

class QSerialPort;

namespace data_source
{
    namespace mavlink
    {
        class UdpLink: public AbstractLink
        {
        public:
            UdpLink(const QString& portName, QObject* parent = nullptr);

        protected:
            void sendData(const QByteArray& data) override;

        private slots:
            void onReadyRead();

        private:
            QSerialPort* m_port;
        };
    }
}

#endif // MAVLINK_UDP_LINK_H
