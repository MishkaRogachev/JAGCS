#include "wind_handler.h"

// Qt
#include <QVariant>

// MAVLink
#include <mavlink.h>

// Internal
#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

using namespace data_source;
using namespace domain;

WindHandler::WindHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(serviceRegistry->telemetryService())
{}

void WindHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_WIND) return;

    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_wind_t wind;
    mavlink_msg_wind_decode(&message, &wind);

    portion.setParameter({ Telemetry::Wind, Telemetry::Yaw }, wind.direction);
    portion.setParameter({ Telemetry::Wind, Telemetry::Speed }, wind.speed);
    portion.setParameter({ Telemetry::Wind, Telemetry::Climb }, wind.speed_z);
}
