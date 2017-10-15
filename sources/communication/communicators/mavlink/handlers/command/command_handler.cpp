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
#include "mode_helper_factory.h"

using namespace comm;
using namespace domain;

namespace
{
    const QMap<quint16, Command::CommandType> mavCommandLongMap =
    {
        { MAV_CMD_COMPONENT_ARM_DISARM, Command::ArmDisarm },
        { MAV_CMD_NAV_RETURN_TO_LAUNCH, Command::Return },
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

class CommandHandler::Impl
{
public:
    VehicleService* vehicleService = ServiceRegistry::vehicleService();
    CommandService* commandService = ServiceRegistry::commandService();

    QScopedPointer<IModeHelper> modeHelper;
    quint8 baseMode = 0;
    int customMode = -1;
    int requestedCustomMode = -1;

    void ackCommand(Command::CommandType type, Command::CommandStatus status)
    {
        QMetaObject::invokeMethod(commandService->sender(), "setCommandStatus",
                                  Qt::QueuedConnection,
                                  Q_ARG(Command::CommandType, type),
                                  Q_ARG(Command::CommandStatus, status));
    }
};

CommandHandler::CommandHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    d(new Impl())
{
    connect(d->commandService->sender(), &CommandSender::sendCommand,
            this, &CommandHandler::onSendCommand);
}

CommandHandler::~CommandHandler()
{}

void CommandHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid == MAVLINK_MSG_ID_COMMAND_ACK) this->processCommandAck(message);
    else if (message.msgid == MAVLINK_MSG_ID_HEARTBEAT) this->processHeartbeat(message);
}

void CommandHandler::processCommandAck(const mavlink_message_t& message)
{
    mavlink_command_ack_t ack;
    mavlink_msg_command_ack_decode(&message, &ack);

    Command::CommandType type = ::mavCommandLongMap.value(ack.command, Command::UnknownCommand);
    if (type == Command::UnknownCommand) return;

    d->ackCommand(type, ::mavStatusMap.value(ack.result, Command::Idle));
}

void CommandHandler::processHeartbeat(const mavlink_message_t& message)
{
    mavlink_heartbeat_t heartbeat;
    mavlink_msg_heartbeat_decode(&message, &heartbeat);

    if (d->modeHelper.isNull())
    {
        ModeHelperFactory f;
        d->modeHelper.reset(f.create(heartbeat.autopilot, heartbeat.type));
    }

    d->baseMode = heartbeat.base_mode;
    d->customMode = heartbeat.custom_mode;

    if (d->requestedCustomMode > -1 && d->requestedCustomMode == d->customMode)
    {
        d->ackCommand(Command::SetMode, Command::Completed);
        d->requestedCustomMode = -1;
    }
}

void CommandHandler::onSendCommand(const Command& command, int attempt)
{
    qDebug() << command.type() << command.arguments() << attempt;

    dao::VehiclePtr vehicle = d->vehicleService->vehicle(command.vehicleId());
    if (vehicle.isNull()) return;

    if (::mavCommandLongMap.values().contains(command.type()))
    {
        this->sendCommandLong(vehicle->mavId(),
                              ::mavCommandLongMap.key(command.type()),
                              command.arguments(), attempt);
        return;
    }

    if (command.arguments().count() < 1) return;

    if (command.type() == Command::SetMode) // TODO: special command map
    {
        this->sendSetMode(vehicle->mavId(), command.arguments().first().value<Mode>());
    }
    else if (command.type() == Command::GoToItem)
    {
        this->sendCurrentItem(vehicle->mavId(), command.arguments().first().toInt());
    }
    else if (command.type() == Command::NavTo)
    {
        QVariantList args = command.arguments();
        if (args.count() > 2)
        {
            this->sentNavTo(vehicle->mavId(),
                            args.at(0).toDouble(),
                            args.at(1).toDouble(),
                            args.at(2).toFloat());
        }
    }
}

void CommandHandler::sendCommandLong(quint8 mavId, quint16 commandId,
                                     const QVariantList& args, int attempt)
{
    mavlink_message_t message;
    mavlink_command_long_t mavCommand;

    mavCommand.target_system = mavId;
    mavCommand.target_component = 0;
    mavCommand.confirmation = attempt;
    mavCommand.command = commandId;

    if (args.count() > 0) mavCommand.param1 = args.at(0).toFloat();
    if (args.count() > 1) mavCommand.param2 = args.at(1).toFloat();
    if (args.count() > 2) mavCommand.param3 = args.at(2).toFloat();
    if (args.count() > 3) mavCommand.param4 = args.at(3).toFloat();
    if (args.count() > 4) mavCommand.param5 = args.at(4).toFloat();
    if (args.count() > 5) mavCommand.param6 = args.at(5).toFloat();
    if (args.count() > 6) mavCommand.param7 = args.at(6).toFloat();

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_msg_command_long_encode_chan(m_communicator->systemId(),
                                         m_communicator->componentId(),
                                         m_communicator->linkChannel(link),
                                         &message, &mavCommand);
    m_communicator->sendMessage(message, link);
}

void CommandHandler::sendSetMode(quint8 mavId, Mode mode)
{
    if (d->modeHelper.isNull()) return;

    mavlink_message_t message;
    mavlink_set_mode_t setMode;

    setMode.target_system = mavId;
    setMode.base_mode = d->baseMode;

    d->requestedCustomMode = d->modeHelper->modeToCustomMode(mode);
    if (d->requestedCustomMode < 0) return;

    setMode.custom_mode = d->requestedCustomMode;

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_msg_set_mode_encode_chan(m_communicator->systemId(),
                                     m_communicator->componentId(),
                                     m_communicator->linkChannel(link),
                                     &message, &setMode);
    m_communicator->sendMessage(message, link);
}

void CommandHandler::sendCurrentItem(quint8 mavId, quint16 seq)
{
    mavlink_message_t message;
    mavlink_mission_set_current_t current;

    current.target_system = mavId;
    current.target_component = MAV_COMP_ID_MISSIONPLANNER;
    current.seq = seq;

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_msg_mission_set_current_encode_chan(m_communicator->systemId(),
                                                m_communicator->componentId(),
                                                m_communicator->linkChannel(link),
                                                &message, &current);
    m_communicator->sendMessage(message, link);

    d->ackCommand(Command::GoToItem, Command::Completed); // TODO: wait current item
}

void CommandHandler::sentNavTo(quint8 mavId, double latitude, double longitude, float altitude)
{
    mavlink_message_t message;
    mavlink_mission_item_t item;

    item.target_system = mavId;
    item.target_component = MAV_COMP_ID_MISSIONPLANNER;
    item.frame = MAV_FRAME_GLOBAL_RELATIVE_ALT;
    item.command = MAV_CMD_NAV_WAYPOINT;
    item.current = 2; // guided
    item.seq = 0;
    item.autocontinue = false;
    item.x = latitude;
    item.y = longitude;
    item.z = altitude;

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_msg_mission_item_encode_chan(m_communicator->systemId(),
                                         m_communicator->componentId(),
                                         m_communicator->linkChannel(link),
                                         &message, &item);
    m_communicator->sendMessage(message, link);

    d->ackCommand(Command::NavTo, Command::Completed); // TODO: wait nav to
}
