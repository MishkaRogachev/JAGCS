#ifndef MISSION_HANDLER_H
#define MISSION_HANDLER_H

// Internal
#include "abstract_mavlink_handler.h"
#include "dao_traits.h"

namespace domain
{
    class CommandService;
    class TelemetryService;
    class VehicleService;
    class MissionService;
}

namespace comm
{
    class MissionHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        MissionHandler(domain::VehicleService* vehicleService,
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
       domain::VehicleService* m_vehicleService;
       domain::TelemetryService* m_telemetryService;
       domain::MissionService* m_missionService;
    };
}

#endif // MISSION_HANDLER_H
