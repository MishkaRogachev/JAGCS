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

    node->setParameter({ telemetry::ahrs, telemetry::pitch }, qRadiansToDegrees(attitude.pitch));
    node->setParameter({ telemetry::ahrs, telemetry::roll }, qRadiansToDegrees(attitude.roll));
    node->setParameter({ telemetry::ahrs, telemetry::yaw }, qRadiansToDegrees(attitude.yaw));
    node->setParameter({ telemetry::ahrs, telemetry::pitchspeed }, qRadiansToDegrees(attitude.pitchspeed));
    node->setParameter({ telemetry::ahrs, telemetry::rollspeed }, qRadiansToDegrees(attitude.rollspeed));
    node->setParameter({ telemetry::ahrs, telemetry::yawspeed }, qRadiansToDegrees(attitude.yawspeed));

    node->notify();
}
