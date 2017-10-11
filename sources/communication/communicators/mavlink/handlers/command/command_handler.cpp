#include "command_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"

#include "command_service.h"
#include "command_sender.h"

#include "vehicle_service.h"
#include "vehicle.h"

#include "mavlink_communicator.h"

using namespace comm;
using namespace domain;

namespace
{
    const QMap<quint16, Command::CommandType> mavCommandMap =
    {
        { MAV_CMD_COMPONENT_ARM_DISARM, Command::ArmDisarm },
        { MAV_CMD_NAV_RETURN_TO_LAUNCH, Command::Return },
        { MAV_CMD_NAV_GUIDED_ENABLE, Command::EnableGuided },
        { MAV_CMD_MISSION_START, Command::Start },
        { MAV_CMD_DO_LAND_START, Command::Land },
        { MAV_CMD_DO_GO_AROUND, Command::GoAround },
        { MAV_CMD_DO_PAUSE_CONTINUE, Command::PauseContinue },
        { MAV_CMD_DO_PARACHUTE, Command::Parachute },
        { MAV_CMD_DO_CHANGE_SPEED, Command::SetSpeed },
        { MAV_CMD_DO_CHANGE_ALTITUDE, Command::SetAltitude },
        { MAV_CMD_DO_SET_HOME, Command::SetHome },
        { MAV_CMD_PREFLIGHT_CALIBRATION, Command::PreflightCalibration }
        // TODO: MAV_CMD_DO_SET_ROI, MAV_CMD_DO_MOUNT_CONTROL, MAV_CMD_DO_DIGICAM_CONTROL, MAV_CMD_NAV_LOITER_UNLIM
    };

    const QMultiMap<quint8, Command::CommandStatus> mavStatusMap =
    {
        { MAV_RESULT_DENIED, Command::Rejected },
        { MAV_RESULT_TEMPORARILY_REJECTED, Command::Rejected },
        { MAV_RESULT_UNSUPPORTED, Command::Rejected },
        { MAV_RESULT_FAILED, Command::Rejected },
        { MAV_RESULT_IN_PROGRESS, Command::InProgress },
        { MAV_RESULT_ACCEPTED, Command::Completed }
    };
}

CommandHandler::CommandHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_commandService(ServiceRegistry::commandService()),
    m_vehicleService(ServiceRegistry::vehicleService())
{
    connect(m_commandService->sender(), &CommandSender::sendCommand,
            this, &CommandHandler::onSendCommand);
}

void CommandHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_COMMAND_ACK) return;

    mavlink_command_ack_t ack;
    mavlink_msg_command_ack_decode(&message, &ack);

    Command::CommandType type = ::mavCommandMap.value(ack.command, Command::UnknownCommand);
    if (type == Command::UnknownCommand) return;

    Command::CommandStatus status = ::mavStatusMap.value(ack.result, Command::Idle);

    QMetaObject::invokeMethod(m_commandService->sender(), "setCommandStatus", Qt::QueuedConnection,
                              Q_ARG(Command::CommandType, type), Q_ARG(Command::CommandStatus, status));
}

void CommandHandler::onSendCommand(const Command& command, int attempt)
{
    qDebug() << command.type() << command.arguments() << attempt;

    dao::VehiclePtr vehicle = m_vehicleService->vehicle(command.vehicleId());
    if (vehicle.isNull()) return;

    mavlink_message_t message;
    mavlink_command_long_t mavCommand;

    mavCommand.target_system = vehicle->mavId();
    mavCommand.target_component = 0;
    mavCommand.confirmation = attempt;
    mavCommand.command = ::mavCommandMap.key(command.type());

    QVariantList args = command.arguments();
    if (args.count() > 0) mavCommand.param1 = args.at(0).toFloat();
    if (args.count() > 1) mavCommand.param2 = args.at(1).toFloat();
    if (args.count() > 2) mavCommand.param3 = args.at(2).toFloat();
    if (args.count() > 3) mavCommand.param4 = args.at(3).toFloat();
    if (args.count() > 4) mavCommand.param5 = args.at(4).toFloat();
    if (args.count() > 5) mavCommand.param6 = args.at(5).toFloat();
    if (args.count() > 6) mavCommand.param7 = args.at(6).toFloat();

    AbstractLink* link = m_communicator->mavSystemLink(vehicle->mavId());
    if (!link) return;

    mavlink_msg_command_long_encode_chan(m_communicator->systemId(),
                                         m_communicator->componentId(),
                                         m_communicator->linkChannel(link),
                                         &message, &mavCommand);
    m_communicator->sendMessage(message, link);
}
