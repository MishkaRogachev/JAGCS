#ifndef SYSTEM_STATUS_HANDLER_H
#define SYSTEM_STATUS_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;
}

namespace comm
{
    class SystemStatusHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        SystemStatusHandler(domain::VehicleService* vehicleService,
                            MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        domain::VehicleService* m_vehicleService;
    };
}

#endif // SYSTEM_STATUS_HANDLER_H
