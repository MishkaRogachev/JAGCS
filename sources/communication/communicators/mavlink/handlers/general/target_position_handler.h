#ifndef TARGET_POSITION_HANDLER_H
#define TARGET_POSITION_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class TargetPositionHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        explicit TargetPositionHandler(MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        domain::TelemetryService* m_telemetryService;
    };
}
#endif // TARGET_POSITION_HANDLER_H
