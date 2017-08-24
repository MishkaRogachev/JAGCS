#include "mission_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QMap>
#include <QTimerEvent>
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

namespace
{
    const int interval = 1000;

    const QMap<quint16, dao::MissionItem::Command> mavCommandMap =
    {
        { MAV_CMD_NAV_TAKEOFF, dao::MissionItem::Takeoff },
        { MAV_CMD_NAV_LAND, dao::MissionItem::Landing },
        { MAV_CMD_NAV_WAYPOINT, dao::MissionItem::Waypoint },
        { MAV_CMD_NAV_LOITER_UNLIM, dao::MissionItem::LoiterUnlim },
        { MAV_CMD_NAV_LOITER_TO_ALT, dao::MissionItem::LoiterAltitude },
        { MAV_CMD_NAV_LOITER_TURNS, dao::MissionItem::LoiterTurns },
        { MAV_CMD_NAV_LOITER_TIME, dao::MissionItem::LoiterTime },
        { MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT, dao::MissionItem::Continue },
        { MAV_CMD_NAV_RETURN_TO_LAUNCH, dao::MissionItem::Return },

        { MAV_CMD_DO_CHANGE_SPEED, dao::MissionItem::SetSpeed },

        { MAV_CMD_DO_JUMP, dao::MissionItem::JumpTo },

        { MAV_CMD_DO_SET_SERVO, dao::MissionItem::SetServo },
        { MAV_CMD_DO_SET_RELAY, dao::MissionItem::SetRelay },
        { MAV_CMD_DO_REPEAT_SERVO, dao::MissionItem::RepeatServo },
        { MAV_CMD_DO_REPEAT_RELAY, dao::MissionItem::RepeatRelay },

        { MAV_CMD_DO_SET_ROI, dao::MissionItem::SetRoi },
        { MAV_CMD_DO_MOUNT_CONTROL, dao::MissionItem::MountControl },
        { MAV_CMD_DO_SET_CAM_TRIGG_DIST, dao::MissionItem::SetCameraTriggerDistance },
        { MAV_CMD_DO_DIGICAM_CONTROL, dao::MissionItem::CameraControl }
    };
}

using namespace comm;
using namespace domain;

class MissionHandler::Impl
{
public:
    VehicleService* vehicleService = ServiceRegistry::vehicleService();
    TelemetryService* telemetryService = ServiceRegistry::telemetryService();
    MissionService* missionService = ServiceRegistry::missionService();

    QMap <quint8, MissionHandler::Stage> mavStages;
    QMap <quint8, int> mavTimers;
    QMap <quint8, QList<int> > mavSequencer;
    int lastSendedSequence = -1;
};

