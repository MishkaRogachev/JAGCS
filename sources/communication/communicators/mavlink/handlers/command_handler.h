#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

// Internal
#include "abstract_mavlink_handler.h"

namespace db
{
    class DbFacade;
}

namespace domain
{
    class Command;
    class CommandService;
}

namespace comm
{
    class CommandHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        CommandHandler(db::DbFacade* dbFacade,
                       domain::CommandService* commandService,
                       MavLinkCommunicator* communicator);

    public slots:
       void processMessage(const mavlink_message_t& message) override;

    private slots:
       void onGotCommand();
       void sendCommand(const domain::Command& command);

   private:
       domain::CommandService* m_commandService;
       db::DbFacade* m_dbFacade;
    };
}

#endif // COMMAND_HANDLER_H
