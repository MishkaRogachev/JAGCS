#ifndef VFR_HUD_HANDLER_H
#define VFR_HUD_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class VfrHudHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        VfrHudHandler(MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        domain::TelemetryService* m_telemetryService;
    };
}

#endif // VFR_HUD_HANDLER_H
