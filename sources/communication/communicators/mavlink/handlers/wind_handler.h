#ifndef WIND_HANDLER_H
#define WIND_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class WindHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        WindHandler(MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        domain::TelemetryService* m_telemetryService;
    };
}

#endif // WIND_HANDLER_H
