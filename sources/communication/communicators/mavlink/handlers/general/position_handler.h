#ifndef POSITION_HANDLER_H
#define POSITION_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class PositionHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        explicit PositionHandler(MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        domain::TelemetryService* m_telemetryService;
    };
}
#endif // POSITION_HANDLER_H
