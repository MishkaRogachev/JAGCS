#include "vibration_handler.h"

// SwarmLink
#include <swarmlink/mavlink.h>

// Qt
#include <QVariant>
#include <QVector3D>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

using namespace comm;
using namespace domain;

VibrationHandler::VibrationHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(serviceRegistry->telemetryService())
{}

void VibrationHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_VIBRATION) return;

    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_vibration_t vibration;
    mavlink_msg_vibration_decode(&message, &vibration);

    portion.setParameter({ Telemetry::Ahrs, Telemetry::Vibration },
                         QVector3D(vibration.vibration_x,
                                   vibration.vibration_y,
                                   vibration.vibration_z));
}
