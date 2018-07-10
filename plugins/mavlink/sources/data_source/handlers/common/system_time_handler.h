#ifndef SYSTEM_TIME_HANDLER_H
#define SYSTEM_TIME_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace data_source
{
    class SystemTimeHandler: public AbstractMavLinkHandler
    {
    public:
        explicit SystemTimeHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

    private:
        const domain::TelemetryService* m_telemetryService;
    };
}

#endif // SYSTEM_TIME_HANDLER_H
