#ifndef ATTITUDE_TARGET_HANDLER_H
#define ATTITUDE_TARGET_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class AttitudeTargetHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        explicit AttitudeTargetHandler(MavLinkCommunicator* communicator);
        ~AttitudeTargetHandler() override;

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void sendAttitude(int vehicledId, float pitch, float roll, float thrust, float yaw);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // ATTITUDE_TARGET_HANDLER_H
