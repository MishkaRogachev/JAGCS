#ifndef GPS_HANDLER_H
#define GPS_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;

    class GpsHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        GpsHandler(VehicleService* vehicleService,
                   data_source::MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        VehicleService* m_vehicleService;
    };
}

#endif // GPS_HANDLER_H
