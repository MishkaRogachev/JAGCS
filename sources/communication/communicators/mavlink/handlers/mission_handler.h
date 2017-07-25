#ifndef MISSION_HANDLER_H
#define MISSION_HANDLER_H

// Internal
#include "abstract_mavlink_handler.h"
#include "dao_traits.h"

namespace db
{
    class DbFacade;
}

namespace domain
{
    class VehicleService;
    class TelemetryService;
    class MissionService;
    class CommandService;
}

namespace comm
{
    class MissionHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        MissionHandler(db::DbFacade* dbFacade,
                       domain::TelemetryService* telemetryService,
                       domain::MissionService* missionService,
                       domain::CommandService* commandService,
                       MavLinkCommunicator* communicator);

    public slots:
       void processMessage(const mavlink_message_t& message) override;

       void download(const dao::MissionAssignmentPtr& assignment);
       void upload(const dao::MissionAssignmentPtr& assignment);

       void requestMissionItem(uint8_t mavId, uint16_t seq);

       void sendMissionItem(uint8_t mavId, uint16_t seq);
       void sendMissionAck(uint8_t mavId);

    protected:
        void processMissionCount(const mavlink_message_t& message);
        void processMissionItem(const mavlink_message_t& message);
        void processMissionRequest(const mavlink_message_t& message);
        void processMissionAck(const mavlink_message_t& message);
        void processMissionCurrent(const mavlink_message_t& message);
        void processMissionReached(const mavlink_message_t& message);

   private:
       db::DbFacade* m_dbFacade;
       domain::TelemetryService* m_telemetryService;
       domain::MissionService* m_missionService;
    };
}

#endif // MISSION_HANDLER_H
