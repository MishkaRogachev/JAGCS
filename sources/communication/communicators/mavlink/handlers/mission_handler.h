#ifndef MISSION_HANDLER_H
#define MISSION_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class MissionService;
}

namespace comm
{
    class MissionHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        MissionHandler(domain::MissionService* missionService,
                       MavLinkCommunicator* communicator);

   public slots:
       void processMessage(const mavlink_message_t& message) override;

    protected:
        void processMissionCount(const mavlink_message_t& message);
        void processMissionItem(const mavlink_message_t& message);
        void processMissionRequest(const mavlink_message_t& message);
        void processMissionAck(const mavlink_message_t& message);
        void processMissionCurrent(const mavlink_message_t& message);

   private:
       domain::MissionService* m_missionService;
    };
}

#endif // MISSION_HANDLER_H
