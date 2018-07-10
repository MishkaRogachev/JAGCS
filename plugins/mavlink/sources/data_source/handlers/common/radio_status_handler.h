#ifndef RADIO_STATUS_HANDLER_H
#define RADIO_STATUS_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace data_source
{
    class RadioStatusHandler: public AbstractMavLinkHandler
    {
    public:
        explicit RadioStatusHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

    private:
        const domain::TelemetryService* m_telemetryService;
    };
}

#endif // RADIO_STATUS_HANDLER_H
