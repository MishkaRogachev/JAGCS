#include "command_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"

#include "command_service.h"

#include "telemetry_service.h"
#include "telemetry_portion.h"

#include "vehicle_service.h"
#include "vehicle.h"

#include "mavlink_communicator.h"
#include "mode_helper_factory.h"


using namespace comm;

namespace
{
    const QMap<quint16, dto::Command::CommandType> mavCommandLongMap =
    {
        { MAV_CMD_COMPONENT_ARM_DISARM, dto::Command::ArmDisarm },
        { MAV_CMD_NAV_RETURN_TO_LAUNCH, dto::Command::Return },
        { MAV_CMD_MISSION_START, dto::Command::Start },
        { MAV_CMD_DO_LAND_START, dto::Command::Land },
        { MAV_CMD_DO_GO_AROUND, dto::Command::GoAround },
        { MAV_CMD_DO_PAUSE_CONTINUE, dto::Command::PauseContinue },
        { MAV_CMD_DO_PARACHUTE, dto::Command::Parachute },

        // TODO: MAV_CMD_DO_SET_ROI, MAV_CMD_DO_MOUNT_CONTROL, MAV_CMD_DO_DIGICAM_CONTROL, MAV_CMD_NAV_LOITER_UNLIM
    };

    const QMultiMap<quint8, dto::Command::CommandStatus> mavStatusMap =
    {
        { MAV_RESULT_DENIED, dto::Command::Rejected },
        { MAV_RESULT_TEMPORARILY_REJECTED, dto::Command::Rejected },
        { MAV_RESULT_UNSUPPORTED, dto::Command::Rejected },
        { MAV_RESULT_FAILED, dto::Command::Rejected },
        { MAV_RESULT_IN_PROGRESS, dto::Command::InProgress },
        { MAV_RESULT_ACCEPTED, dto::Command::Completed }
    };

    int toMavLinkImpact(float value)
    {
        return qIsNaN(value) ? std::numeric_limits<std::int32_t>::max() : value * 1000;
    }
}

class CommandHandler::Impl
{
public:
    domain::VehicleService* vehicleService = serviceRegistry->vehicleService();
    domain::TelemetryService* telemetryService = serviceRegistry->telemetryService();

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
    QMap<quint8, QSharedPointer<IModeHelper> > modeHelpers;
};

CommandHandler::CommandHandler(MavLinkCommunicator* communicator):
    AbstractCommandHandler(communicator),
    AbstractMavLinkHandler(communicator),
    d(new Impl())
{
    serviceRegistry->commandService()->addHandler(this);

    connect(d->vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &CommandHandler::onVehicleRemoved);
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

    int vehicleId = d->vehicleService->vehicleIdByMavId(message.sysid);

    switch (ack.command)
    {
    case MAV_CMD_DO_CHANGE_SPEED:
        // FIXME: separae ack on speed commands
        this->ackCommand(vehicleId, dto::Command::SetAirspeed,
                         ::mavStatusMap.value(ack.result, dto::Command::Idle));
        this->ackCommand(vehicleId, dto::Command::SetGroundspeed,
                         ::mavStatusMap.value(ack.result, dto::Command::Idle));
        this->ackCommand(vehicleId, dto::Command::SetThrottle,
                         ::mavStatusMap.value(ack.result, dto::Command::Idle));
        break;
    case MAV_CMD_PREFLIGHT_CALIBRATION:
        this->ackCommand(vehicleId, dto::Command::CalibrateAirspeed,
                         ::mavStatusMap.value(ack.result, dto::Command::Idle));
        this->ackCommand(vehicleId, dto::Command::CalibrateReferencePressure,
                         ::mavStatusMap.value(ack.result, dto::Command::Idle));
        this->ackCommand(vehicleId, dto::Command::CalibrateTemperature,
                         ::mavStatusMap.value(ack.result, dto::Command::Idle));
        break;
    case MAV_CMD_DO_SET_HOME:
        this->ackCommand(vehicleId, dto::Command::SetReturn,
                         ::mavStatusMap.value(ack.result, dto::Command::Idle));
    default:
        break;
    }

    dto::Command::CommandType type = ::mavCommandLongMap.value(
                                         ack.command, dto::Command::UnknownCommand);
    if (type == dto::Command::UnknownCommand) return;

    this->ackCommand(vehicleId, type, ::mavStatusMap.value(ack.result, dto::Command::Idle));
}

