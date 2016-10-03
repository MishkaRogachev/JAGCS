#ifndef HEARTBEAT_HANDLER_H
#define HEARTBEAT_HANDLER_H

#include "abstract_mavlink_handler.h"

class QTimer;

namespace domain
{
    class VehicleService;
    class MavLinkCommunicator;

    class HeartbeatHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        HeartbeatHandler(VehicleService* vehicleService,
                         MavLinkCommunicator* communicator);
        ~HeartbeatHandler() override;

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void sendHeartbeat();

    private:
        VehicleService* m_vehicleService;
        MavLinkCommunicator* m_communicator;
        QTimer* m_timer;
    };
}

#endif // HEARTBEAT_HANDLER_H
