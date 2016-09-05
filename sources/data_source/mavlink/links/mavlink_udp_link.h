#ifndef MAVLINK_UDP_LINK_H
#define MAVLINK_UDP_LINK_H

#include "mavlink_abstract_link.h"

// Qt
#include <QHostAddress>

class QUdpSocket;

namespace data_source
{
    namespace mavlink
    {
        class UdpLink: public AbstractLink
        {
            Q_OBJECT

        public:
            UdpLink(int hostPort, const QHostAddress& address, int port,
                    QObject* parent = nullptr);

            bool isUp() const override;

        public slots:
            void up() override;
            void down() override;

        protected:
            void sendData(const QByteArray& data) override;

        private slots:
            void readPendingDatagrams();

        private:
            QUdpSocket* m_socket;
            int m_hostPort;
            QHostAddress m_address;
            int m_port;
        };
    }
}

#endif // MAVLINK_UDP_LINK_H
