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

    node->setParameters(
    { { telemetry::indicatedAirspeed, float(vfrHud.airspeed) },
      { telemetry::trueAirspeed,
        vfrHud.airspeed + (vfrHud.airspeed * 0.02 * vfrHud.alt / 1000) },
      // TODO: TAS from MAVLink TAS = IAS + [(IAS X 2/100) X (DA/1000)]
      { telemetry::groundspeed, float(vfrHud.groundspeed) },
      { telemetry::heading, short(vfrHud.heading) } });

    node->childNode(telemetry::barometer)->setParameters(
    { { telemetry::altitude, float(vfrHud.alt) },
      { telemetry::climb, float(vfrHud.climb) } });

    node->childNode(telemetry::powerSystem)->setParameters(
    { { telemetry::throttle, float(vfrHud.throttle) } });
}
