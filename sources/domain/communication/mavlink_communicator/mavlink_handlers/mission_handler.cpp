#include "mission_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "mavlink_communicator.h"

#include "mission_service.h"
#include "mission.h"
#include "mission_item_factory.h"
#include "mission_vehicle.h"

#include "home_mission_item.h"
#include "takeoff_mission_item.h"
#include "waypoint_mission_item.h"
#include "continue_mission_item.h"
#include "loiter_turns_mission_item.h"
#include "return_mission_item.h"
#include "landing_mission_item.h"

using namespace domain;

namespace
{
    Command decodeCommand(uint16_t command, uint8_t seq)
    {
        switch (command) {
        case MAV_CMD_NAV_TAKEOFF:
            return Command::Takeoff;
        case MAV_CMD_NAV_WAYPOINT:
            return seq > 0 ? Command::Waypoint : Command::Home;
        case MAV_CMD_NAV_LOITER_TO_ALT:
            return Command::LoiterAltitude;
        case MAV_CMD_NAV_LOITER_TURNS:
            return Command::LoiterTurns;
        case MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT:
            return Command::Continue;
        case MAV_CMD_NAV_RETURN_TO_LAUNCH:
            return Command::Return;
        case MAV_CMD_NAV_LAND:
            return Command::Landing;
        default:
            return Command::UnknownCommand;
        }
    }

    uint16_t encodeCommand(Command command)
    {
        switch (command) {
        case Command::Takeoff:
            return MAV_CMD_NAV_TAKEOFF;
        case Command::Home:
        case Command::Waypoint:
            return MAV_CMD_NAV_WAYPOINT;
        case Command::LoiterAltitude:
            return MAV_CMD_NAV_LOITER_TO_ALT;
        case Command::LoiterTurns:
            return MAV_CMD_NAV_LOITER_TURNS;
        case Command::Continue:
            return MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT;
        case Command::Return:
            return MAV_CMD_NAV_RETURN_TO_LAUNCH;
        case Command::Landing:
            return MAV_CMD_NAV_LAND;
        default:
            return 0;
        }
    }
}

