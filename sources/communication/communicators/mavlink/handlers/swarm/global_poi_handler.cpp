#include "global_poi_handler.h"

// SwarmLink
#include <swarmlink/mavlink.h>

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "mavlink_protocol_helpers.h"

#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

using namespace comm;
using namespace domain;

GlobalPoiHandler::GlobalPoiHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(serviceRegistry->telemetryService())
{}

void GlobalPoiHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_GLOBAL_POI) return;

    mavlink_global_poi_t poi;
    mavlink_msg_altitude_decode(&message, &poi);

    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    QGeoCoordinate coordinate(decodeLatLon(poi.lat), decodeLatLon(poi.lon), decodeAltitude(poi.alt));

    portion.setParameter({ Telemetry::Swarm, Telemetry::Poi, Telemetry::Coordinate }, coordinate);
    portion.setParameter({ Telemetry::Swarm, Telemetry::Poi, Telemetry::Group }, poi.gpid);
    portion.setParameter({ Telemetry::Swarm, Telemetry::Poi, Telemetry::Number }, poi.poi_n);
}
