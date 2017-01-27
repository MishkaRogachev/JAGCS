#include "command_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "mavlink_communicator.h"

#include "vehicle_service.h"
#include "vehicle.h"

using namespace domain;

CommandHandler::CommandHandler(VehicleService* vehicleService,
                               MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(vehicleService)
{
    connect(vehicleService, &VehicleService::vehicleAdded,
            this, &CommandHandler::onVehicleAdded);
}

void CommandHandler::processMessage(const mavlink_message_t& message)
{
    Q_UNUSED(message) // TODO: handle command quitantion
}

void CommandHandler::sendArmCommand(bool arm)
{
    domain::Vehicle* vehicle = qobject_cast<domain::Vehicle*>(this->sender());
    if (!vehicle) return;

    mavlink_message_t message;
    mavlink_command_long_t command;

    command.target_system = m_vehicleService->vehicleId(vehicle);
    command.target_component = 0;
    command.confirmation = 0;

    command.command = MAV_CMD_COMPONENT_ARM_DISARM;

    command.param1 = arm;

    mavlink_msg_command_long_encode(m_communicator->systemId(),
                                    m_communicator->componentId(),
                                    &message, &command);
    m_communicator->sendMessageAllLinks(message);
}

void CommandHandler::onVehicleAdded(Vehicle* vehicle)
{
    connect(vehicle, &Vehicle::commandArm,
            this, &CommandHandler::sendArmCommand);
}
