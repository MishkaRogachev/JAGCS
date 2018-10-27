#include "mission_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QMap>
#include <QTimerEvent>
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "mission.h"
#include "mission_item.h"
#include "vehicle.h"
#include "mission_assignment.h"

#include "mavlink_communicator.h"

#include "service_registry.h"
#include "command_service.h"
#include "vehicle_service.h"
#include "mission_service.h"

#include "telemetry_service.h"
#include "telemetry_portion.h"

#include "notification_bus.h"

namespace
{
    const int interval = 2000;

    const QMap<quint16, dto::MissionItem::Command> mavCommandLongMap =
    {
        { MAV_CMD_NAV_TAKEOFF, dto::MissionItem::Takeoff },
        { MAV_CMD_NAV_LAND, dto::MissionItem::Landing },
        { MAV_CMD_NAV_WAYPOINT, dto::MissionItem::Waypoint },
        { MAV_CMD_NAV_LOITER_UNLIM, dto::MissionItem::LoiterUnlim },
        { MAV_CMD_NAV_LOITER_TO_ALT, dto::MissionItem::LoiterAltitude },
        { MAV_CMD_NAV_LOITER_TURNS, dto::MissionItem::LoiterTurns },
        { MAV_CMD_NAV_LOITER_TIME, dto::MissionItem::LoiterTime },
        { MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT, dto::MissionItem::Continue },
        { MAV_CMD_NAV_RETURN_TO_LAUNCH, dto::MissionItem::Return },

        { MAV_CMD_DO_CHANGE_SPEED, dto::MissionItem::SetSpeed },
        { MAV_CMD_DO_JUMP, dto::MissionItem::JumpTo },

        { MAV_CMD_DO_SET_SERVO, dto::MissionItem::SetServo },
        { MAV_CMD_DO_SET_RELAY, dto::MissionItem::SetRelay },
        { MAV_CMD_DO_REPEAT_SERVO, dto::MissionItem::RepeatServo },
        { MAV_CMD_DO_REPEAT_RELAY, dto::MissionItem::RepeatRelay },

        { MAV_CMD_DO_SET_ROI, dto::MissionItem::SetRoi },
        { MAV_CMD_DO_MOUNT_CONTROL, dto::MissionItem::MountControl },
        { MAV_CMD_DO_SET_CAM_TRIGG_DIST, dto::MissionItem::SetCameraTriggerDistance },
        { MAV_CMD_DO_DIGICAM_CONTROL, dto::MissionItem::CameraControl }
    };

    QString decodeCommandResult(int result)
    {
        switch (result) {
        case MAV_MISSION_ERROR:
            return qApp->translate("MissionHandler", "generic error");
        case MAV_MISSION_UNSUPPORTED_FRAME:
            return qApp->translate("MissionHandler", "coordinate frame is not supported");
        case MAV_MISSION_UNSUPPORTED:
            return qApp->translate("MissionHandler", "command is not supported");
        case MAV_MISSION_NO_SPACE:
            return qApp->translate("MissionHandler", "mission item exceeds storage space");
        case MAV_MISSION_INVALID:
        case MAV_MISSION_INVALID_PARAM1:
        case MAV_MISSION_INVALID_PARAM2:
        case MAV_MISSION_INVALID_PARAM3:
        case MAV_MISSION_INVALID_PARAM4:
        case MAV_MISSION_INVALID_PARAM5_X:
        case MAV_MISSION_INVALID_PARAM6_Y:
        case MAV_MISSION_INVALID_PARAM7:
            return qApp->translate("MissionHandler", "invalid parameter(s)");
        case MAV_MISSION_INVALID_SEQUENCE:
            return qApp->translate("MissionHandler", "waypoint out of sequence");
        case MAV_MISSION_DENIED:
            return qApp->translate("MissionHandler", "not accepting any mission commands");
        default:
            return qApp->translate("MissionHandler", "unknown");
        }
    }
}

using namespace comm;
using namespace domain;

class MissionHandler::Impl
{
public:
    VehicleService* vehicleService = serviceRegistry->vehicleService();
    TelemetryService* telemetryService = serviceRegistry->telemetryService();
    MissionService* missionService = serviceRegistry->missionService();

