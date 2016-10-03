#include "gps_raw_handler.h"

// MAVLink
#include <mavlink.h>
#include <mavlink_msg_gps_raw_int.h>

// Internal
#include "vehicle_service.h"
#include "vehicle.h"

using namespace domain;

GpsRawHandler::GpsRawHandler(VehicleService* vehicleService, QObject* parent):
    AbstractMavLinkHandler(parent),
    m_vehicleService(vehicleService)
{}

void GpsRawHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_GPS_RAW_INT ||
        message.sysid == 0) return;

    Vehicle* vehicle = m_vehicleService->requestVehicle(message.sysid);

    mavlink_gps_raw_int_t gps;
    mavlink_msg_gps_raw_int_decode(&message, &gps);

    //TODO: raw navigation vehicle->
}
