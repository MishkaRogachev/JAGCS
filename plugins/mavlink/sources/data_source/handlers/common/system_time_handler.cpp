#include "system_time_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDateTime>
#include <QDebug>

// Internal
#include "mavlink_protocol_helpers.h"

#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

using namespace comm;
using namespace domain;

SystemTimeHandler::SystemTimeHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(serviceRegistry->telemetryService())
{}

void SystemTimeHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_SYSTEM_TIME) return;

    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_system_time_t time;
    mavlink_msg_system_time_decode(&message, &time);

    portion.setParameter({ Telemetry::System, Telemetry::Time },
                         QDateTime::fromMSecsSinceEpoch(time.time_unix_usec));
}