    QMap <quint8, MissionHandler::Stage> mavStages;
    QMap <quint8, int> mavTimers;
    QMap <quint8, QList<int> > mavSequencer;
    int lastSendedSequence = -1;
};

MissionHandler::MissionHandler(MavLinkCommunicator* communicator):
    QObject(communicator),
    AbstractMavLinkHandler(communicator),
    d(new Impl())
{
    connect(d->missionService, &MissionService::download, this, &MissionHandler::download);
    connect(d->missionService, &MissionService::upload, this, &MissionHandler::upload);
    connect(d->missionService, &MissionService::cancelSync, this, &MissionHandler::cancelSync);
}

MissionHandler::~MissionHandler()
{}

void MissionHandler::processMessage(const mavlink_message_t& message)
{
    switch (message.msgid)
    {
    case MAVLINK_MSG_ID_MISSION_COUNT:
        this->processMissionCount(message);
        break;
    case MAVLINK_MSG_ID_MISSION_ITEM:
        this->processMissionItem(message);
        break;
    case MAVLINK_MSG_ID_MISSION_REQUEST:
        this->processMissionRequest(message);
        break;
    case MAVLINK_MSG_ID_MISSION_ACK:
        this->processMissionAck(message);
        break;
    case MAVLINK_MSG_ID_MISSION_CURRENT:
        this->processMissionCurrent(message);
        break;
    case MAVLINK_MSG_ID_MISSION_ITEM_REACHED:
        this->processMissionReached(message);
        break;
    default:
        break;
    }
}

void MissionHandler::download(const dto::MissionAssignmentPtr& assignment)
{
    dto::VehiclePtr vehicle = d->vehicleService->vehicle(assignment->vehicleId());
    if (vehicle.isNull()) return;

    assignment->setStatus(dto::MissionAssignment::Downloading);
    assignment->setProgress(0);
    d->missionService->assignmentChanged(assignment);

    this->enterStage(Stage::WaitingCount, vehicle->mavId());
    this->requestMissionCount(vehicle->mavId());
}

void MissionHandler::upload(const dto::MissionAssignmentPtr& assignment)
{
    dto::VehiclePtr vehicle = d->vehicleService->vehicle(assignment->vehicleId());
    if (vehicle.isNull()) return;

    d->mavSequencer[vehicle->mavId()].clear();
    for (const dto::MissionItemPtr& item: d->missionService->missionItems(assignment->missionId()))
    {
        d->mavSequencer[vehicle->mavId()].append(item->sequence());
        item->setStatus(dto::MissionItem::NotActual);
        d->missionService->missionItemChanged(item);
    }

    if (d->mavSequencer.isEmpty())
    {
        this->enterStage(Stage::Idle, vehicle->mavId());
    }
    else
    {
        assignment->setStatus(dto::MissionAssignment::Uploading);
        assignment->setProgress(0);
        d->missionService->assignmentChanged(assignment);

        d->lastSendedSequence = -1;
        this->enterStage(Stage::SendingCount, vehicle->mavId());
        this->sendMissionCount(vehicle->mavId());
    }
}

void MissionHandler::cancelSync(const dto::MissionAssignmentPtr& assignment)
{
    this->enterStage(Stage::Idle, d->vehicleService->mavIdByVehicleId(assignment->vehicleId()));

    assignment->setStatus(dto::MissionAssignment::NotActual);
    assignment->setProgress(0);
    d->missionService->assignmentChanged(assignment);
}

void MissionHandler::requestMissionCount(quint8 mavId)
{
    mavlink_message_t message;
    mavlink_mission_request_list_t request;

    request.target_system = mavId;
    request.target_component = MAV_COMP_ID_MISSIONPLANNER;

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_msg_mission_request_list_encode_chan(m_communicator->systemId(),
                                                 m_communicator->componentId(),
                                                 m_communicator->linkChannel(link),
                                                 &message, &request);
    m_communicator->sendMessage(message, link);
}

