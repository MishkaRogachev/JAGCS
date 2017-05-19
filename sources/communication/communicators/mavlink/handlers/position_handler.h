#ifndef POSITION_HANDLER_H
#define POSITION_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;
}

namespace comm
{
    class PositionHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        PositionHandler(domain::VehicleService* vehicleService,
                        MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        domain::VehicleService* m_vehicleService;
    };
}
#endif // POSITION_HANDLER_H
