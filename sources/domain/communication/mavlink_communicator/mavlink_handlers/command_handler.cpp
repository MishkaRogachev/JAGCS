#include "command_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "mavlink_communicator.h"

#include "vehicle_service.h"
#include "base_vehicle.h"

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

void CommandHandler::sendArmDisarm(bool arm)
{
    auto vehicle = qobject_cast<domain::BaseVehicle*>(this->sender());
    if (!vehicle) return;

    mavlink_message_t message;
    mavlink_command_long_t command;

    command.target_system = vehicle->vehicleId();
    command.target_component = 0;
    command.confirmation = 0;

    command.command = MAV_CMD_COMPONENT_ARM_DISARM;

    command.param1 = arm;

    mavlink_msg_command_long_encode(m_communicator->systemId(),
                                    m_communicator->componentId(),
                                    &message, &command);
    m_communicator->sendMessageAllLinks(message);
}

void CommandHandler::sendReturn()
{
    auto vehicle = qobject_cast<domain::BaseVehicle*>(this->sender());
    if (!vehicle) return;

    mavlink_message_t message;
    mavlink_command_long_t command;

    command.target_system = vehicle->vehicleId();
    command.target_component = 0;
    command.confirmation = 0;

    command.command = MAV_CMD_NAV_RETURN_TO_LAUNCH;

    mavlink_msg_command_long_encode(m_communicator->systemId(),
                                    m_communicator->componentId(),
                                    &message, &command);
    m_communicator->sendMessageAllLinks(message);
}

void CommandHandler::sendMissionStart(int startPoint)
{
    auto vehicle = qobject_cast<domain::AbstractVehicle*>(this->sender());
    if (!vehicle) return;

    mavlink_message_t message;
    mavlink_command_long_t command;

    command.target_system = vehicle->vehicleId();
    command.target_component = 0;
    command.confirmation = 0;

    command.command = MAV_CMD_MISSION_START;

    command.param1 = startPoint;
    command.param2 = vehicle->missionItems() - 1;

    mavlink_msg_command_long_encode(m_communicator->systemId(),
                                    m_communicator->componentId(),
                                    &message, &command);
    m_communicator->sendMessageAllLinks(message);
}

void CommandHandler::onVehicleAdded(AbstractVehicle* vehicle)
{
    connect(vehicle, &AbstractVehicle::commandReturn,
            this, &CommandHandler::sendReturn);
    connect(vehicle, &AbstractVehicle::commandJumpTo,
            this, &CommandHandler::sendMissionStart);

    auto baseVehicle = qobject_cast<domain::BaseVehicle*>(vehicle);
    {
        connect(baseVehicle, &BaseVehicle::commandArmDisarm,
                this, &CommandHandler::sendArmDisarm);
    }
}

void CommandHandler::onVehicleRemoved(AbstractVehicle* vehicle)
{
    disconnect(vehicle, 0, this, 0);
}