void MissionHandler::requestMissionItem(quint8 mavId, quint16 seq)
{
    dto::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(
                                               d->vehicleService->vehicleIdByMavId(mavId));
    if (assignment.isNull()) return;

    mavlink_message_t message;
    mavlink_mission_request_t missionRequest;

    missionRequest.target_system = mavId;
    missionRequest.target_component = MAV_COMP_ID_MISSIONPLANNER;
    missionRequest.seq = seq;

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_msg_mission_request_encode_chan(m_communicator->systemId(),
                                            m_communicator->componentId(),
                                            m_communicator->linkChannel(link),
                                            &message, &missionRequest);
    m_communicator->sendMessage(message, link);
}

void MissionHandler::sendMissionCount(quint8 mavId)
{
    dto::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(
                                               d->vehicleService->vehicleIdByMavId(mavId));
    if (assignment.isNull()) return;

    dto::MissionPtr mission = d->missionService->mission(assignment->missionId());

    mavlink_message_t message;
    mavlink_mission_count_t countMessage;

    countMessage.target_system = mavId;
    countMessage.target_component = MAV_COMP_ID_MISSIONPLANNER;
    countMessage.count = mission->count();

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_msg_mission_count_encode_chan(m_communicator->systemId(),
                                          m_communicator->componentId(),
                                          m_communicator->linkChannel(link),
                                          &message, &countMessage);
    m_communicator->sendMessage(message, link);
}

void MissionHandler::sendMissionItem(quint8 mavId, quint16 seq)
{
    int vehicleId = d->vehicleService->vehicleIdByMavId(mavId);
    dto::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_message_t message;
    mavlink_mission_item_t msgItem;

    msgItem.target_system = mavId;
    msgItem.target_component = MAV_COMP_ID_MISSIONPLANNER;

    // TODO: mission item to message convertor class
    dto::MissionItemPtr item = d->missionService->missionItem(assignment->missionId(), seq);
    if (item.isNull()) return;

    msgItem.seq = seq;
    msgItem.autocontinue = seq < d->missionService->mission(assignment->missionId())->count() - 1;

    if (seq) msgItem.command = ::mavCommandLongMap.key(item->command(), 0);
    else msgItem.command = MAV_CMD_NAV_WAYPOINT; // Home is waypoint

    if (item->isAltitudedItem())
    {
        msgItem.frame = item->isAltitudeRelative() ? MAV_FRAME_GLOBAL_RELATIVE_ALT :
                                                      MAV_FRAME_GLOBAL;
        msgItem.z = item->altitude();
    }

    if (item->isPositionatedItem())
    {
        msgItem.x = static_cast<float>(item->latitude());
        msgItem.y = static_cast<float>(item->longitude());
    }

    msgItem.param1 = 0;
    msgItem.param2 = 0;
    msgItem.param3 = 0;
    msgItem.param4 = 0;

    if (msgItem.command == MAV_CMD_NAV_TAKEOFF)
    {
        msgItem.param1 = item->parameter(dto::MissionItem::Pitch).toFloat();
    }
    else if (msgItem.command == MAV_CMD_NAV_LAND)
    {
        msgItem.param1 = item->parameter(dto::MissionItem::AbortAltitude).toFloat();
        msgItem.param4 = item->parameter(dto::MissionItem::Yaw).toFloat();
    }
    else if (msgItem.command == MAV_CMD_NAV_WAYPOINT)
    {
        msgItem.param2 = item->parameter(dto::MissionItem::Radius).toFloat();
    }
    else if (msgItem.command == MAV_CMD_NAV_LOITER_UNLIM ||
             msgItem.command == MAV_CMD_NAV_LOITER_TURNS ||
             msgItem.command == MAV_CMD_NAV_LOITER_TIME)
    {
        msgItem.param3 = item->parameter(dto::MissionItem::Clockwise).toBool() ?
                             item->parameter(dto::MissionItem::Radius).toFloat() :
                             -1 * item->parameter(dto::MissionItem::Radius).toFloat();
        msgItem.param4 = item->parameter(dto::MissionItem::Yaw).toFloat();
    }
    else if (msgItem.command == MAV_CMD_NAV_LOITER_TO_ALT)
    {
        msgItem.param1 = item->parameter(dto::MissionItem::HeadingRequired).toBool();
        msgItem.param2 = item->parameter(dto::MissionItem::Clockwise).toBool() ?
                             item->parameter(dto::MissionItem::Radius).toFloat() :
                             -1 * item->parameter(dto::MissionItem::Radius).toFloat();
    }
    else if (msgItem.command == MAV_CMD_DO_CHANGE_SPEED)
    {
        msgItem.param1 = item->parameter(dto::MissionItem::IsGroundSpeed).toBool();
        msgItem.param2 = item->parameter(dto::MissionItem::Speed, -1).toFloat();
        msgItem.param3 = item->parameter(dto::MissionItem::Throttle, -1).toInt();
    }

    if (msgItem.command == MAV_CMD_NAV_LOITER_TURNS)
    {
        msgItem.param1 = item->parameter(dto::MissionItem::Repeats).toInt();
    }
    else if (msgItem.command == MAV_CMD_NAV_LOITER_TIME)
    {
        msgItem.param1 = item->parameter(dto::MissionItem::Time).toFloat();
    }

//    if (msgItem.command == MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT)
//    {
//  TODO: In Plane 3.4 (and later) the param1 value sets how close the vehicle
//        altitude must be to target altitude for command completion.
//    }

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_msg_mission_item_encode_chan(m_communicator->systemId(),
                                         m_communicator->componentId(),
                                         m_communicator->linkChannel(link),
                                         &message, &msgItem);
    m_communicator->sendMessage(message, link);

    item->setStatus(dto::MissionItem::Actual);
    d->lastSendedSequence = seq;
    d->missionService->missionItemChanged(item);

    if (d->mavStages[mavId] == Stage::SendingItem)
    {
        d->mavSequencer[mavId].removeOne(seq);
        assignment->addProgress();

        if (d->mavSequencer[mavId].isEmpty()) this->enterStage(Stage::WaitongAck, mavId);

        d->missionService->assignmentChanged(assignment);
    }
}

