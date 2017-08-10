#include "position_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QVector3D>
#include <QVariant>
#include <QDebug>

// Internal
#include "mavlink_protocol_helpers.h"

#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

using namespace comm;
using namespace domain;

PositionHandler::PositionHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(ServiceRegistry::telemetryService())
{}

void PositionHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_GLOBAL_POSITION_INT) return;

    TelemetryPortion port(m_telemetryService->mavNode(message.sysid));

    mavlink_global_position_int_t position;
    mavlink_msg_global_position_int_decode(&message, &position);

    QGeoCoordinate coordinate(decodeLatLon(position.lat), decodeLatLon(position.lon),
                              decodeAltitude(position.alt));
    QVector3D direction(position.vx, position.vy, position.vz);

    port.setParameter({ Telemetry::Position, Telemetry::Coordinate },
                       QVariant::fromValue(coordinate));
    port.setParameter({ Telemetry::Position, Telemetry::Direction },
                       QVariant::fromValue(direction));
}
