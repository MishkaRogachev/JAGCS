#include "waypoint_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "mavlink_communicator.h"

#include "vehicle_service.h"
#include "vehicle.h"

using namespace domain;

WaypointHandler::WaypointHandler(VehicleService* vehicleService,
                                 MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(vehicleService)
{}

void WaypointHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid == MAVLINK_MSG_ID_MISSION_COUNT)
    {
        Vehicle* vehicle = m_vehicleService->requestVehicle(message.sysid);

        mavlink_mission_count_t missionCount;
        mavlink_msg_mission_count_decode(&message, &missionCount);

        qDebug() << message.sysid << missionCount.target_system;

        // TODO: vehicle->mission.setCount(missionCount.count);
        return;
    }

    if (message.msgid == MAVLINK_MSG_ID_MISSION_ITEM)
    {
        Vehicle* vehicle = m_vehicleService->requestVehicle(message.sysid);

        mavlink_mission_item_t missionItem;
        mavlink_msg_mission_item_decode(&message, &missionItem);

        // TODO: vehicle->mission.setMissionItem(missionItem.seq, missionItem);
        return;
    }

    if (message.msgid == MAVLINK_MSG_ID_MISSION_ACK)
    {
        Vehicle* vehicle = m_vehicleService->requestVehicle(message.sysid);

        mavlink_mission_ack_t missionAck;
        mavlink_msg_mission_ack_decode(&message, &missionAck);

        // TODO: handle missionAck
    }
}

void WaypointHandler::requestMission(uint8_t id)
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

void WaypointHandler::requestMissionItem(uint8_t id, uint16_t item)
{
    mavlink_message_t message;
    mavlink_mission_request_t missionRequest;

    missionRequest.target_system = id;
    missionRequest.target_component = MAV_COMP_ID_MISSIONPLANNER;
    missionRequest.seq = item;

    mavlink_msg_mission_request_encode(m_communicator->systemId(),
                                       m_communicator->componentId(),
                                       &message, &missionRequest);
    m_communicator->sendMessageAllLinks(message);
}
