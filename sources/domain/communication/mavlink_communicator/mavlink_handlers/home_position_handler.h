#ifndef HOME_POSITION_HANDLER_H
#define HOME_POSITION_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;

    class HomePositionHandler: public AbstractMavLinkHandler
    {
    public:
        HomePositionHandler(VehicleService* vehicleService,
                            MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        VehicleService* m_vehicleService;
    };
}

#endif // HOMEPOSITIONHANDLER_H
