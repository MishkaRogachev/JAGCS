#include "autopilot_version_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QtMath>
#include <QVariant>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

using namespace comm;
using namespace domain;

AutopilotVersionHandler::AutopilotVersionHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(ServiceRegistry::telemetryService())
{}

void AutopilotVersionHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_AUTOPILOT_VERSION) return;

   // TelemetryPortion port(m_telemetryService->mavNode(message.sysid));

    mavlink_autopilot_version_t version;
    mavlink_msg_autopilot_version_decode(&message, &version);

    qDebug() << "MAVLINK2" << (version.capabilities & MAV_PROTOCOL_CAPABILITY_MAVLINK2);
}
