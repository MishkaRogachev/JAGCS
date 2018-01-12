#include "altitude_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

using namespace comm;
using namespace domain;

AltitudeHandler::AltitudeHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(ServiceRegistry::telemetryService())
{}

void AltitudeHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_ALTITUDE) return;

    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_altitude_t altitude;
    mavlink_msg_altitude_decode(&message, &altitude);

    portion.setParameter({ Telemetry::Barometric, Telemetry::AltitudeMsl }, altitude.altitude_amsl);
    portion.setParameter({ Telemetry::Barometric, Telemetry::AltitudeRelative }, altitude.altitude_relative);
    portion.setParameter({ Telemetry::Barometric, Telemetry::AltitudeTerrain }, altitude.altitude_terrain);
}
