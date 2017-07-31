#include "wind_handler.h"

// Qt
#include <QVariant>

// MAVLink
#include <mavlink.h>

// Internal
#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry.h"

using namespace comm;
using namespace domain;

WindHandler::WindHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(ServiceRegistry::telemetryService())
{}

void WindHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_WIND) return;

    Telemetry* node = m_telemetryService->mavNode(message.sysid);
    if (!node) return;

    mavlink_wind_t wind;
    mavlink_msg_wind_decode(&message, &wind);

    node->setParameter({ Telemetry::Wind, Telemetry::Yaw }, wind.direction);
    node->setParameter({ Telemetry::Wind, Telemetry::Speed }, wind.speed);
    node->setParameter({ Telemetry::Wind, Telemetry::Climb }, wind.speed_z);

    node->notify();
}
