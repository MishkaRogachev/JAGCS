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

    node->setParameter({ TelemetryId::Pitot, TelemetryId::IndicatedAirspeed }, vfrHud.airspeed);
    node->setParameter({ TelemetryId::Pitot, TelemetryId::TrueAirspeed },
                       vfrHud.airspeed + (vfrHud.airspeed * 0.02 * vfrHud.alt / 1000));

    node->setParameter({ TelemetryId::Compass, TelemetryId::Heading }, vfrHud.heading);

    node->setParameter({ TelemetryId::Barometric, TelemetryId::Altitude }, vfrHud.alt);
    node->setParameter({ TelemetryId::Barometric, TelemetryId::Climb }, vfrHud.climb);

    node->setParameter({ TelemetryId::PowerSystem, TelemetryId::Throttle }, vfrHud.throttle);

    node->notify();
}
