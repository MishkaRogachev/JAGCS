#ifndef FLIGHT_HANDLER_H
#define FLIGHT_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace data_source
{
    class FlightHandler: public AbstractMavLinkHandler
    {
    public:
        explicit FlightHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

    private:
        const domain::TelemetryService* m_telemetryService;
    };
}

#endif // FLIGHT_HANDLER_H
