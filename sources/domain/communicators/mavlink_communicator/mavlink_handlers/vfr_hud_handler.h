#ifndef VFR_HUD_HANDLER_H
#define VFR_HUD_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;

    class VfrHudHandler: public AbstractMavLinkHandler
    {
    public:
        VfrHudHandler(VehicleService* vehicleService);

    protected:
        int messageId() const override;
        void processMessage(const mavlink_message_t& message) override;

    private:
        VehicleService* m_vehicleService;
    };
}

#endif // VFR_HUD_HANDLER_H
