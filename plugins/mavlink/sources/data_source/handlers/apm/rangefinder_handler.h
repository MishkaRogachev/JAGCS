#ifndef RANGEFINDER_HANDLER_H
#define RANGEFINDER_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class RangefinderHandler: public AbstractMavLinkHandler
    {
    public:
        explicit RangefinderHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

    private:
        const domain::TelemetryService* m_telemetryService;
    };
}

#endif // RANGEFINDER_HANDLER_H