void MissionHandler::sendMissionAck(quint8 mavId)
{
    mavlink_message_t message;
    mavlink_mission_ack_t ackItem;

    ackItem.target_system = mavId;
    ackItem.target_component = MAV_COMP_ID_MISSIONPLANNER;
    ackItem.type = MAV_MISSION_ACCEPTED;

#ifdef MAVLINK_V2
    ackItem.mission_type = MAV_MISSION_TYPE_MISSION;
#endif

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_msg_mission_ack_encode_chan(m_communicator->systemId(),
                                        m_communicator->componentId(),
                                        m_communicator->linkChannel(link),
                                        &message, &ackItem);
    m_communicator->sendMessage(message, link);
}

void MissionHandler::processMissionCount(const mavlink_message_t& message)
{
    // Ignore mission_count, if we are not downloading mission
    if (d->mavStages.value(message.sysid, Stage::Idle) != Stage::WaitingCount) return;

    int vehicleId = d->vehicleService->vehicleIdByMavId(message.sysid);
    dto::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_mission_count_t missionCount;
    mavlink_msg_mission_count_decode(&message, &missionCount);

    // Remove superfluous items
    for (const dto::MissionItemPtr& item:
         d->missionService->missionItems(assignment->missionId()))
    {
        if (item->sequence() > missionCount.count - 1) d->missionService->remove(item);
    }

    // TODO: append fake items
    d->mavSequencer[message.sysid].clear();
    for (int seq = 0; seq < missionCount.count; ++seq)
    {
        d->mavSequencer[message.sysid].append(seq);
    }

    this->enterStage(Stage::WaitingItem, message.sysid);
    this->requestMissionItem(message.sysid, 0);
}

