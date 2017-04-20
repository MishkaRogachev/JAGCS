#ifndef HEARTBEAT_HANDLER_H
#define HEARTBEAT_HANDLER_H

#include "abstract_mavlink_handler.h"

class QTimer;

namespace data_source
{
    class MavLinkCommunicator;
}

namespace domain
{
    class VehicleService;

    class HeartbeatHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        HeartbeatHandler(VehicleService* vehicleService,
                         data_source::MavLinkCommunicator* communicator);
        ~HeartbeatHandler() override;

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void sendHeartbeat();

    private:
        VehicleService* m_vehicleService;
        QTimer* m_timer;
    };
}

#endif // HEARTBEAT_HANDLER_H
