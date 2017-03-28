#ifndef WIND_HANDLER_H
#define WIND_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;

    class WindHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        WindHandler(VehicleService* vehicleService,
                    MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        VehicleService* m_vehicleService;
    };
}

#endif // WIND_HANDLER_H
