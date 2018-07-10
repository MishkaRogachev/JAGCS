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

using namespace data_source;
using namespace domain;

PositionHandler::PositionHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(serviceRegistry->telemetryService())
{}

void PositionHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_GLOBAL_POSITION_INT) return;

    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_global_position_int_t position;
    mavlink_msg_global_position_int_decode(&message, &position);

    QGeoCoordinate coordinate;
    if (position.lat != 0) coordinate.setLatitude(decodeLatLon(position.lat));
    if (position.lon != 0) coordinate.setLongitude(decodeLatLon(position.lon));
    coordinate.setAltitude(decodeAltitude(position.alt));

    QVector3D direction(position.vx, position.vy, position.vz);

    portion.setParameter({ Telemetry::Position, Telemetry::Coordinate },
                       QVariant::fromValue(coordinate));
    portion.setParameter({ Telemetry::Position, Telemetry::Direction },
                       QVariant::fromValue(direction));
}