void MissionHandler::processMissionItem(const mavlink_message_t& message)
{
    int vehicleId = d->vehicleService->vehicleIdByMavId(message.sysid);
    dto::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_mission_item_t msgItem;
    mavlink_msg_mission_item_decode(&message, &msgItem);

    // Don't allow mav to change items while not in downloading stage(except home)
    if (d->mavStages.value(message.sysid, Stage::Idle) != Stage::WaitingItem &&
        msgItem.seq != 0) return;

    dto::MissionItemPtr item = d->missionService->missionItem(assignment->missionId(), msgItem.seq);
    if (item.isNull())
    {
        item = dto::MissionItemPtr::create();
        item->setMissionId(assignment->missionId());
        item->setSequence(msgItem.seq);
    }

    item->setCommand(msgItem.seq > 0 ?
                         ::mavCommandLongMap.value(msgItem.command, dto::MissionItem::UnknownCommand) :
                         dto::MissionItem::Home);

    if (item->isAltitudedItem())
    {
        item->setAltitudeRelative(msgItem.frame == MAV_FRAME_GLOBAL_RELATIVE_ALT);
        item->setAltitude(msgItem.z);
    }

    if (item->isPositionatedItem())
    {
        item->setLatitude(static_cast<double>(msgItem.x));
        item->setLongitude(static_cast<double>(msgItem.y));
    }

    if (msgItem.command == MAV_CMD_NAV_TAKEOFF)
    {
        item->setParameter(dto::MissionItem::Pitch, msgItem.param1);
    }
    else if (msgItem.command == MAV_CMD_NAV_LAND)
    {
        item->setParameter(dto::MissionItem::AbortAltitude, msgItem.param1);
        item->setParameter(dto::MissionItem::Yaw, msgItem.param4);
    }
    else if (msgItem.command == MAV_CMD_NAV_WAYPOINT)
    {
        item->setParameter(dto::MissionItem::Radius, msgItem.param2);
    }
    else if (msgItem.command == MAV_CMD_NAV_LOITER_UNLIM ||
             msgItem.command == MAV_CMD_NAV_LOITER_TURNS ||
             msgItem.command == MAV_CMD_NAV_LOITER_TIME)
    {
        item->setParameter(dto::MissionItem::Radius, qAbs(msgItem.param3));
        item->setParameter(dto::MissionItem::Clockwise, bool(msgItem.param3 > 0));
        item->setParameter(dto::MissionItem::Yaw, msgItem.param4);
    }
    else if (msgItem.command == MAV_CMD_NAV_LOITER_TO_ALT)
    {
        item->setParameter(dto::MissionItem::HeadingRequired, bool(msgItem.param1));
        item->setParameter(dto::MissionItem::Radius, qAbs(msgItem.param2));
        item->setParameter(dto::MissionItem::Clockwise, bool(msgItem.param2 > 0));
    }
    else if (msgItem.command == MAV_CMD_DO_CHANGE_SPEED)
    {
        item->setParameter(dto::MissionItem::IsGroundSpeed, bool(msgItem.param1));
        if (msgItem.param2 != -1) item->setParameter(dto::MissionItem::Speed, msgItem.param2);
        if (msgItem.param3 != -1) item->setParameter(dto::MissionItem::Throttle, int(msgItem.param3));
    }

    if (msgItem.command == MAV_CMD_NAV_LOITER_TURNS)
    {
        item->setParameter(dto::MissionItem::Repeats, int(msgItem.param1));
    }
    else if (msgItem.command == MAV_CMD_NAV_LOITER_TIME)
    {
        item->setParameter(dto::MissionItem::Time, msgItem.param1);
    }

//    if (msgItem.command == MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT)
//    {
//  TODO: In APM Plane 3.4 (and later) the param1 value sets how close the vehicle
//        altitude must be to target altitude for command completion.
//    }

    item->setStatus(dto::MissionItem::Actual);
    d->missionService->save(item);

    if (d->mavSequencer[message.sysid].contains(msgItem.seq) &&
        d->mavStages.value(message.sysid, Stage::Idle) == Stage::WaitingItem)
    {
        d->mavSequencer[message.sysid].removeOne(msgItem.seq);
        assignment->addProgress();

        if (d->mavSequencer[message.sysid].isEmpty())
        {
            assignment->setStatus(dto::MissionAssignment::Actual);

            this->sendMissionAck(message.sysid);
            this->enterStage(Stage::Idle, message.sysid);
        }
        else
        {
            this->enterStage(Stage::WaitingItem, message.sysid);
            this->requestMissionItem(message.sysid, d->mavSequencer[message.sysid].first());
        }

        d->missionService->assignmentChanged(assignment);
    }
}

