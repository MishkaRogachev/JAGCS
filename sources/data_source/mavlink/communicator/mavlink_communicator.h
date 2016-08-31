#ifndef MAVLINK_COMMUNICATOR_H
#define MAVLINK_COMMUNICATOR_H

#include "mavlink_abstract_link.h"

// MAVLink
#include <mavlink.h>

namespace data_source
{
    namespace mavlink
    {
        class Communicator: public QObject
        {
            Q_OBJECT

        public:
            explicit Communicator(QObject* parent = nullptr);
            ~Communicator() override;

        public slots:
            void addLink(AbstractLink* link);
            void removeLink(AbstractLink* link);

            void sendMessage(const mavlink_message_t& message);

        signals:
            void heartBeatReceived(mavlink_heartbeat_t heartbeat);

            void messageReceived(mavlink_message_t message);

        private slots:
            void handleMessage(const mavlink_message_t& message);

        private:
            class Impl;
            Impl* const d;
        };
    }
}

#endif // MAVLINK_COMMUNICATOR_H
