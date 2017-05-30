#include "nav_controller_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "telemetry_service.h"
#include "mavlink_protocol_helpers.h"

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

    int vehicleId = m_telemetryService->vehicleIdByMavId(message.sysid);
    if (!vehicleId) return;

    mavlink_nav_controller_output_t output;
    mavlink_msg_nav_controller_output_decode(&message, &output);

    // TODO: handle NAV_CONTROLLER_OUTPUT
}

