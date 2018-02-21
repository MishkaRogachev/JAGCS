#include "manual_control_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "vehicle_service.h"
#include "command_service.h"

#include "mavlink_communicator.h"

namespace
{
    int normalize(float value)
    {
        return value * 1000;
    }
}

using namespace comm;

ManualControlHandler::ManualControlHandler(MavLinkCommunicator* communicator):
    AbstractCommandHandler(communicator),
    AbstractMavLinkHandler(communicator),
    m_vehicleService(domain::ServiceRegistry::vehicleService())
{
    domain::ServiceRegistry::commandService()->addHandler(this);
}

void ManualControlHandler::processMessage(const mavlink_message_t& message)
{
    Q_UNUSED(message) // TODO: handle feedback
}

void ManualControlHandler::sendManualControl(int vehicledId, float pitch, float roll,
                                             float yaw, float thrust)
{
    qDebug() << "manual:" << pitch << roll << yaw << thrust;

    mavlink_manual_control_t mavlink_manual_control;

    int mavId = m_vehicleService->mavIdByVehicleId(vehicledId);
    mavlink_manual_control.target = mavId;

    mavlink_manual_control.x = ::normalize(pitch);
    mavlink_manual_control.y = ::normalize(roll);
    mavlink_manual_control.r = ::normalize(yaw);
    mavlink_manual_control.z = ::normalize(thrust);

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_message_t message;
    mavlink_msg_manual_control_encode_chan(m_communicator->systemId(),
                                           m_communicator->componentId(),
                                           m_communicator->linkChannel(link),
                                           &message, &mavlink_manual_control);
    m_communicator->sendMessage(message, link);
}

void ManualControlHandler::sendCommand(int vehicleId, const dao::CommandPtr& command, int attempt)
{
    Q_UNUSED(attempt)

    if (command->type() != dao::Command::ManualImpacts) return;

    this->sendManualControl(vehicleId,
                            command->arguments().value(0, 0).toFloat(),
                            command->arguments().value(1, 0).toFloat(),
                            command->arguments().value(2, 0).toFloat(),
                            command->arguments().value(3, 0).toFloat());
    // TODO: wait feedback
    this->ackCommand(vehicleId, dao::Command::ManualImpacts, dao::Command::Completed);
}

