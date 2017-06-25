#include "vfr_hud_handler.h"

// Qt
#include <QVariant>

// MAVLink
#include <mavlink.h>

// Internal
#include "telemetry_service.h"
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

    Telemetry* node = m_telemetryService->mavNode(message.sysid);
    if (!node) return;

    mavlink_vfr_hud_t vfrHud;
    mavlink_msg_vfr_hud_decode(&message, &vfrHud);

    node->setParameter({ Telemetry::Pitot, Telemetry::IndicatedAirspeed }, vfrHud.airspeed);
    node->setParameter({ Telemetry::Pitot, Telemetry::TrueAirspeed },
                       vfrHud.airspeed + (vfrHud.airspeed * 0.02 * vfrHud.alt / 1000));

    node->setParameter({ Telemetry::Compass, Telemetry::Heading }, vfrHud.heading);

    node->setParameter({ Telemetry::Barometric, Telemetry::Altitude }, vfrHud.alt);
    node->setParameter({ Telemetry::Barometric, Telemetry::Climb }, vfrHud.climb);

    node->setParameter({ Telemetry::PowerSystem, Telemetry::Throttle }, vfrHud.throttle);

    node->notify();
}
