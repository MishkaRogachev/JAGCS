#include "vfr_hud_handler.h"

// Qt
#include <QVariant>

// MAVLink
#include <mavlink.h>

// Internal
#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

#include "mavlink_protocol_helpers.h"

using namespace data_source;
using namespace domain;

VfrHudHandler::VfrHudHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(serviceRegistry->telemetryService())
{}

void VfrHudHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_VFR_HUD) return;

    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_vfr_hud_t vfrHud;
    mavlink_msg_vfr_hud_decode(&message, &vfrHud);

    portion.setParameter({ Telemetry::Pitot, Telemetry::IndicatedAirspeed }, vfrHud.airspeed);
    portion.setParameter({ Telemetry::Pitot, Telemetry::TrueAirspeed },
                         getTrueAirspeed(vfrHud.airspeed, vfrHud.alt));

    portion.setParameter({ Telemetry::Ahrs, Telemetry::Compass, Telemetry::Heading }, vfrHud.heading);

    portion.setParameter({ Telemetry::Barometric, Telemetry::AltitudeMsl }, vfrHud.alt);
    portion.setParameter({ Telemetry::Barometric, Telemetry::Climb }, vfrHud.climb);

    portion.setParameter({ Telemetry::PowerSystem, Telemetry::Throttle }, vfrHud.throttle);
}
