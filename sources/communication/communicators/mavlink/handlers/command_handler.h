#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

// Internal
#include "abstract_mavlink_handler.h"

namespace domain
{
    class Command;
    class CommandService;
    class VehicleService;
}

namespace comm
{
    class CommandHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        CommandHandler(domain::VehicleService* vehicleService,
                       domain::CommandService* commandService,
                       MavLinkCommunicator* communicator);

    public slots:
       void processMessage(const mavlink_message_t& message) override;

    private slots:
       void onGotCommand();
       void sendCommand(const domain::Command& command);

   private:
       domain::CommandService* m_commandService;
       domain::VehicleService* m_vehicleService;
    };
}

#endif // COMMAND_HANDLER_H
