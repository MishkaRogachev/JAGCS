#include "attitude_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QtMath>

// Internal
#include "telemetry_service.h"

using namespace comm;
using namespace domain;

AttitudeHandler::AttitudeHandler(TelemetryService* telemetryService,
                                 MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(telemetryService)
{}

void AttitudeHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_ATTITUDE) return;

    int vehicleId = m_telemetryService->vehicleIdByMavId(message.sysid);
    if (!vehicleId) return;

    mavlink_attitude_t attitude;
    mavlink_msg_attitude_decode(&message, &attitude);

    m_telemetryService->setAttitude(vehicleId, Attitude(qRadiansToDegrees(attitude.pitch),
                                                        qRadiansToDegrees(attitude.roll),
                                                        qRadiansToDegrees(attitude.yaw)));
}
