#include "high_latency_handler.h"

// Qt
#include <QGeoCoordinate>
#include <QVariant>

// MAVLink
#include <mavlink.h>

// Internal
#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

#include "mavlink_protocol_helpers.h"

using namespace comm;
using namespace domain;

HighLatencyHandler::HighLatencyHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(serviceRegistry->telemetryService())
{}

void HighLatencyHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_HIGH_LATENCY) return;

// TODO: some anothr high latency data
// uint32_t custom_mode; /*< A bitfield for use for autopilot-specific flags.*/
// uint8_t landed_state; /*< The landed state. Is set to MAV_LANDED_STATE_UNDEFINED if landed state is unknown.*/
// uint8_t failsafe; /*< failsafe (each bit represents a failsafe where 0=ok, 1=failsafe active (bit0:RC, bit1:batt, bit2:GPS, bit3:GCS, bit4:fence)*/
// uint8_t wp_num; /*< current waypoint number*/
// int8_t temperature_air; /*< Air temperature (degrees C) from airspeed sensor*/

    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_high_latency_t high;
    mavlink_msg_high_latency_decode(&message, &high);

    portion.setParameter({ Telemetry::System, Telemetry::Armed },
                         bool(high.base_mode & MAV_MODE_FLAG_DECODE_POSITION_SAFETY));
    portion.setParameter({ Telemetry::System, Telemetry::Auto },
                         bool(high.base_mode & MAV_MODE_FLAG_DECODE_POSITION_AUTO));
    portion.setParameter({ Telemetry::System, Telemetry::Guided },
                         bool(high.base_mode & MAV_MODE_FLAG_DECODE_POSITION_GUIDED));
    portion.setParameter({ Telemetry::System, Telemetry::Stabilized },
                         bool(high.base_mode & MAV_MODE_FLAG_DECODE_POSITION_STABILIZE));
    portion.setParameter({ Telemetry::System, Telemetry::Manual },
                         bool(high.base_mode & MAV_MODE_FLAG_DECODE_POSITION_MANUAL));

    QGeoCoordinate coordinate(decodeLatLon(high.latitude), decodeLatLon(high.longitude),
                              decodeAltitude(high.altitude_amsl));

    portion.setParameter({ Telemetry::Position, Telemetry::Coordinate }, QVariant::fromValue(coordinate));

    portion.setParameter({ Telemetry::Navigator, Telemetry::Distance }, high.wp_distance);

    portion.setParameter({ Telemetry::Ahrs, Telemetry::Pitch }, fromCentidegrees(high.pitch));
    portion.setParameter({ Telemetry::Ahrs, Telemetry::Roll }, fromCentidegrees(high.roll));

    portion.setParameter({ Telemetry::Pitot, Telemetry::IndicatedAirspeed }, high.airspeed);
    portion.setParameter({ Telemetry::Pitot, Telemetry::TrueAirspeed },
                          getTrueAirspeed(high.airspeed, high.altitude_amsl));

    portion.setParameter({ Telemetry::Ahrs, Telemetry::Compass, Telemetry::Heading }, high.heading);

    portion.setParameter({ Telemetry::Barometric, Telemetry::AltitudeMsl }, high.altitude_amsl);
    portion.setParameter({ Telemetry::Barometric, Telemetry::AltitudeRelative }, high.altitude_sp);
    portion.setParameter({ Telemetry::Barometric, Telemetry::Climb }, high.climb_rate);

    portion.setParameter({ Telemetry::Satellite, Telemetry::Groundspeed }, high.groundspeed);
    portion.setParameter({ Telemetry::Satellite, Telemetry::Fix }, high.gps_fix_type);
    portion.setParameter({ Telemetry::Satellite, Telemetry::SatellitesVisible }, high.gps_nsat);
    portion.setParameter({ Telemetry::Barometric, Telemetry::Temperature }, high.temperature);

    portion.setParameter({ Telemetry::PowerSystem, Telemetry::Throttle }, high.throttle);

    portion.setParameter({ Telemetry::Battery, Telemetry::Percentage }, high.battery_remaining);
}
