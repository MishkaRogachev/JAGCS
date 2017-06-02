#include "nav_controller_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "mavlink_protocol_helpers.h"

#include "telemetry.h"

using namespace comm;
using namespace domain;

NavControllerHandler::NavControllerHandler(TelemetryService* telemetryService,
                                           MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(telemetryService)
{}

void NavControllerHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT) return;

    TelemetryNode* node = m_telemetryService->nodeByMavId(message.sysid);
    if (!node) return;

    mavlink_nav_controller_output_t output;
    mavlink_msg_nav_controller_output_decode(&message, &output);

    node->childNode(telemetry::navi)->setParameters(
    { { telemetry::targetBearing, short(output.target_bearing) },
      { telemetry::targetDistance, unsigned(output.wp_dist) },
      { telemetry::trackError, float(output.xtrack_error) },
      { telemetry::altitudeError, float(output.alt_error) },
      { telemetry::desiredPitch, float(output.nav_pitch) },
      { telemetry::desiredRoll, float(output.nav_roll) },
      { telemetry::desiredHeading, float(output.nav_bearing) } });
}

