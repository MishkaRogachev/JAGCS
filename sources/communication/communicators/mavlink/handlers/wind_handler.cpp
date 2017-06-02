#include "wind_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "telemetry.h"

using namespace comm;
using namespace domain;

WindHandler::WindHandler(TelemetryService* telemetryService,
                         MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(telemetryService)
{}

void WindHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_WIND) return;

    TelemetryNode* node = m_telemetryService->nodeByMavId(message.sysid);
    if (!node) return;

    mavlink_wind_t wind;
    mavlink_msg_wind_decode(&message, &wind);

    node->childNode(telemetry::wind)->setParameters(
    { { telemetry::yaw, float(wind.direction) },
      { telemetry::speed, float(wind.speed) },
      { telemetry::climb, float(wind.speed_z) } });
}
