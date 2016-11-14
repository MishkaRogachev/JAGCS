#ifndef HOME_POSITION_HANDLER_H
#define HOME_POSITION_HANDLER_H

#include "abstract_mavlink_handler.h"

class QGeoCoordinate;

namespace domain
{
    class VehicleService;

    class HomePositionHandler: public AbstractMavLinkHandler
    {
    public:
        HomePositionHandler(VehicleService* vehicleService,
                            MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void sendHomePositionRequest();
        void sendHomePositionSetting(const QGeoCoordinate& position,
                                     const QVector3D& approach);

    private:
        VehicleService* m_vehicleService;
    };
}

#endif // HOMEPOSITIONHANDLER_H
