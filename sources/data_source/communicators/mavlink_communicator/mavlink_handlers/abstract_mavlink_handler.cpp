#include "abstract_mavlink_handler.h"

using namespace data_source;

AbstractMavLinkHandler::AbstractMavLinkHandler()
{}

AbstractMavLinkHandler::~AbstractMavLinkHandler()
{}

bool AbstractMavLinkHandler::handleMessage(const mavlink_message_t& message)
{
    if (message.msgid == this->messageId())
    {
        this->processMessage(message);
        return true;
    }
    return false;
}

/*
    void processSystemStatus(const mavlink_message_t& message)
    {
        mavlink_sys_status_t status;
        mavlink_msg_sys_status_decode(&message, &status);

        emit p->systemStatusReceived(status);
    }

    void processGpsRaw(const mavlink_message_t& message)
    {
        mavlink_gps_raw_int_t gps;
        mavlink_msg_gps_raw_int_decode(&message, &gps);

        emit p->gpsRawReceived(gps);
    }

    void processVfrHud(const mavlink_message_t& message)
    {
        mavlink_vfr_hud_t vfrHud;
        mavlink_msg_vfr_hud_decode(&message, &vfrHud);

        emit p->vfrHudReceived(vfrHud);
    }

    void processAttitude(const mavlink_message_t& message)
    {
        mavlink_attitude_t attitude;
        mavlink_msg_attitude_decode(&message, &attitude);

        emit p->attitudeReceived(attitude);
    }

void Communicator::handleMessage(const mavlink_message_t& message)
{
    switch (message.msgid) {
    case MAVLINK_MSG_ID_SYS_STATUS: // voltage, current, remaining
        d->processSystemStatus(message);
        break;
    case MAVLINK_MSG_ID_GPS_RAW_INT: // lat, lon, fix, satellites, cog, eph
        d->processGpsRaw(message);
        break;
    case MAVLINK_MSG_ID_VFR_HUD: // airspeed, groundspeed, heading, throttle, alt, climb
        d->processVfrHud(message);
        break;
    case MAVLINK_MSG_ID_ATTITUDE: // pitch, roll, yaw
        d->processAttitude(message);
        break;
    // TODO: MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT, MAVLINK_MSG_ID_MISSION_CURRENT, MAVLINK_MSG_ID_RC_CHANNELS_RAW
    //       MAVLINK_MSG_ID_WIND, MAVLINK_MSG_ID_SCALED_PRESSURE, MAVLINK_MSG_ID_GLOBAL_POSITION_INT
    //       MAVLINK_MSG_ID_BATTERY_STATUS, MAVLINK_MSG_ID_RADIO_STATUS, MAVLINK_MSG_ID_LOCAL_POSITION_NED,
    //       MAVLINK_MSG_ID_GLOBAL_POSITION_INT, MAVLINK_MSG_ID_POSITION_TARGET_LOCAL_NED,
    //       MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT, MAVLINK_MSG_ID_HIGHRES_IMU
    default:
        break;
    }

    emit messageReceived(message);
}
*/
