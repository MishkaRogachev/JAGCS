#include "attitude_handler.h"

// MAVLink
#include <mavlink.h>
#include <mavlink_msg_attitude.h>

using namespace data_source;

AttitudeHandler::AttitudeHandler():
    AbstractMavLinkHandler()
{}

int AttitudeHandler::messageId() const
{
    return MAVLINK_MSG_ID_ATTITUDE;
}

void AttitudeHandler::processMessage(const mavlink_message_t& message)
{
    mavlink_attitude_t attitude;
    mavlink_msg_attitude_decode(&message, &attitude);

    // TODO: handle attitude
}