MissionHandler::MissionHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    d(new Impl())
{
    connect(d->missionService, &MissionService::download, this, &MissionHandler::download);
    connect(d->missionService, &MissionService::upload, this, &MissionHandler::upload);
    connect(d->missionService, &MissionService::cancelSync, this, &MissionHandler::cancelSync);
    connect(d->missionService, &MissionService::selectCurrentItem, this, &MissionHandler::selectCurrent);
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

void MissionHandler::download(const dao::MissionAssignmentPtr& assignment)
{
    dao::VehiclePtr vehicle = d->vehicleService->vehicle(assignment->vehicleId());
    if (vehicle.isNull()) return;

    assignment->setStatus(dao::MissionAssignment::Downloading);
    d->missionService->assignmentChanged(assignment);

    this->enterStage(Stage::WaitingCount, vehicle->mavId());
    this->requestMissionCount(vehicle->mavId());
}

void MissionHandler::upload(const dao::MissionAssignmentPtr& assignment)
{
    dao::VehiclePtr vehicle = d->vehicleService->vehicle(assignment->vehicleId());
    if (vehicle.isNull()) return;

    d->mavSequencer[vehicle->mavId()].clear();
    for (const dao::MissionItemPtr& item: d->missionService->missionItems(assignment->missionId()))
    {
        if (item->status() == dao::MissionItem::Actual) continue;

        d->mavSequencer[vehicle->mavId()].append(item->sequence());
        item->setStatus(dao::MissionItem::NotActual);
        d->missionService->missionItemChanged(item);
    }

    if (d->mavSequencer.isEmpty())
    {
        this->enterStage(Stage::Idle, vehicle->mavId());
    }
    else
    {
        assignment->setStatus(dao::MissionAssignment::Uploading);
        d->missionService->assignmentChanged(assignment);

        d->lastSendedSequence = -1;
        this->enterStage(Stage::SendingCount, vehicle->mavId());
        this->sendMissionCount(vehicle->mavId());
    }
}

void MissionHandler::cancelSync(const dao::MissionAssignmentPtr& assignment)
{
    this->enterStage(Stage::Idle, d->vehicleService->mavIdByVehicleId(assignment->vehicleId()));

    assignment->setStatus(dao::MissionAssignment::NotActual);
    d->missionService->assignmentChanged(assignment);
}

void MissionHandler::selectCurrent(int vehicleId, quint16 seq)
{
    this->sendCurrentItem(d->vehicleService->mavIdByVehicleId(vehicleId), seq);
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
    dao::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(
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

    dao::MissionItemPtr item = d->missionService->missionItem(assignment->missionId(), seq);
    if (item.isNull()) return;

    item->setStatus(dao::MissionItem::Downloading);
    d->missionService->missionItemChanged(item);
}

void MissionHandler::sendMissionCount(quint8 mavId)
{
    dao::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(
                                               d->vehicleService->vehicleIdByMavId(mavId));
    if (assignment.isNull()) return;

    dao::MissionPtr mission = d->missionService->mission(assignment->missionId());

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
    dao::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_message_t message;
    mavlink_mission_item_t msgItem;

    msgItem.target_system = mavId;
    msgItem.target_component = MAV_COMP_ID_MISSIONPLANNER;

    dao::MissionItemPtr item = d->missionService->missionItem(assignment->missionId(), seq);
    if (item.isNull()) return;

    msgItem.seq = seq;
    msgItem.autocontinue = seq < d->missionService->mission(assignment->missionId())->count() - 1;

    if (seq) msgItem.command = ::mavCommandMap.key(item->command(), 0);
    else msgItem.command = MAV_CMD_NAV_WAYPOINT; // Home is waypoint

    if (!qIsNaN(item->altitude()))
    {
        msgItem.frame = item->isAltitudeRelative() ? MAV_FRAME_GLOBAL_RELATIVE_ALT : MAV_FRAME_GLOBAL;
        msgItem.z = item->altitude();
    }

    if (!qIsNaN(item->latitude())) msgItem.x = item->latitude();

    if (!qIsNaN(item->longitude())) msgItem.y = item->longitude();

    if (msgItem.command == MAV_CMD_NAV_TAKEOFF)
    {
        msgItem.param1 = item->parameter(dao::MissionItem::Pitch).toFloat();
    }
    else if (msgItem.command == MAV_CMD_NAV_LAND)
    {
        msgItem.param1 = item->parameter(dao::MissionItem::AbortAltitude).toFloat();
        msgItem.param4 = item->parameter(dao::MissionItem::Yaw).toFloat();
    }
    else if (msgItem.command == MAV_CMD_NAV_WAYPOINT)
    {
        msgItem.param2 = item->parameter(dao::MissionItem::Radius).toFloat();
    }
    else if (msgItem.command == MAV_CMD_NAV_LOITER_UNLIM ||
             msgItem.command == MAV_CMD_NAV_LOITER_TURNS ||
             msgItem.command == MAV_CMD_NAV_LOITER_TIME)
    {
        msgItem.param3 = item->parameter(dao::MissionItem::Clockwise).toBool() ?
                             item->parameter(dao::MissionItem::Radius).toFloat() :
                             -1 * item->parameter(dao::MissionItem::Radius).toFloat();
        msgItem.param4 = item->parameter(dao::MissionItem::Yaw).toFloat();
    }
    else if (msgItem.command == MAV_CMD_NAV_LOITER_TO_ALT)
    {
        msgItem.param1 = item->parameter(dao::MissionItem::HeadingRequired).toBool();
        msgItem.param2 = item->parameter(dao::MissionItem::Clockwise).toBool() ?
                             item->parameter(dao::MissionItem::Radius).toFloat() :
                             -1 * item->parameter(dao::MissionItem::Radius).toFloat();
    }
    else if (msgItem.command == MAV_CMD_DO_CHANGE_SPEED)
    {
        msgItem.param1 = item->parameter(dao::MissionItem::IsGroundSpeed).toBool();
        msgItem.param2 = item->parameter(dao::MissionItem::Speed, -1).toFloat();
        msgItem.param3 = item->parameter(dao::MissionItem::Throttle, -1).toInt();
    }

    if (msgItem.command == MAV_CMD_NAV_LOITER_TURNS)
    {
        msgItem.param1 = item->parameter(dao::MissionItem::Repeats).toInt();
    }
    else if (msgItem.command == MAV_CMD_NAV_LOITER_TIME)
    {
        msgItem.param1 = item->parameter(dao::MissionItem::Time).toFloat();
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

    item->setStatus(dao::MissionItem::Uploading);
    d->lastSendedSequence = seq;
    d->missionService->missionItemChanged(item);
}

void MissionHandler::sendMissionAck(quint8 mavId)
{
    mavlink_message_t message;
    mavlink_mission_ack_t ackItem;

    ackItem.target_system = mavId;
    ackItem.target_component = MAV_COMP_ID_MISSIONPLANNER;
    ackItem.mission_type = MAV_MISSION_TYPE_MISSION;
    ackItem.type = MAV_MISSION_ACCEPTED;

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_msg_mission_ack_encode_chan(m_communicator->systemId(),
                                        m_communicator->componentId(),
                                        m_communicator->linkChannel(link),
                                        &message, &ackItem);
    m_communicator->sendMessage(message, link);
}

void MissionHandler::sendCurrentItem(quint8 mavId, quint16 seq)
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
}

void MissionHandler::processMissionCount(const mavlink_message_t& message)
{
    // Ignore mission_count, if we are not downloading mission
    if (d->mavStages.value(message.sysid, Stage::Idle) != Stage::WaitingCount) return;

    int vehicleId = d->vehicleService->vehicleIdByMavId(message.sysid);
    dao::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_mission_count_t missionCount;
    mavlink_msg_mission_count_decode(&message, &missionCount);

    // Remove superfluous items
    for (const dao::MissionItemPtr& item:
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
    dao::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_mission_item_t msgItem;
    mavlink_msg_mission_item_decode(&message, &msgItem);

    // Don't allow mav to change items while not in downloading stage(except home)
    if (d->mavStages.value(message.sysid, Stage::Idle) != Stage::WaitingItem &&
        msgItem.seq != 0) return;

    dao::MissionItemPtr item = d->missionService->missionItem(assignment->missionId(), msgItem.seq);
    if (item.isNull())
    {
        item = dao::MissionItemPtr::create();
        item->setMissionId(assignment->missionId());
        item->setSequence(msgItem.seq);
    }

    item->setCommand(msgItem.seq > 0 ?
                         ::mavCommandMap.value(msgItem.command, dao::MissionItem::UnknownCommand) :
                         dao::MissionItem::Home);

    switch (msgItem.frame)
    {
    case MAV_FRAME_GLOBAL_RELATIVE_ALT:
        item->setAltitudeRelative(true);
        break;
    case MAV_FRAME_GLOBAL:
    default:
        item->setAltitudeRelative(false);
        break;
    }

    item->setAltitude(msgItem.z);

    if (qFuzzyIsNull(msgItem.x) && qFuzzyIsNull(msgItem.y))
    {
        item->setLatitude(qQNaN());
        item->setLongitude(qQNaN());
    }
    else
    {
        item->setLatitude(msgItem.x);
        item->setLongitude(msgItem.y);
    }

    if (msgItem.command == MAV_CMD_NAV_TAKEOFF)
    {
        item->setParameter(dao::MissionItem::Pitch, msgItem.param1);
    }
    else if (msgItem.command == MAV_CMD_NAV_LAND)
    {
        item->setParameter(dao::MissionItem::AbortAltitude, msgItem.param1);
        item->setParameter(dao::MissionItem::Yaw, msgItem.param4);
    }
    else if (msgItem.command == MAV_CMD_NAV_WAYPOINT)
    {
        item->setParameter(dao::MissionItem::Radius, msgItem.param2);
    }
    else if (msgItem.command == MAV_CMD_NAV_LOITER_UNLIM ||
             msgItem.command == MAV_CMD_NAV_LOITER_TURNS ||
             msgItem.command == MAV_CMD_NAV_LOITER_TIME)
    {
        item->setParameter(dao::MissionItem::Radius, qAbs(msgItem.param3));
        item->setParameter(dao::MissionItem::Clockwise, bool(msgItem.param3 > 0));
        item->setParameter(dao::MissionItem::Yaw, msgItem.param4);
    }
    else if (msgItem.command == MAV_CMD_NAV_LOITER_TO_ALT)
    {
        item->setParameter(dao::MissionItem::HeadingRequired, bool(msgItem.param1));
        item->setParameter(dao::MissionItem::Radius, qAbs(msgItem.param2));
        item->setParameter(dao::MissionItem::Clockwise, bool(msgItem.param2 > 0));
    }
    else if (msgItem.command == MAV_CMD_DO_CHANGE_SPEED)
    {
        item->setParameter(dao::MissionItem::IsGroundSpeed, bool(msgItem.param1));
        if (msgItem.param2 != -1) item->setParameter(dao::MissionItem::Speed, msgItem.param2);
        if (msgItem.param3 != -1) item->setParameter(dao::MissionItem::Throttle, int(msgItem.param3));
    }

    if (msgItem.command == MAV_CMD_NAV_LOITER_TURNS)
    {
        item->setParameter(dao::MissionItem::Repeats, int(msgItem.param1));
    }
    else if (msgItem.command == MAV_CMD_NAV_LOITER_TIME)
    {
        item->setParameter(dao::MissionItem::Time, msgItem.param1);
    }

//    if (msgItem.command == MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT)
//    {
//  TODO: In Plane 3.4 (and later) the param1 value sets how close the vehicle
//        altitude must be to target altitude for command completion.
//    }

    item->setStatus(dao::MissionItem::Actual);
    d->missionService->save(item);

    if (d->mavSequencer[message.sysid].contains(msgItem.seq) &&
        d->mavStages.value(message.sysid, Stage::Idle) == Stage::WaitingItem)
    {
        d->mavSequencer[message.sysid].removeOne(msgItem.seq);

        if (d->mavSequencer[message.sysid].isEmpty())
        {
            assignment->setStatus(dao::MissionAssignment::Actual);
            d->missionService->assignmentChanged(assignment);

            this->sendMissionAck(message.sysid);
            this->enterStage(Stage::Idle, message.sysid);
        }
        else
        {
            this->enterStage(Stage::WaitingItem, message.sysid);
            this->requestMissionItem(message.sysid, d->mavSequencer[message.sysid].first());
        }
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
        dao::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(vehicleId);
        if (assignment)
        {
            dao::MissionItemPtr item = d->missionService->missionItem(assignment->missionId(),
                                                                      d->lastSendedSequence);
            if (item)
            {
                item->setStatus(dao::MissionItem::Actual);
                d->missionService->missionItemChanged(item);
            }
        }
    }

    this->sendMissionItem(message.sysid, request.seq);
}

void MissionHandler::processMissionAck(const mavlink_message_t& message)
{
    int vehicleId = d->vehicleService->vehicleIdByMavId(message.sysid);
    dao::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_mission_ack_t ack;
    mavlink_msg_mission_ack_decode(&message, &ack);


    if (ack.mission_type != MAV_MISSION_TYPE_MISSION) return;

    dao::MissionItemPtr item = d->missionService->missionItem(assignment->missionId(),
                                                              d->lastSendedSequence);
    if (item.isNull()) return;

    if (ack.type == MAV_MISSION_ACCEPTED)
    {
        item->setStatus(dao::MissionItem::Actual);
    }
    else
    {
        // TODO: show error, why not actual
        item->setStatus(dao::MissionItem::NotActual);
    }

    d->missionService->missionItemChanged(item);

    if (d->mavStages[message.sysid] == Stage::SendingItem)
    {
        d->mavSequencer[message.sysid].removeOne(d->lastSendedSequence);

        if (d->mavSequencer[message.sysid].isEmpty())
        {
            assignment->setStatus(dao::MissionAssignment::Actual);
            d->missionService->assignmentChanged(assignment);

            this->enterStage(Stage::Idle, message.sysid);
        }
    }
}

void MissionHandler::processMissionCurrent(const mavlink_message_t& message)
{
    int vehicleId = d->vehicleService->vehicleIdByMavId(message.sysid);
    dao::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_mission_current_t current;
    mavlink_msg_mission_current_decode(&message, &current);

    d->missionService->setCurrentItem(
                vehicleId, d->missionService->missionItem(assignment->missionId(), current.seq));
}

void MissionHandler::processMissionReached(const mavlink_message_t& message)
{
    int vehicleId = d->vehicleService->vehicleIdByMavId(message.sysid);
    dao::MissionAssignmentPtr assignment = d->missionService->vehicleAssignment(vehicleId);
    if (assignment.isNull()) return;

    mavlink_mission_item_reached_t reached;
    mavlink_msg_mission_item_reached_decode(&message, &reached);

    dao::MissionItemPtr item = d->missionService->missionItem(assignment->missionId(), reached.seq);
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
        stage != Stage::SendingItem)
    {
        d->mavTimers[mavId] = this->startTimer(::interval);
    }
}

void MissionHandler::timerEvent(QTimerEvent* event)
{
    quint8 mavId = d->mavTimers.key(event->timerId(), 0);
    if (!mavId) AbstractMavLinkHandler::timerEvent(event);

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
