#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

// Internal
#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;
    class AbstractVehicle;

    class CommandHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        CommandHandler(VehicleService* vehicleService,
                       MavLinkCommunicator* communicator);

    public slots:
       void processMessage(const mavlink_message_t& message) override;

       void sendArmDisarm(bool arm);
       void sendReturn();
       void sendMissionRestart();
       void sendMissionStart(int startPoint);
       void sendMissionJumpTo(int startPoint);
       //TODO: SET_ROLL_PITCH_YAW_THRUST

    private slots:
        void onVehicleAdded(domain::AbstractVehicle* vehicle);
        void onVehicleRemoved(domain::AbstractVehicle* vehicle);

   private:
       VehicleService* m_vehicleService;
    };
}

#endif // COMMAND_HANDLER_H
