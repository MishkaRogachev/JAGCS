#ifndef GPS_RAW_HANDLER_H
#define GPS_RAW_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;

    class GpsRawHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        GpsRawHandler(VehicleService* vehicleService, QObject* parent = nullptr);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        VehicleService* m_vehicleService;
    };
}

#endif // GPS_RAW_HANDLER_H
