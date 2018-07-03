#ifndef POSITION_HANDLER_H
#define POSITION_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class PositionHandler: public AbstractMavLinkHandler
    {
    public:
        explicit PositionHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

    private:
        const domain::TelemetryService* m_telemetryService;
    };
}
#endif // POSITION_HANDLER_H
