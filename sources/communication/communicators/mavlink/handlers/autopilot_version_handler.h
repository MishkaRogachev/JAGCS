#ifndef AUTOPILOT_VERSION_HANDLER_H
#define AUTOPILOT_VERSION_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class AutopilotVersionHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        AutopilotVersionHandler(MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        domain::TelemetryService* m_telemetryService;
    };
}

#endif // AUTOPILOT_VERSION_HANDLER_H
