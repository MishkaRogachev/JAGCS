#ifndef GPS_HANDLER_H
#define GPS_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;
}

namespace comm
{
    class GpsHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        GpsHandler(domain::VehicleService* vehicleService,
                   MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        domain::VehicleService* m_vehicleService;
    };
}

#endif // GPS_HANDLER_H
