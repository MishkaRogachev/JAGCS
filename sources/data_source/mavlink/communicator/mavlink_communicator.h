#ifndef MAVLINK_COMMUNICATOR_H
#define MAVLINK_COMMUNICATOR_H

#include "i_link.h"

// MAVLink
#include <mavlink.h>

#include <mavlink_msg_set_position_target_local_ned.h>
#include <mavlink_msg_command_long.h>

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

            QList<ILink*> links() const;

        public slots:
            void addLink(ILink* link);
            void removeLink(ILink* link);

            void sendSetPositionTargetLocal(
                    const mavlink_set_position_target_local_ned_t& setPoint);
            void sendCommandLong(const mavlink_command_long_t& com);

            void sendMessage(const mavlink_message_t& message);

        signals:
            void heartBeatReceived(mavlink_heartbeat_t heartbeat);
            void systemStatusReceived(mavlink_sys_status_t status);
            void gpsRawReceived(mavlink_gps_raw_int_t gps);
            void vfrHudReceived(mavlink_vfr_hud_t vfrHud);
            void attitudeReceived(mavlink_attitude_t attitude);

            void messageReceived(mavlink_message_t message);

        private slots:
            void handleData(const QByteArray& data);
            void handleMessage(const mavlink_message_t& message);

        private:
            class Impl;
            Impl* const d;
        };
    }
}

#endif // MAVLINK_COMMUNICATOR_H
