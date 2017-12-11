#ifndef GPS_HANDLER_H
#define GPS_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class GpsHandler: public AbstractMavLinkHandler
    {
    public:
        explicit GpsHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

    private:
        const domain::TelemetryService* m_telemetryService;
    };
}

#endif // GPS_HANDLER_H
