#include "attitude_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QtMath>
#include <QDebug>

// Internal
#include "telemetry.h"

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

    TelemetryNode* node = m_telemetryService->nodeByMavId(message.sysid);
    if (!node) return;

    mavlink_attitude_t attitude;
    mavlink_msg_attitude_decode(&message, &attitude);

    node->setParameter({ TelemetryId::Ahrs, TelemetryId::Pitch }, qRadiansToDegrees(attitude.pitch));
    node->setParameter({ TelemetryId::Ahrs, TelemetryId::Roll }, qRadiansToDegrees(attitude.roll));
    node->setParameter({ TelemetryId::Ahrs, TelemetryId::Yaw }, qRadiansToDegrees(attitude.yaw));
    node->setParameter({ TelemetryId::Ahrs, TelemetryId::PitchSpeed }, qRadiansToDegrees(attitude.pitchspeed));
    node->setParameter({ TelemetryId::Ahrs, TelemetryId::RollSpeed }, qRadiansToDegrees(attitude.rollspeed));
    node->setParameter({ TelemetryId::Ahrs, TelemetryId::YawSpeed }, qRadiansToDegrees(attitude.yawspeed));

    node->notify();
}
