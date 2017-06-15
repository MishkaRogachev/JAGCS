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

    node->setParameter({ TelemetryId::Navigator, TelemetryId::TargetBearing }, output.target_bearing);
    node->setParameter({ TelemetryId::Navigator, TelemetryId::TargetDistance }, output.wp_dist);
    node->setParameter({ TelemetryId::Navigator, TelemetryId::TrackError }, output.xtrack_error);
    node->setParameter({ TelemetryId::Navigator, TelemetryId::AltitudeError }, output.alt_error);
    node->setParameter({ TelemetryId::Navigator, TelemetryId::DesiredPitch }, output.nav_pitch);
    node->setParameter({ TelemetryId::Navigator, TelemetryId::DesiredRoll }, output.nav_roll);
    node->setParameter({ TelemetryId::Navigator, TelemetryId::DesiredHeading }, output.nav_bearing);

    node->notify();
}

