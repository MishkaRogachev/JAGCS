#include "heartbeat_handler.h"

// MAVLink
#include <mavlink.h>

using namespace domain;

HeartbeatHandler::HeartbeatHandler():
    AbstractMavLinkHandler()
{}

int HeartbeatHandler::messageId() const
{
    return MAVLINK_MSG_ID_HEARTBEAT;
}

void HeartbeatHandler::processMessage(const mavlink_message_t& message)
{
    mavlink_heartbeat_t heartbeat;
    mavlink_msg_heartbeat_decode(&message, &heartbeat);

    // TODO: handle heartbeat
}
