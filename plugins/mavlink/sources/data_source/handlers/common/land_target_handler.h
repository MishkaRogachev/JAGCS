#ifndef LAND_TARGET_HANDLER_H
#define LAND_TARGET_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class LandTargetHandler: public AbstractMavLinkHandler
    {
    public:
        explicit LandTargetHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

    private:
        const domain::TelemetryService* m_telemetryService;
    };
}

#endif // LAND_TARGET_HANDLER_H
