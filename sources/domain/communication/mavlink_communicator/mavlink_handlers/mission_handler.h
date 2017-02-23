#ifndef MISSION_HANDLER_H
#define MISSION_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class MissionService;
    class Mission;

    class MissionHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        MissionHandler(MissionService* missionService,
                       MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void requestMission(uint8_t id);
        void requestMissionItem(uint8_t id, uint16_t seq);

        void sendMissionCount(uint8_t id);
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
        MissionService* m_missionService;
    };
}

#endif // MISSION_HANDLER_H
