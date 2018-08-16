#ifndef ATTITUDE_TARGET_HANDLER_H
#define ATTITUDE_TARGET_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;
}

namespace data_source
{
    class AttitudeTargetHandler: public AbstractMavLinkHandler
    {
    public:
        explicit AttitudeTargetHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

        void sendAttitude(int vehicledId, float pitch, float roll, float thrust, float yaw);

    private:
        const domain::VehicleService* m_vehicleService;
    };
}

#endif // ATTITUDE_TARGET_HANDLER_H
