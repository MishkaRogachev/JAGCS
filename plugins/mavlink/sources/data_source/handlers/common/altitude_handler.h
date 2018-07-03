#ifndef ALTITUDE_HANDLER_H
#define ALTITUDE_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class AltitudeHandler: public AbstractMavLinkHandler
    {
    public:
        explicit AltitudeHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

    private:
        const domain::TelemetryService* m_telemetryService;
    };
}

#endif // ALTITUDE_HANDLER_H
