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

    node->setParameter({ telemetry::navigator, telemetry::targetBearing }, output.target_bearing);
    node->setParameter({ telemetry::navigator, telemetry::targetDistance }, output.wp_dist);
    node->setParameter({ telemetry::navigator, telemetry::trackError }, output.xtrack_error);
    node->setParameter({ telemetry::navigator, telemetry::altitudeError }, output.alt_error);
    node->setParameter({ telemetry::navigator, telemetry::desiredPitch }, output.nav_pitch);
    node->setParameter({ telemetry::navigator, telemetry::desiredRoll }, output.nav_roll);
    node->setParameter({ telemetry::navigator, telemetry::desiredHeading }, output.nav_bearing);

    node->notify();
}

