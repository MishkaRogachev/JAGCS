#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

// Internal
#include "abstract_mavlink_handler.h"

namespace domain
{
    class CommandService;
}

namespace comm
{
    class CommandHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        CommandHandler(domain::CommandService* commandService,
                       MavLinkCommunicator* communicator);

    public slots:
       void processMessage(const mavlink_message_t& message) override;

       void sendArmDisarm(int mavId, bool arm);
       void sendReturn(int mavId);
       void sendMissionRestart(int mavId);
       void sendMissionStart(int mavId, int startPoint);
       void sendMissionJumpTo(int mavId, int startPoint);

   private:
       domain::CommandService* m_commandService;
    };
}

#endif // COMMAND_HANDLER_H
