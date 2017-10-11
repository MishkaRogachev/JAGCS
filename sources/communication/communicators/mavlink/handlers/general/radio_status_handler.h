#ifndef RADIO_STATUS_HANDLER_H
#define RADIO_STATUS_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class RadioStatusHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        explicit RadioStatusHandler(MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        domain::TelemetryService* m_telemetryService;
    };
}

#endif // RADIO_STATUS_HANDLER_H
