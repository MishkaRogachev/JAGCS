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

void CommandHandler::sendCommand(Command command, const QVariantList& args)
{
    domain::Vehicle* vehicle = qobject_cast<domain::Vehicle*>(this->sender());
    if (!vehicle) return;

    switch (command)
    {
    case Command::Arm:
        this->sendArmDisarm(vehicle->vehicleId(), true);
        break;
    case Command::Disarm:
        this->sendArmDisarm(vehicle->vehicleId(), false);
        break;
    case Command::Return:
        this->sendReturn(vehicle->vehicleId());
        break;
        // TODO: other commands
    default:
        qDebug() << "Not handled command" << int(command);
        break;
    }
}

void CommandHandler::sendArmDisarm(uint8_t id, bool arm)
{
    mavlink_message_t message;
    mavlink_command_long_t command;

    command.target_system = id;
    command.target_component = 0;
    command.confirmation = 0;

    command.command = MAV_CMD_COMPONENT_ARM_DISARM;

    command.param1 = arm;

    mavlink_msg_command_long_encode(m_communicator->systemId(),
                                    m_communicator->componentId(),
                                    &message, &command);
    m_communicator->sendMessageAllLinks(message);
}

void CommandHandler::sendReturn(uint8_t id)
{
    mavlink_message_t message;
    mavlink_command_long_t command;

    command.target_system = id;
    command.target_component = 0;
    command.confirmation = 0;

    command.command = MAV_CMD_NAV_RETURN_TO_LAUNCH;

    mavlink_msg_command_long_encode(m_communicator->systemId(),
                                    m_communicator->componentId(),
                                    &message, &command);
    m_communicator->sendMessageAllLinks(message);
}

void CommandHandler::onVehicleAdded(AbstractVehicle* vehicle)
{
    connect(vehicle, &Vehicle::executeCommand, this, &CommandHandler::sendCommand);
}

void CommandHandler::onVehicleRemoved(AbstractVehicle* vehicle)
{
    disconnect(vehicle, &Vehicle::executeCommand, this, &CommandHandler::sendCommand);
}
