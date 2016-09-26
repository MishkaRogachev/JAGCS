#include "abstract_mavlink_handler.h"

using namespace domain;

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

// TODO: MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT, MAVLINK_MSG_ID_MISSION_CURRENT, MAVLINK_MSG_ID_RC_CHANNELS_RAW
//       MAVLINK_MSG_ID_WIND, MAVLINK_MSG_ID_SCALED_PRESSURE, MAVLINK_MSG_ID_GLOBAL_POSITION_INT
//       MAVLINK_MSG_ID_BATTERY_STATUS, MAVLINK_MSG_ID_RADIO_STATUS, MAVLINK_MSG_ID_LOCAL_POSITION_NED,
//       MAVLINK_MSG_ID_GLOBAL_POSITION_INT, MAVLINK_MSG_ID_POSITION_TARGET_LOCAL_NED,
//       MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT, MAVLINK_MSG_ID_HIGHRES_IMU