void CommandHandler::processHeartbeat(const mavlink_message_t& message)
{
    mavlink_heartbeat_t heartbeat;
    mavlink_msg_heartbeat_decode(&message, &heartbeat);

    domain::TelemetryPortion portion(d->telemetryService->mavNode(message.sysid));

    if (d->modeHelpers.value(message.sysid).isNull())
    {
        ModeHelperFactory f;
        d->modeHelpers[message.sysid].reset(f.create(heartbeat.autopilot, heartbeat.type));

        if (d->modeHelpers[message.sysid])
        {
            portion.setParameter({ domain::Telemetry::System, domain::Telemetry::AvailableModes },
                                 qVariantFromValue(d->modeHelpers[message.sysid]->availableModes()));
        }
    }

    if (d->modeHelpers[message.sysid])
    {
        portion.setParameter({ domain::Telemetry::System, domain::Telemetry::Mode },
                             QVariant::fromValue(d->modeHelpers[message.sysid]->customModeToMode(
                                 heartbeat.custom_mode)));
    }

    d->modes[message.sysid].baseMode = heartbeat.base_mode;
    d->modes[message.sysid].customMode = heartbeat.custom_mode;

    if (d->modes[message.sysid].isObtained())
    {
        this->ackCommand(d->vehicleService->vehicleIdByMavId(message.sysid),
                         dto::Command::SetMode, dto::Command::Completed);
        d->modes[message.sysid].requestedCustomMode = -1;
    }
}

void CommandHandler::sendCommand(int vehicleId, const dto::CommandPtr& command, int attempt)
{
    qDebug() << "MAV:" << vehicleId << command->type() << command->arguments() << attempt;

    dto::VehiclePtr vehicle = d->vehicleService->vehicle(vehicleId);
    if (vehicle.isNull()) return;

    // TODO: to common command sender
    if (::mavCommandLongMap.values().contains(command->type()))
    {
        this->sendCommandLong(vehicle->mavId(), ::mavCommandLongMap.key(command->type()),
                              command->arguments(), attempt);
        return;
    }

    QVariantList args = command->arguments();
    switch (command->type())  // TODO: special command sender classes
    {
    case dto::Command::SetMode:
            this->sendSetMode(vehicle->mavId(), args.value(0).value<domain::vehicle::Mode>());
        break;
    case dto::Command::GoTo:
            this->sendCurrentItem(vehicle->mavId(), args.value(0, 0).toInt());
        break;
    case dto::Command::NavTo:
        this->sendNavTo(vehicle->mavId(), args.value(0, 0).toDouble(),
                        args.value(1, 0).toDouble(), args.value(2, 0).toFloat());
        break;
    case dto::Command::SetReturn:
        this->sendCommandLong(vehicle->mavId(), MAV_CMD_DO_SET_HOME,
                              { args.isEmpty() ? 1 : 0, 0, 0, 0, args.value(0, 0).toDouble(),
                                args.value(1, 0).toDouble(), args.value(2, 0).toFloat() }, attempt);
        break;
    case dto::Command::SetAltitude:
        this->sendSetAltitude(vehicle->mavId(), args.value(0, 0).toFloat());
        break;
    case dto::Command::SetLoiterRadius:
        this->sendSetLoiterRadius(vehicle->mavId(), args.value(0, 0).toFloat());
        break;
    case dto::Command::SetAirspeed:
        this->sendCommandLong(vehicle->mavId(), MAV_CMD_DO_CHANGE_SPEED,
                              { 0, args.value(0, 0).toFloat(), -1, 0 }, attempt);
        break;
    case dto::Command::SetGroundspeed:
        this->sendCommandLong(vehicle->mavId(), MAV_CMD_DO_CHANGE_SPEED,
                              { 1, args.value(0, 0).toFloat(), -1, 0 }, attempt);
        break;
    case dto::Command::SetThrottle:
        this->sendCommandLong(vehicle->mavId(), MAV_CMD_DO_CHANGE_SPEED,
                              { 0, -1, args.value(0, 0).toInt(), 0 }, attempt);
        break;
    case dto::Command::ManualImpacts:
        this->sendManualControl(vehicle->mavId(), args.value(0, 0).toFloat(),
                                args.value(1, 0).toFloat(), args.value(2, 0).toFloat(),
                                args.value(3, 0).toFloat());
        break;
    case dto::Command::CalibrateAirspeed:
        this->sendCommandLong(vehicle->mavId(), MAV_CMD_PREFLIGHT_CALIBRATION,
                              { 0, 0, 0, 0, 0, 2, 0 }, attempt);
        break;
    case dto::Command::CalibrateTemperature:
        this->sendCommandLong(vehicle->mavId(), MAV_CMD_PREFLIGHT_CALIBRATION,
                              { 3, 0, 0, 0, 3, 0, 3 }, attempt);
        break;
    case dto::Command::CalibrateReferencePressure:
        this->sendCommandLong(vehicle->mavId(), MAV_CMD_PREFLIGHT_CALIBRATION,
                              { 0, 0, 1, 0, 0, 0, 0 }, attempt);
        break;
    default:
        break;
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
    if (d->modeHelpers.value(mavId).isNull()) return;

    mavlink_message_t message;
    mavlink_set_mode_t setMode;

    setMode.target_system = mavId;
    setMode.base_mode = d->modes[mavId].baseMode;

    d->modes[mavId].requestedCustomMode = d->modeHelpers[mavId]->modeToCustomMode(mode);
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
                     dto::Command::GoTo, dto::Command::Completed); // TODO: wait current item
}

