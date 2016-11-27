#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;

    class CommandHandler: public AbstractMavLinkHandler
    {
    public:
        CommandHandler(VehicleService* vehicleService,
                       MavLinkCommunicator* communicator);

   public slots:
       void processMessage(const mavlink_message_t& message) override;

       void sendArmCommand(bool arm);

    private slots:
        void onVehicleAdded(uint8_t id);

   private:
       VehicleService* m_vehicleService;
    };
}

#endif // COMMAND_HANDLER_H
