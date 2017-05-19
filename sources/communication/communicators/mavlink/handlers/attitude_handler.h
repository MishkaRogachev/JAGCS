#ifndef ATTITUDE_HANDLER_H
#define ATTITUDE_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;
}

namespace comm
{
    class AttitudeHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        AttitudeHandler(domain::VehicleService* vehicleService,
                        MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        domain::VehicleService* m_vehicleService;
    };
}

#endif // ATTITUDE_HANDLER_H
