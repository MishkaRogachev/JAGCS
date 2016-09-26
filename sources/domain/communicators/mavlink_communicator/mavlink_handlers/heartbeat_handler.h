#ifndef HEARTBEAT_HANDLER_H
#define HEARTBEAT_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;

    class HeartbeatHandler: public AbstractMavLinkHandler
    {
    public:
        HeartbeatHandler(VehicleService* vehicleService);

    protected:
        int messageId() const override;
        void processMessage(const mavlink_message_t& message) override;

    private:
        VehicleService* m_vehicleService;
    };
}

#endif // HEARTBEAT_HANDLER_H
