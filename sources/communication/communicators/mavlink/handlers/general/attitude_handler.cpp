#include "attitude_handler.h"

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

AttitudeHandler::AttitudeHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(ServiceRegistry::telemetryService())
{}

void AttitudeHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_ATTITUDE) return;

    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_attitude_t attitude;
    mavlink_msg_attitude_decode(&message, &attitude);

    portion.setParameter({ Telemetry::Ahrs, Telemetry::Pitch }, qRadiansToDegrees(attitude.pitch));
    portion.setParameter({ Telemetry::Ahrs, Telemetry::Roll }, qRadiansToDegrees(attitude.roll));
    portion.setParameter({ Telemetry::Ahrs, Telemetry::Yaw }, qRadiansToDegrees(attitude.yaw));
    portion.setParameter({ Telemetry::Ahrs, Telemetry::PitchSpeed }, qRadiansToDegrees(attitude.pitchspeed));
    portion.setParameter({ Telemetry::Ahrs, Telemetry::RollSpeed }, qRadiansToDegrees(attitude.rollspeed));
    portion.setParameter({ Telemetry::Ahrs, Telemetry::YawSpeed }, qRadiansToDegrees(attitude.yawspeed));
}
