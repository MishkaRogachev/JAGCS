#ifndef EKF_STATUS_HANDLER_H
#define EKF_STATUS_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class EkfStatusHandler: public AbstractMavLinkHandler
    {
    public:
        explicit EkfStatusHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

    private:
        const domain::TelemetryService* m_telemetryService;
    };
}

#endif // EKF_STATUS_HANDLER_H
