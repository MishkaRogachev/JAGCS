#ifndef SYSTEM_STATUS_HANDLER_H
#define SYSTEM_STATUS_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;

    class SystemStatusHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        SystemStatusHandler(VehicleService* vehicleService,
                            MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        VehicleService* m_vehicleService;
    };
}

#endif // SYSTEM_STATUS_HANDLER_H
