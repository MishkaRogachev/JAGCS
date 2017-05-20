#include "gps_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "vehicle_service.h"
#include "base_vehicle.h"

#include "mavlink_protocol_helpers.h"

using namespace comm;
using namespace domain;

namespace
{
    Sns::Fix gpdFixFromFixType(uint8_t fixType)
    {
        switch (fixType) {
        case GPS_FIX_TYPE_NO_GPS:
        default: return Sns::NoGps;
        case GPS_FIX_TYPE_NO_FIX: return Sns::NoFix;
        case GPS_FIX_TYPE_2D_FIX: return Sns::Fix2D;
        case GPS_FIX_TYPE_3D_FIX:
        case GPS_FIX_TYPE_DGPS:
        case GPS_FIX_TYPE_RTK_FLOAT:
        case GPS_FIX_TYPE_RTK_FIXED: return Sns::Fix3D;
        }
    }
}

GpsHandler::GpsHandler(VehicleService* vehicleService,
                       MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(vehicleService)
{} // TODO: handle GPS_STATUS

void GpsHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_GPS_RAW_INT) return;

    BaseVehicle* vehicle = m_vehicleService->baseVehicle(message.sysid);
    if (!vehicle) return;

    mavlink_gps_raw_int_t gps;
    mavlink_msg_gps_raw_int_decode(&message, &gps);

    vehicle->setGps(Sns(::gpdFixFromFixType(gps.fix_type),
                        gps.satellites_visible < 255 ?
                            gps.satellites_visible : -1,
                        QGeoCoordinate(decodeLatLon(gps.lat),
                                       decodeLatLon(gps.lon),
                                       decodeAltitude(gps.alt)),
                        decodeCourse(gps.cog),
                        gps.eph,
                        gps.epv));
}
