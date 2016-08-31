#ifndef MAVLINK_COMMUNICATOR_H
#define MAVLINK_COMMUNICATOR_H

#include "mavlink_abstract_link.h"

// MAVLink
#include <mavlink.h>

#include <mavlink_msg_sys_status.h>
#include <mavlink_msg_gps_raw_int.h>
#include <mavlink_msg_vfr_hud.h>
#include <mavlink_msg_attitude.h>

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
            void systemStatusReceived(mavlink_sys_status_t status);
            void gpsRawReceived(mavlink_gps_raw_int_t gps);
            void vfrHudReceived(mavlink_vfr_hud_t vfrHud);
            void attitudeReceived(mavlink_attitude_t attitude);

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
