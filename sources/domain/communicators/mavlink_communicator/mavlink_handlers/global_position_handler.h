#ifndef GLOBAL_POSITION_HANDLER_H
#define GLOBAL_POSITION_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;

    class GlobalPositionHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        GlobalPositionHandler(VehicleService* vehicleService,
                              QObject* parent = nullptr);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        VehicleService* m_vehicleService;
    };
}
#endif // GLOBAL_POSITION_HANDLER_H
