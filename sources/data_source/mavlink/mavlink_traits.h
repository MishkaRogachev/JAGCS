#ifndef MAVLINK_TRAITS_H
#define MAVLINK_TRAITS_H

// MAVLink
#include <mavlink.h>
/*
#include <mavlink_msg_set_position_target_local_ned.h>
#include <mavlink_msg_command_long.h>

#include <mavlink_msg_sys_status.h>
#include <mavlink_msg_gps_raw_int.h>
#include <mavlink_msg_vfr_hud.h>
#include <mavlink_msg_attitude.h>*/

namespace data_source
{
    namespace mavlink
    {
        inline void init()
        {
            qRegisterMetaType<mavlink_message_t>("mavlink_message_t");
            qRegisterMetaType<mavlink_status_t>("mavlink_status_t");
/*
            qRegisterMetaType<mavlink_set_position_target_local_ned_t>("mavlink_set_position_target_local_ned_t");
            qRegisterMetaType<mavlink_sys_status_t>("mavlink_sys_status_t");

            qRegisterMetaType<mavlink_heartbeat_t>("mavlink_heartbeat_t");
            qRegisterMetaType<mavlink_sys_status_t>("mavlink_sys_status_t");
            qRegisterMetaType<mavlink_gps_raw_int_t>("mavlink_gps_raw_int_t");
            qRegisterMetaType<mavlink_vfr_hud_t>("mavlink_vfr_hud_t");
            qRegisterMetaType<mavlink_attitude_t>("mavlink_attitude_t");*/
        }
    }
}

#endif // MAVLINK_TRAITS_H