void CommandHandler::sendNavTo(quint8 mavId, double latitude, double longitude, float altitude)
{
    mavlink_message_t message;
    mavlink_mission_item_t item;

    item.param1 = 0;
    item.param2 = 0;
    item.param3 = 0;
    item.param4 = 0;
    item.target_system = mavId;
    item.target_component = MAV_COMP_ID_MISSIONPLANNER;
    item.frame = MAV_FRAME_GLOBAL_RELATIVE_ALT;
    item.command = MAV_CMD_NAV_WAYPOINT;
    item.current = 2; // guided
    item.seq = 0;
    item.autocontinue = false;
    item.x = static_cast<float>(latitude);
    item.y = static_cast<float>(longitude);
    item.z = altitude;

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_msg_mission_item_encode_chan(m_communicator->systemId(),
                                         m_communicator->componentId(),
                                         m_communicator->linkChannel(link),
                                         &message, &item);
    m_communicator->sendMessage(message, link);

    // TODO: wait mission ack
    this->ackCommand(d->vehicleService->vehicleIdByMavId(mavId),
                     dto::Command::NavTo, dto::Command::Completed);
}

void CommandHandler::sendSetAltitude(quint8 mavId, float altitude)
{
    mavlink_message_t message;
    mavlink_mission_item_t item;

    item.target_system = mavId;
    item.target_component = MAV_COMP_ID_MISSIONPLANNER;
    item.frame = MAV_FRAME_GLOBAL_RELATIVE_ALT;
    item.command = MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT;
    item.current = 3; // guided
    item.seq = 0;
    item.autocontinue = false;
    item.z = altitude;
    item.param1 = 0;

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_msg_mission_item_encode_chan(m_communicator->systemId(),
                                         m_communicator->componentId(),
                                         m_communicator->linkChannel(link),
                                         &message, &item);
    m_communicator->sendMessage(message, link);

    // TODO: wait mission ack
    this->ackCommand(d->vehicleService->vehicleIdByMavId(mavId),
                     dto::Command::SetAltitude, dto::Command::Completed);
}

void CommandHandler::sendSetLoiterRadius(quint8 mavId, float radius)
{
     mavlink_param_set_t setParam;

     setParam.target_system = mavId;
     strncpy(setParam.param_id, "WP_LOITER_RAD", sizeof("WP_LOITER_RAD")); //LOITER_RAD
     setParam.param_value = radius;

     AbstractLink* link = m_communicator->mavSystemLink(mavId);
     if (!link) return;

     mavlink_message_t message;
     mavlink_msg_param_set_encode_chan(m_communicator->systemId(),
                                       m_communicator->componentId(),
                                       m_communicator->linkChannel(link),
                                       &message, &setParam);
     m_communicator->sendMessage(message, link);

     // TODO: wait ack
     this->ackCommand(d->vehicleService->vehicleIdByMavId(mavId),
                      dto::Command::SetLoiterRadius
                      , dto::Command::Completed);
}

void CommandHandler::sendManualControl(quint8 mavId, float pitch, float roll,
                                       float yaw, float thrust)
{
    mavlink_manual_control_t mavlink_manual_control;

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

    // TODO: wait ack
    this->ackCommand(d->vehicleService->vehicleIdByMavId(mavId),
                     dto::Command::ManualImpacts, dto::Command::Completed);
}

void CommandHandler::onVehicleRemoved(const dto::VehiclePtr& vehicle)
{
    d->modeHelpers.remove(vehicle->mavId());
}

