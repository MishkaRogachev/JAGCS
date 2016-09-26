#include "gps_raw_handler.h"

// MAVLink
#include <mavlink.h>
#include <mavlink_msg_gps_raw_int.h>

using namespace domain;

GpsRawHandler::GpsRawHandler():
    AbstractMavLinkHandler()
{}

int GpsRawHandler::messageId() const
{
    return MAVLINK_MSG_ID_GPS_RAW_INT;
}

void GpsRawHandler::processMessage(const mavlink_message_t& message)
{
    mavlink_gps_raw_int_t gps;
    mavlink_msg_gps_raw_int_decode(&message, &gps);

    // TODO: handle gps raw
}
