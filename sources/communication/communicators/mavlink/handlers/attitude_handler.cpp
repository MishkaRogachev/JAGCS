#include "attitude_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QtMath>
#include <QVariant>
#include <QDebug>

// Internal
#include "telemetry_service.h"
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

    Telemetry* node = m_telemetryService->nodeByMavId(message.sysid);
    if (!node) return;

    mavlink_attitude_t attitude;
    mavlink_msg_attitude_decode(&message, &attitude);

    node->setParameter({ Telemetry::Ahrs, Telemetry::Pitch }, qRadiansToDegrees(attitude.pitch));
    node->setParameter({ Telemetry::Ahrs, Telemetry::Roll }, qRadiansToDegrees(attitude.roll));
    node->setParameter({ Telemetry::Ahrs, Telemetry::Yaw }, qRadiansToDegrees(attitude.yaw));
    node->setParameter({ Telemetry::Ahrs, Telemetry::PitchSpeed }, qRadiansToDegrees(attitude.pitchspeed));
    node->setParameter({ Telemetry::Ahrs, Telemetry::RollSpeed }, qRadiansToDegrees(attitude.rollspeed));
    node->setParameter({ Telemetry::Ahrs, Telemetry::YawSpeed }, qRadiansToDegrees(attitude.yawspeed));

    node->notify();
}
