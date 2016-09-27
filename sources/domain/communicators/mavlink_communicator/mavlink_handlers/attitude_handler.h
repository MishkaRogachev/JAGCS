#ifndef ATTITUDE_HANDLER_H
#define ATTITUDE_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;

    class AttitudeHandler: public AbstractMavLinkHandler
    {
    public:
        AttitudeHandler(VehicleService* vehicleService);

    protected:
        int messageId() const override;
        void processMessage(const mavlink_message_t& message) override;

    private:
        VehicleService* m_vehicleService;
    };
}

#endif // ATTITUDE_HANDLER_H