void MissionHandler::processMissionRequest(const mavlink_message_t& message)
{
    mavlink_mission_request_t request;
    mavlink_msg_mission_request_decode(&message, &request);

    if (d->mavStages.value(message.sysid, Stage::Idle) == Stage::SendingCount)
    {
        this->enterStage(Stage::SendingItem, message.sysid);
    }

    if (d->lastSendedSequence != -1 && d->lastSendedSequence != request.seq)
    {
        d->mavSequencer[message.sysid].removeOne(d->lastSendedSequence);

        int vehicleId = d->vehicleService->vehicleIdByMavId(message.sysid);
        dto::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(vehicleId);
        if (assignment)
        {
            dto::MissionItemPtr item = d->missionService->missionItem(assignment->missionId(),
                                                                      d->lastSendedSequence);
            if (item)
            {
                item->setStatus(dto::MissionItem::Actual);
                d->missionService->missionItemChanged(item);
            }
        }
    }

    this->sendMissionItem(message.sysid, request.seq);
}

void MissionHandler::processMissionAck(const mavlink_message_t& message)
{
    int vehicleId = d->vehicleService->vehicleIdByMavId(message.sysid);
    dto::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_mission_ack_t ack;
    mavlink_msg_mission_ack_decode(&message, &ack);

#ifdef MAVLINK_V2
    if (ack.mission_type != MAV_MISSION_TYPE_MISSION) return;
#endif

    if (ack.type == MAV_MISSION_ACCEPTED)
    {
        if (d->mavStages.value(message.sysid, Stage::Idle) == Stage::WaitongAck)
        {
            assignment->setStatus(dto::MissionAssignment::Actual);
        }
    }
    else
    {
        notificationBus->notify(tr("Mission"), tr("Error uploading waypoint %1").arg(
                                 ::decodeCommandResult(ack.type)),
                             dto::Notification::Warning);
        assignment->setStatus(dto::MissionAssignment::NotActual);
    }

    d->missionService->assignmentChanged(assignment);
}

void MissionHandler::processMissionCurrent(const mavlink_message_t& message)
{
    int vehicleId = d->vehicleService->vehicleIdByMavId(message.sysid);
    dto::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_mission_current_t current;
    mavlink_msg_mission_current_decode(&message, &current);

    d->missionService->setCurrentItem(
                vehicleId, d->missionService->missionItem(assignment->missionId(), current.seq));
}

void MissionHandler::processMissionReached(const mavlink_message_t& message)
{
    int vehicleId = d->vehicleService->vehicleIdByMavId(message.sysid);
    dto::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_mission_item_reached_t reached;
    mavlink_msg_mission_item_reached_decode(&message, &reached);

    dto::MissionItemPtr item = d->missionService->missionItem(assignment->missionId(), reached.seq);
    if (item)
    {
        item->setReached(true);
        emit d->missionService->missionItemChanged(item);
    }
}

void MissionHandler::enterStage(Stage stage, quint8 mavId)
{
    if (d->mavTimers.contains(mavId))
    {
        this->killTimer(d->mavTimers.take(mavId));
    }

    d->mavStages[mavId] = stage;
    if (stage != Stage::Idle &&
        stage != Stage::SendingItem &&
        stage != Stage::WaitongAck)
    {
        d->mavTimers[mavId] = this->startTimer(::interval);
    }
}

void MissionHandler::timerEvent(QTimerEvent* event)
{
    quint8 mavId = d->mavTimers.key(event->timerId(), 0);
    if (!mavId) QObject::timerEvent(event);

    switch (d->mavStages.value(mavId, Stage::Idle))
    {
    case Stage::WaitingCount:
        this->requestMissionCount(mavId);
        break;
    case Stage::WaitingItem:
    {
        const QList<int>& list = d->mavSequencer[mavId];
        if (list.isEmpty()) this->enterStage(Stage::Idle, mavId);
        else this->requestMissionItem(mavId, list.first());
        break;
    }
    case Stage::SendingCount:
        this->sendMissionCount(mavId);
    case Stage::Idle:
    default:
        break;
    }
}
