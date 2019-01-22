#ifndef GLOBAL_POI_HANDLER_H
#define GLOBAL_POI_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class GlobalPoiHandler: public AbstractMavLinkHandler
    {
    public:
        explicit GlobalPoiHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

    private:
        const domain::TelemetryService* m_telemetryService;
    };
}

#endif // GLOBAL_POI_HANDLER_H
