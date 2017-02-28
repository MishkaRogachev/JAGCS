#ifndef MANUAL_HANDLER_H
#define MANUAL_HANDLER_H

// Internal
#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;
    class AbstractVehicle;

    class ManualHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        ManualHandler(VehicleService* vehicleService,
                      MavLinkCommunicator* communicator);

    public slots:
       void processMessage(const mavlink_message_t& message) override;

       void sendManualInput(int x, int y, int z, int r);

    private slots:
        void onVehicleAdded(domain::AbstractVehicle* vehicle);
        void onVehicleRemoved(domain::AbstractVehicle* vehicle);

   private:
       VehicleService* m_vehicleService;
    };
}

#endif // MANUAL_HANDLER_H
