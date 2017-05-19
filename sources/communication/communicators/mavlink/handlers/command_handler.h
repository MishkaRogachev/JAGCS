#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

// Internal
#include "abstract_mavlink_handler.h"
#include "db_traits.h"

namespace domain
{
    class VehicleService;
}

namespace comm
{
    class CommandHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        CommandHandler(domain::VehicleService* vehicleService,
                       MavLinkCommunicator* communicator);

    public slots:
       void processMessage(const mavlink_message_t& message) override;

       void sendArmDisarm(bool arm);
       void sendReturn();
       void sendMissionRestart();
       void sendMissionStart(int startPoint);
       void sendMissionJumpTo(int startPoint);

    private slots:
        void onVehicleAdded(const db::VehicleDescriptionPtr& description);

   private:
       domain::VehicleService* m_vehicleService;
    };
}

#endif // COMMAND_HANDLER_H
