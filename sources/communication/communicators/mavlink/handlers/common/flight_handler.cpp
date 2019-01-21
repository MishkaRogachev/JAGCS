#include "flight_handler.h"

// SwarmLink
#include <swarmlink/mavlink.h>

// Qt
#include <QVariant>
#include <QDateTime>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

using namespace comm;
using namespace domain;

FlightHandler::FlightHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(serviceRegistry->telemetryService())
{}

void FlightHandler::processMessage(const mavlink_message_t& message)
{
#ifdef MAVLINK_V2
    if (message.msgid != MAVLINK_MSG_ID_FLIGHT_INFORMATION) return;

    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_flight_information_t info;
    mavlink_msg_flight_information_decode(&message, &info);

    portion.setParameter({ Telemetry::Flight, Telemetry::Uid }, quint64(info.flight_uuid));
    portion.setParameter({ Telemetry::Flight, Telemetry::Time },
                         QDateTime::fromMSecsSinceEpoch(info.takeoff_time_utc));
#endif
}
