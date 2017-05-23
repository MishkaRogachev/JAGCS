#include "position_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "telemetry_service.h"
#include "mavlink_protocol_helpers.h"

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

    int vehicleId = m_telemetryService->vehicleIdByMavId(message.sysid);
    if (!vehicleId) return;

    mavlink_global_position_int_t position;
    mavlink_msg_global_position_int_decode(&message, &position);

    m_telemetryService->setPosition(vehicleId, Position(
                                        decodeCoordinate(position.lat, position.lon, position.alt),
                                        QVector3D(position.vx, position.vy, position.vz)));
}
