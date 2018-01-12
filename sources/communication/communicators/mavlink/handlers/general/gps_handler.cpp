#include "gps_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QVariant>
#include <QGeoCoordinate>
#include <QDateTime>

// Internal
#include "mavlink_protocol_helpers.h"

#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

#include "satellite_info.h"

using namespace comm;
using namespace domain;

GpsHandler::GpsHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(ServiceRegistry::telemetryService())
{
    qRegisterMetaType<SatelliteInfo>("SatelliteInfo");
}

void GpsHandler::processMessage(const mavlink_message_t& message)
{
    switch (message.msgid)
    {
    case MAVLINK_MSG_ID_GPS_RAW_INT:
        this->processGpsRaw(message);
        break;
    case MAVLINK_MSG_ID_GPS_STATUS:
        this->processGpsStatus(message);
        break;
    default:
        break;
    }

}

void GpsHandler::processGpsRaw(const mavlink_message_t& message)
{
    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_gps_raw_int_t gps;
    mavlink_msg_gps_raw_int_decode(&message, &gps);

    QGeoCoordinate coordinate(decodeLatLon(gps.lat), decodeLatLon(gps.lon),
                              decodeAltitude(gps.alt));

    portion.setParameter({ Telemetry::Satellite, Telemetry::Fix }, gps.fix_type);
    portion.setParameter({ Telemetry::Satellite, Telemetry::Coordinate },
                         QVariant::fromValue(coordinate));
    portion.setParameter({ Telemetry::Satellite, Telemetry::Groundspeed },
                         decodeGroundSpeed(gps.vel));
    portion.setParameter({ Telemetry::Satellite, Telemetry::Course },
                         decodeCourse(gps.cog));
    portion.setParameter({ Telemetry::Satellite, Telemetry::Altitude },
                         decodeAltitude(gps.alt));
    portion.setParameter({ Telemetry::Satellite, Telemetry::Eph }, gps.eph);
    portion.setParameter({ Telemetry::Satellite, Telemetry::Epv }, gps.epv);
    portion.setParameter({ Telemetry::Satellite, Telemetry::Time },
                         QDateTime::fromMSecsSinceEpoch(gps.time_usec));
    portion.setParameter({ Telemetry::Satellite, Telemetry::SatellitesVisible },
                         gps.satellites_visible);
}

void GpsHandler::processGpsStatus(const mavlink_message_t& message)
{
    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_gps_status_t gps;
    mavlink_msg_gps_status_decode(&message, &gps);

    QList<SatelliteInfo> infos;
    infos.reserve(gps.satellites_visible);

    for (int i = 0; i < gps.satellites_visible; ++i)
    {
        infos.append(SatelliteInfo(gps.satellite_prn[i], gps.satellite_used[i],
                                   gps.satellite_elevation[i], gps.satellite_azimuth[i],
                                   gps.satellite_snr[i]));
    }

    portion.setParameter({ Telemetry::SatellitesVisible, Telemetry::SatelliteInfos },
                         QVariant::fromValue(infos));
}
