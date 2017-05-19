#include "command_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "vehicle_description.h"
#include "mavlink_communicator.h"

#include "vehicle_service.h"
#include "base_vehicle.h"

using namespace comm;
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
    auto vehicle = qobject_cast<BaseVehicle*>(this->sender());
    if (!vehicle) return;

    mavlink_message_t message;
    mavlink_command_long_t command;

    command.target_system = vehicle->mavId();
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
    auto vehicle = qobject_cast<BaseVehicle*>(this->sender());
    if (!vehicle) return;

    mavlink_message_t message;
    mavlink_command_long_t command;

    command.target_system = vehicle->mavId();
    command.target_component = 0;
    command.confirmation = 0;

    command.command = MAV_CMD_NAV_RETURN_TO_LAUNCH;

    mavlink_msg_command_long_encode(m_communicator->systemId(),
                                    m_communicator->componentId(),
                                    &message, &command);
    m_communicator->sendMessageAllLinks(message);
}

void CommandHandler::sendMissionRestart()
{
    this->sendMissionStart(1);
}

void CommandHandler::sendMissionStart(int startPoint)
{
    auto vehicle = qobject_cast<BaseVehicle*>(this->sender());
    if (!vehicle) return;

    mavlink_message_t message;
    mavlink_command_long_t command;

    command.target_system = vehicle->mavId();
    command.target_component = 0;
    command.confirmation = 0;

    command.command = MAV_CMD_MISSION_START;

    command.param1 = startPoint;
    //TODO: command.param2 = vehicle->missionItems() - 1;

    mavlink_msg_command_long_encode(m_communicator->systemId(),
                                    m_communicator->componentId(),
                                    &message, &command);
    m_communicator->sendMessageAllLinks(message);
}

void CommandHandler::sendMissionJumpTo(int startPoint)
{
    auto vehicle = qobject_cast<BaseVehicle*>(this->sender());
    if (!vehicle) return;

    mavlink_message_t message;
    mavlink_command_long_t command;

    command.target_system = vehicle->mavId();
    command.target_component = 0;
    command.confirmation = 0;

    command.command = MAV_CMD_DO_JUMP;

    command.param1 = startPoint;

    mavlink_msg_command_long_encode(m_communicator->systemId(),
                                    m_communicator->componentId(),
                                    &message, &command);
    m_communicator->sendMessageAllLinks(message);
}

void CommandHandler::onVehicleAdded(
        const db::VehicleDescriptionPtr& description)
{
    BaseVehicle* vehicle = m_vehicleService->baseVehicle(description);

    connect(vehicle, &BaseVehicle::commandReturn,
            this, &CommandHandler::sendReturn);
    connect(vehicle, &BaseVehicle::commandStartMission,
            this, &CommandHandler::sendMissionStart);
    connect(vehicle, &BaseVehicle::commandJumpToMission,
            this, &CommandHandler::sendMissionJumpTo);
    connect(vehicle, &BaseVehicle::commandArmDisarm,
            this, &CommandHandler::sendArmDisarm);
}
