#include "gps_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QVariant>
#include <QGeoCoordinate>
#include <QDateTime>

// Internal
#include "mavlink_protocol_helpers.h"
#include "telemetry.h"

using namespace comm;
using namespace domain;

namespace
{
    int gpdFixFromFixType(uint8_t fixType)
    {
        return 0;/* TODO: gps fix
        switch (fixType) {
        case GPS_FIX_TYPE_NO_GPS:
        default: return telemetry::SnsFix::NoGps;
        case GPS_FIX_TYPE_NO_FIX: return telemetry::SnsFix::NoFix;
        case GPS_FIX_TYPE_2D_FIX: return telemetry::SnsFix::Fix2D;
        case GPS_FIX_TYPE_3D_FIX:
        case GPS_FIX_TYPE_DGPS:
        case GPS_FIX_TYPE_RTK_FLOAT:
        case GPS_FIX_TYPE_RTK_FIXED: return telemetry::SnsFix::Fix3D;
        }*/
    }
}

GpsHandler::GpsHandler(TelemetryService* telemetryService,
                       MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(telemetryService)
{} // TODO: handle GPS_STATUS

void GpsHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_GPS_RAW_INT) return;

    TelemetryNode* node = m_telemetryService->nodeByMavId(message.sysid);
    if (!node) return;

    mavlink_gps_raw_int_t gps;
    mavlink_msg_gps_raw_int_decode(&message, &gps);

    QGeoCoordinate coordinate(decodeLatLon(gps.lat), decodeLatLon(gps.lon),
                              decodeAltitude(gps.alt));

    node->setParameter({ TelemetryId::Satellite, TelemetryId::Fix },
                       ::gpdFixFromFixType(gps.fix_type));
    node->setParameter({ TelemetryId::Satellite, TelemetryId::Coordinate },
                       QVariant::fromValue(coordinate));
    node->setParameter({ TelemetryId::Satellite, TelemetryId::Groundspeed },
                       decodeGroundSpeed(gps.vel));
    node->setParameter({ TelemetryId::Satellite, TelemetryId::Course },
                       decodeCourse(gps.cog));
    node->setParameter({ TelemetryId::Satellite, TelemetryId::Altitude },
                       decodeAltitude(gps.alt));
    node->setParameter({ TelemetryId::Satellite, TelemetryId::Eph }, gps.eph);
    node->setParameter({ TelemetryId::Satellite, TelemetryId::Epv }, gps.epv);
    node->setParameter({ TelemetryId::Satellite, TelemetryId::Time },
                       QDateTime::fromMSecsSinceEpoch(gps.time_usec));
    node->setParameter({ TelemetryId::Satellite, TelemetryId::SatellitesVisible },
                       decodeAltitude(gps.satellites_visible));

    node->notify();
}
