#include "target_position_handler.h"

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

TargetPositionHandler::TargetPositionHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(serviceRegistry->telemetryService())
{}

void TargetPositionHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT) return;

    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_position_target_global_int_t position;
    mavlink_msg_position_target_global_int_decode(&message, &position);

    QGeoCoordinate coordinate(decodeLatLon(position.lat_int), decodeLatLon(position.lon_int),
                              position.alt);

    portion.setParameter({ Telemetry::Navigator, Telemetry::Coordinate },
                         QVariant::fromValue(coordinate));
}
