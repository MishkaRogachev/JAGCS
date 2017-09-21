#ifndef MANUAL_CONTROL_HANDLER_H
#define MANUAL_CONTROL_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace comm
{
    class ManualControlHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        ManualControlHandler(MavLinkCommunicator* communicator);
        ~ManualControlHandler() override;

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void sendManualControl(int vehicledId, float pitch, float roll, float thrust, float yaw);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MANUAL_CONTROL_HANDLER_H
