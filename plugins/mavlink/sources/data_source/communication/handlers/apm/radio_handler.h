#ifndef RADIO_HANDLER_H
#define RADIO_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace data_source
{
    class RadioHandler: public AbstractMavLinkHandler
    {
    public:
        explicit RadioHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

    private:
        const domain::TelemetryService* m_telemetryService;
    };
}

#endif // RADIO_HANDLER_H
