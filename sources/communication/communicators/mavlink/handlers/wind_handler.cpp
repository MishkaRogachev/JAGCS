#include "wind_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "telemetry_service.h"

using namespace comm;
using namespace domain;

WindHandler::WindHandler(TelemetryService* telemetryService,
                         MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(telemetryService)
{}

void WindHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_WIND) return;

    int vehicleId = m_telemetryService->vehicleIdByMavId(message.sysid);
    if (!vehicleId) return;

    mavlink_wind_t wind;
    mavlink_msg_wind_decode(&message, &wind);

    // TODO: wind
    //m_telemetryService->setA->setWind(Wind(wind.direction, wind.speed, wind.speed_z));
}
