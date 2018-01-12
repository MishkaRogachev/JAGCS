#ifndef MANUAL_CONTROL_HANDLER_H
#define MANUAL_CONTROL_HANDLER_H

// Qt
#include <QObject>

// Internal
#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;
}

namespace comm
{
    class ManualControlHandler: public QObject, public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        explicit ManualControlHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

    public slots:
        void sendManualControl(int vehicledId, float pitch, float roll, float thrust, float yaw);

    private:
        const domain::VehicleService* m_vehicleService;
    };
}

#endif // MANUAL_CONTROL_HANDLER_H
