#ifndef NAV_CONTROLLER_HANDLER_H
#define NAV_CONTROLLER_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class NavControllerHandler: public AbstractMavLinkHandler
    {
    public:
        explicit NavControllerHandler(MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        domain::TelemetryService* m_telemetryService;
    };
}

#endif // NAV_CONTROLLER_HANDLER_H
