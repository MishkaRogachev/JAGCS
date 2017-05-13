#ifndef MISSION_HANDLER_H
#define MISSION_HANDLER_H

// Internal
#include "abstract_mavlink_handler.h"
#include "db_traits.h"

namespace domain
{
    class MissionService;
    class VehicleService;
}

namespace comm
{
    class MissionHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        MissionHandler(domain::MissionService* missionService,
                       domain::VehicleService* vehicleService,
                       MavLinkCommunicator* communicator);

    public slots:
       void processMessage(const mavlink_message_t& message) override;

       void download(const db::MissionAssignmentPtr& assignment);
       void upload(const db::MissionAssignmentPtr& assignment);

       void requestMissionItem(uint8_t id, uint16_t seq);

       void sendMissionItem(uint8_t id, uint16_t seq);
       void sendMissionAck(uint8_t id);
       // TODO: MISSION_SET_CURRENT, MISSION_ITEM_REACHED

    protected:
        void processMissionCount(const mavlink_message_t& message);
        void processMissionItem(const mavlink_message_t& message);
        void processMissionRequest(const mavlink_message_t& message);
        void processMissionAck(const mavlink_message_t& message);
        void processMissionCurrent(const mavlink_message_t& message);

   private:
       domain::MissionService* m_missionService;
       domain::VehicleService* m_vehicleService;
    };
}

#endif // MISSION_HANDLER_H
