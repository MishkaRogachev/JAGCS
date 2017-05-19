#ifndef VFR_HUD_HANDLER_H
#define VFR_HUD_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;
}

namespace comm
{
    class VfrHudHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        VfrHudHandler(domain::VehicleService* vehicleService,
                      MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        domain::VehicleService* m_vehicleService;
    };
}

#endif // VFR_HUD_HANDLER_H
