#include "vfr_hud_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "telemetry.h"

using namespace comm;
using namespace domain;

VfrHudHandler::VfrHudHandler(TelemetryService* telemetryService,
                             MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(telemetryService)
{}

void VfrHudHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_VFR_HUD) return;

    TelemetryNode* node = m_telemetryService->nodeByMavId(message.sysid);
    if (!node) return;

    mavlink_vfr_hud_t vfrHud;
    mavlink_msg_vfr_hud_decode(&message, &vfrHud);

    node->setValue(telemetry::indicatedAirspeed, vfrHud.airspeed);
    // TODO: TAS from MAVLink TAS = IAS + [(IAS X 2/100) X (DA/1000)]
    node->setValue(telemetry::trueAirspeed,
                   vfrHud.airspeed + (vfrHud.airspeed * 0.02 * vfrHud.alt / 1000));
    node->setValue(telemetry::groundspeed, vfrHud.groundspeed);
    node->setValue({ telemetry::baro, telemetry::altitude }, vfrHud.alt);
    node->setValue({ telemetry::baro, telemetry::climb }, vfrHud.climb);
    node->setValue(telemetry::heading, vfrHud.heading);
    node->setValue({ telemetry::powerSystem, telemetry::throttle }, vfrHud.throttle);
}
