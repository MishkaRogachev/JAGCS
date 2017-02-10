#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

// Internal
#include "abstract_mavlink_handler.h"
#include "command.h"

namespace domain
{
    class VehicleService;
    class Vehicle;

    class CommandHandler: public AbstractMavLinkHandler
    {
    public:
        CommandHandler(VehicleService* vehicleService,
                       MavLinkCommunicator* communicator);

   public slots:
       void processMessage(const mavlink_message_t& message) override;

       void sendCommand(Command command, const QVariantList& args);

       void sendArmDisarm(uint8_t id, bool arm);

    private slots:
        void onVehicleAdded(domain::Vehicle* vehicle);

   private:
       VehicleService* m_vehicleService;
    };
}

#endif // COMMAND_HANDLER_H
