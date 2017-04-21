#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

// Internal
#include "abstract_mavlink_handler.h"
#include "db_traits.h"

namespace domain
{
    class VehicleService;

    class CommandHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        CommandHandler(VehicleService* vehicleService,
                       data_source::MavLinkCommunicator* communicator);

    public slots:
       void processMessage(const mavlink_message_t& message) override;

       void sendArmDisarm(bool arm);
       void sendReturn();
       void sendMissionRestart();
       void sendMissionStart(int startPoint);
       void sendMissionJumpTo(int startPoint);

    private slots:
        void onVehicleAdded(const data_source::VehicleDescriptionPtr& description);

   private:
       VehicleService* m_vehicleService;
    };
}

#endif // COMMAND_HANDLER_H