MissionHandler::MissionHandler(MissionService* missionService,
                               MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_missionService(missionService)
{
    connect(missionService, &MissionService::requestMission,
            this, &MissionHandler::requestMission);
    connect(missionService, &MissionService::sendMission,
            this, &MissionHandler::sendMissionCount);
}

void MissionHandler::processMessage(const mavlink_message_t& message)
{
    switch (message.msgid) {
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
    default:
        break;
    }
}

void MissionHandler::requestMission(uint8_t id)
{
    mavlink_message_t message;
    mavlink_mission_request_list_t request;

    // TODO: request Timer

    request.target_system = id;
    request.target_component = MAV_COMP_ID_MISSIONPLANNER;

    mavlink_msg_mission_request_list_encode(m_communicator->systemId(),
                                            m_communicator->componentId(),
                                            &message, &request);
    m_communicator->sendMessageAllLinks(message);
}

void MissionHandler::requestMissionItem(uint8_t id, uint16_t seq)
{
    mavlink_message_t message;
    mavlink_mission_request_t missionRequest;

    missionRequest.target_system = id;
    missionRequest.target_component = MAV_COMP_ID_MISSIONPLANNER;
    missionRequest.seq = seq;

    mavlink_msg_mission_request_encode(m_communicator->systemId(),
                                       m_communicator->componentId(),
                                       &message, &missionRequest);
    m_communicator->sendMessageAllLinks(message);
}

void MissionHandler::sendMissionCount(uint8_t id)
{
    Mission* mission = m_missionService->missionForVehicleId(id);
    if (!mission) return;

    mavlink_message_t message;
    mavlink_mission_count_t count;

    count.target_system = id;
    count.target_component = MAV_COMP_ID_MISSIONPLANNER;
    count.count = mission->count();

    mission->assignment()->setCurrentProgress(0);
    mission->assignment()->setTotalProgress(count.count);

    mavlink_msg_mission_count_encode(m_communicator->systemId(),
                                     m_communicator->componentId(),
                                     &message, &count);
    m_communicator->sendMessageAllLinks(message);
}

void MissionHandler::sendMissionItem(uint8_t id, uint16_t seq)
{
    Mission* mission = m_missionService->missionForVehicleId(id);
    if (!mission || mission->count() <= seq) return;

    MissionItem* item = mission->item(seq);

    mavlink_message_t message;
    mavlink_mission_item_t msgItem;

    msgItem.target_system = id;
    msgItem.target_component = MAV_COMP_ID_MISSIONPLANNER;

    msgItem.seq = item->sequence();
    msgItem.autocontinue = item->sequence() < mission->count() - 1;

    msgItem.command = ::encodeCommand(item->command());

    AltitudeMissionItem* altitudeItem = qobject_cast<AltitudeMissionItem*>(item);
    if (altitudeItem)
    {
        msgItem.frame = altitudeItem->isRelativeAltitude() ?
                            MAV_FRAME_GLOBAL_RELATIVE_ALT : MAV_FRAME_GLOBAL;
        msgItem.z = altitudeItem->altitude();

        AltitudeMissionItem* continueItem =
                qobject_cast<ContinueMissionItem*>(altitudeItem);
        if (continueItem)
        {
            msgItem.param1 = altitudeItem->climb() ?
                                 1 : altitudeItem->climb() < 0 ? -1 : 0;
        }

        PositionMissionItem* positionItem =
                qobject_cast<PositionMissionItem*>(altitudeItem);
        if (positionItem)
        {
            msgItem.x = positionItem->latitude();
            msgItem.y = positionItem->longitude();

            TakeoffMissionItem* takeoffItem =
                    qobject_cast<TakeoffMissionItem*>(positionItem);
            if (takeoffItem)
            {
                msgItem.param1 = takeoffItem->pitch();
                msgItem.param4 = takeoffItem->azimuth();
            }

            LandingMissionItem* landingItem =
                    qobject_cast<LandingMissionItem*>(positionItem);
            if (landingItem)
            {
                msgItem.param4 = landingItem->azimuth();
            }

            WaypointMissionItem* waypointItem =
                    qobject_cast<WaypointMissionItem*>(positionItem);
            if (waypointItem)
            {
                msgItem.param2 = waypointItem->acceptanceRadius();
            }

            LoiterMissionItem* loiterItem =
                    qobject_cast<LoiterMissionItem*>(positionItem);
            if (loiterItem)
            {
                // TODO: headingRequired
                msgItem.param2 = loiterItem->radius();
            }

            LoiterTurnsMissionItem* turnsItem =
                    qobject_cast<LoiterTurnsMissionItem*>(positionItem);
            if (turnsItem)
            {
                msgItem.param1 = turnsItem->turns();
                msgItem.param3 = turnsItem->radius();
            }
        }
    }

    mavlink_msg_mission_item_encode(m_communicator->systemId(),
                                    m_communicator->componentId(),
                                    &message, &msgItem);
    m_communicator->sendMessageAllLinks(message);

    mission->assignment()->setCurrentProgress(item->sequence());

    if (mission->assignment()->currentProgress() ==
        mission->assignment()->totalProgress())
    {
        mission->assignment()->setStatus(MissionVehicle::Ready);
    }
}

void MissionHandler::sendMissionAck(uint8_t id)
{
    mavlink_message_t message;
    mavlink_mission_ack_t ackItem;

    ackItem.target_system = id;
    ackItem.target_component = MAV_COMP_ID_MISSIONPLANNER;
    ackItem.type = MAV_MISSION_ACCEPTED;

    mavlink_msg_mission_ack_encode(m_communicator->systemId(),
                                   m_communicator->componentId(),
                                   &message, &ackItem);
    m_communicator->sendMessageAllLinks(message);
}

void MissionHandler::processMissionCount(const mavlink_message_t& message)
{
    Mission* mission = m_missionService->missionForVehicleId(message.sysid);
    if (!mission) return;

    mavlink_mission_count_t missionCount;
    mavlink_msg_mission_count_decode(&message, &missionCount);

    mission->assignment()->setCurrentProgress(0);
    mission->assignment()->setTotalProgress(missionCount.count);
    mission->setCount(missionCount.count);

    for (uint16_t seq = 0; seq < missionCount.count; ++seq)
    {
        this->requestMissionItem(message.sysid, seq);
    }
}

void MissionHandler::processMissionItem(const mavlink_message_t& message)
{
    Mission* mission = m_missionService->missionForVehicleId(message.sysid);
    if (!mission) return;

    mavlink_mission_item_t msgItem;
    mavlink_msg_mission_item_decode(&message, &msgItem);

    MissionItemFactory factory(mission);
    MissionItem* item = factory.create(::decodeCommand(msgItem.command, msgItem.seq));

    AltitudeMissionItem* altitudeItem = qobject_cast<AltitudeMissionItem*>(item);
    if (altitudeItem)
    {
        switch (msgItem.frame)
        {
        case MAV_FRAME_GLOBAL_RELATIVE_ALT:
            altitudeItem->setRelativeAltitude(true);
            break;
        case MAV_FRAME_GLOBAL:
            altitudeItem->setRelativeAltitude(false);
            break;
        default:
            // TODO: Warning unhandled frame
            break;
        }
        altitudeItem->setAltitude(msgItem.z);

        PositionMissionItem* positionItem =
                qobject_cast<PositionMissionItem*>(altitudeItem);
        if (positionItem)
        {
            if (qFuzzyIsNull(msgItem.x) && qFuzzyIsNull(msgItem.y))
            {
                positionItem->setLatitude(qQNaN());
                positionItem->setLongitude(qQNaN());
            }
            else
            {
                positionItem->setLatitude(msgItem.x);
                positionItem->setLongitude(msgItem.y);
            }

            TakeoffMissionItem* takeoffItem =
                    qobject_cast<TakeoffMissionItem*>(positionItem);
            if (takeoffItem)
            {
                takeoffItem->setPitch(msgItem.param1);
            }

            // Ignore azimuth(yaw) in msgItem.param4

            WaypointMissionItem* waypointItem =
                    qobject_cast<WaypointMissionItem*>(positionItem);
            if (waypointItem)
            {
                waypointItem->setAcceptanceRadius(msgItem.param2);
            }

            LoiterMissionItem* loiterItem =
                    qobject_cast<LoiterMissionItem*>(positionItem);
            if (loiterItem)
            {
                // TODO: headingRequired
                loiterItem->setRadius(msgItem.param2);
            }

            LoiterTurnsMissionItem* turnsItem =
                    qobject_cast<LoiterTurnsMissionItem*>(positionItem);
            if (turnsItem)
            {
                turnsItem->setTurns(msgItem.param1);
                turnsItem->setRadius(msgItem.param3);
            }
        }
    }

    mission->setMissionItem(msgItem.seq, item);
    if (msgItem.current) mission->setCurrentIndex(msgItem.seq);

    mission->assignment()->setCurrentProgress(mission->count());

    if (mission->assignment()->currentProgress() ==
        mission->assignment()->totalProgress())
    {
        this->sendMissionAck(message.sysid);
        mission->assignment()->setStatus(MissionVehicle::Ready);
    }
}

void MissionHandler::processMissionRequest(const mavlink_message_t& message)
{
    mavlink_mission_request_t request;
    mavlink_msg_mission_request_decode(&message, &request);

    this->sendMissionItem(message.sysid, request.seq);
}

void MissionHandler::processMissionAck(const mavlink_message_t& message)
{
    Mission* mission = m_missionService->missionForVehicleId(message.sysid);
    if (!mission) return;

    mavlink_mission_ack_t missionAck;
    mavlink_msg_mission_ack_decode(&message, &missionAck);

    // TODO: handle missionAck.type
}
