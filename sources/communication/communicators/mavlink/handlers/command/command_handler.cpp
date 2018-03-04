#include "command_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"

#include "command_service.h"

#include "vehicle_service.h"
#include "vehicle.h"

#include "mavlink_communicator.h"
#include "mode_helper_factory.h"


using namespace comm;

namespace
{
    const QMap<quint16, dao::Command::CommandType> mavCommandLongMap =
    {
        { MAV_CMD_COMPONENT_ARM_DISARM, dao::Command::ArmDisarm },
        { MAV_CMD_NAV_RETURN_TO_LAUNCH, dao::Command::Return },
        { MAV_CMD_MISSION_START, dao::Command::Start },
        { MAV_CMD_DO_LAND_START, dao::Command::Land },
        { MAV_CMD_DO_GO_AROUND, dao::Command::GoAround },
        { MAV_CMD_DO_PAUSE_CONTINUE, dao::Command::PauseContinue },
        { MAV_CMD_DO_PARACHUTE, dao::Command::Parachute },
        { MAV_CMD_DO_CHANGE_SPEED, dao::Command::SetSpeed },
        { MAV_CMD_DO_CHANGE_ALTITUDE, dao::Command::SetAltitude },
        { MAV_CMD_DO_SET_HOME, dao::Command::SetHome },
        { MAV_CMD_PREFLIGHT_CALIBRATION, dao::Command::PreflightCalibration }
        // TODO: MAV_CMD_DO_SET_ROI, MAV_CMD_DO_MOUNT_CONTROL, MAV_CMD_DO_DIGICAM_CONTROL, MAV_CMD_NAV_LOITER_UNLIM
    };

    const QMultiMap<quint8, dao::Command::CommandStatus> mavStatusMap =
    {
        { MAV_RESULT_DENIED, dao::Command::Rejected },
        { MAV_RESULT_TEMPORARILY_REJECTED, dao::Command::Rejected },
        { MAV_RESULT_UNSUPPORTED, dao::Command::Rejected },
        { MAV_RESULT_FAILED, dao::Command::Rejected },
        { MAV_RESULT_IN_PROGRESS, dao::Command::InProgress },
        { MAV_RESULT_ACCEPTED, dao::Command::Completed }
    };

    int toMavLinkImpact(double value)
    {
        return qIsNaN(value) ? std::numeric_limits<std::int32_t>::max() : value * 1000;
    }
}

class CommandHandler::Impl
{
public:
    domain::VehicleService* vehicleService = domain::ServiceRegistry::vehicleService();

    QScopedPointer<IModeHelper> modeHelper;

    struct ModeAgregator
    {
        quint8 baseMode = 0;
        int customMode = -1;
        int requestedCustomMode = -1;

        bool isObtained()
        {
            return requestedCustomMode > -1 && requestedCustomMode == customMode;
        }
    };
    QMap<quint8, ModeAgregator> modes;
};

CommandHandler::CommandHandler(MavLinkCommunicator* communicator):
    AbstractCommandHandler(communicator),
    AbstractMavLinkHandler(communicator),
    d(new Impl())
{
    domain::ServiceRegistry::commandService()->addHandler(this);
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

    dao::Command::CommandType type = ::mavCommandLongMap.value(ack.command, dao::Command::UnknownCommand);
    if (type == dao::Command::UnknownCommand) return;

    this->ackCommand(d->vehicleService->vehicleIdByMavId(message.sysid),
                     type, ::mavStatusMap.value(ack.result, dao::Command::Idle));
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

    d->modes[message.sysid].baseMode = heartbeat.base_mode;
    d->modes[message.sysid].customMode = heartbeat.custom_mode;

    if (d->modes[message.sysid].isObtained())
    {
        this->ackCommand(d->vehicleService->vehicleIdByMavId(message.sysid),
                         dao::Command::SetMode, dao::Command::Completed);
        d->modes[message.sysid].requestedCustomMode = -1;
    }
}

void CommandHandler::sendCommand(int vehicleId, const dao::CommandPtr& command, int attempt)
{
    qDebug() << "MAV:" << vehicleId << command->type() << command->arguments() << attempt;

    dao::VehiclePtr vehicle = d->vehicleService->vehicle(vehicleId);
    if (vehicle.isNull()) return;

    if (::mavCommandLongMap.values().contains(command->type()))
    {
        this->sendCommandLong(vehicle->mavId(),
                              ::mavCommandLongMap.key(command->type()),
                              command->arguments(), attempt);
        return;
    }

    if (command->arguments().count() < 1) return;

    if (command->type() == dao::Command::SetMode) // TODO: special command map
    {
        this->sendSetMode(vehicle->mavId(),
                          command->arguments().first().value<domain::vehicle::Mode>());
    }
    else if (command->type() == dao::Command::GoTo)
    {
        this->sendCurrentItem(vehicle->mavId(), command->arguments().first().toInt());
    }
    else if (command->type() == dao::Command::NavTo)
    {
        QVariantList args = command->arguments();
        if (args.count() > 2)
        {
            this->sentNavTo(vehicle->mavId(),
                            args.at(0).toDouble(),
                            args.at(1).toDouble(),
                            args.at(2).toFloat());
        }
    }
    else if (command->type() == dao::Command::ManualImpacts)
    {
        this->sendManualControl(vehicleId,
                                command->arguments().value(0, 0).toFloat(),
                                command->arguments().value(1, 0).toFloat(),
                                command->arguments().value(2, 0).toFloat(),
                                command->arguments().value(3, 0).toFloat());
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

void CommandHandler::sendSetMode(quint8 mavId, domain::vehicle::Mode mode)
{
    if (d->modeHelper.isNull()) return;

    mavlink_message_t message;
    mavlink_set_mode_t setMode;

    setMode.target_system = mavId;
    setMode.base_mode = d->modes[mavId].baseMode;

    d->modes[mavId].requestedCustomMode = d->modeHelper->modeToCustomMode(mode);
    if (d->modes[mavId].requestedCustomMode < 0) return;

    setMode.custom_mode = d->modes[mavId].requestedCustomMode;

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

    this->ackCommand(d->vehicleService->vehicleIdByMavId(mavId),
                     dao::Command::GoTo, dao::Command::Completed); // TODO: wait current item
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

    this->ackCommand(d->vehicleService->vehicleIdByMavId(mavId),
                     dao::Command::NavTo, dao::Command::Completed); // TODO: wait nav to
}

void CommandHandler::sendManualControl(int vehicleId, double pitch, double roll,
                                       double yaw, double thrust)
{
    mavlink_manual_control_t mavlink_manual_control;

    int mavId = d->vehicleService->mavIdByVehicleId(vehicleId);
    mavlink_manual_control.target = mavId;

    mavlink_manual_control.x = ::toMavLinkImpact(pitch);
    mavlink_manual_control.y = ::toMavLinkImpact(roll);
    mavlink_manual_control.r = ::toMavLinkImpact(yaw);
    mavlink_manual_control.z = ::toMavLinkImpact(thrust);

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_message_t message;
    mavlink_msg_manual_control_encode_chan(m_communicator->systemId(),
                                           m_communicator->componentId(),
                                           m_communicator->linkChannel(link),
                                           &message, &mavlink_manual_control);
    m_communicator->sendMessage(message, link);

    // TODO: wait feedback
    this->ackCommand(vehicleId, dao::Command::ManualImpacts, dao::Command::Completed);
}
