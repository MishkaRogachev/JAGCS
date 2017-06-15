#include "position_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QVector3D>
#include <QVariant>
#include <QDebug>

// Internal
#include "mavlink_protocol_helpers.h"

#include "telemetry_service.h"
#include "telemetry.h"

using namespace comm;
using namespace domain;

PositionHandler::PositionHandler(TelemetryService* telemetryService,
                                 MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(telemetryService)
{}

void PositionHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_GLOBAL_POSITION_INT) return;

    Telemetry* node = m_telemetryService->nodeByMavId(message.sysid);
    if (!node) return;

    mavlink_global_position_int_t position;
    mavlink_msg_global_position_int_decode(&message, &position);

    QGeoCoordinate coordinate(decodeLatLon(position.lat), decodeLatLon(position.lon),
                              decodeAltitude(position.alt));
    QVector3D direction(position.vx, position.vy, position.vz);

    node->setParameter({ Telemetry::Position, Telemetry::Coordinate },
                       QVariant::fromValue(coordinate));
    node->setParameter({ Telemetry::Position, Telemetry::Direction },
                       QVariant::fromValue(direction));

    node->notify();
}
