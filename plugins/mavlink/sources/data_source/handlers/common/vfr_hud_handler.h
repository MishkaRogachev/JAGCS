#ifndef VFR_HUD_HANDLER_H
#define VFR_HUD_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace data_source
{
    class VfrHudHandler: public AbstractMavLinkHandler
    {
    public:
        explicit VfrHudHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

    private:
        const domain::TelemetryService* m_telemetryService;
    };
}

#endif // VFR_HUD_HANDLER_H
