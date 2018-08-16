#ifndef WIND_HANDLER_H
#define WIND_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace data_source
{
    class WindHandler: public AbstractMavLinkHandler
    {
    public:
        explicit WindHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

    private:
        const domain::TelemetryService* m_telemetryService;
    };
}

#endif // WIND_HANDLER_H
