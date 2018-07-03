#ifndef VIBRATION_HANDLER_H
#define VIBRATION_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class VibrationHandler: public AbstractMavLinkHandler
    {
    public:
        explicit VibrationHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

    private:
        const domain::TelemetryService* m_telemetryService;
    };
}

#endif // VIBRATION_HANDLER_H
