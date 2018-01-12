#ifndef HIGH_LATENCY_HANDLER_H
#define HIGH_LATENCY_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class HighLatencyHandler: public AbstractMavLinkHandler
    {
    public:
        explicit HighLatencyHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

    private:
        const domain::TelemetryService* m_telemetryService;
    };
}

#endif // HIGH_LATENCY_HANDLER_H
