#ifndef BATTERY_HANDLER_H
#define BATTERY_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class BatteryHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        BatteryHandler(domain::TelemetryService* telemetryService,
                       MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        domain::TelemetryService* m_telemetryService;
    };
}

#endif // BATTERY_HANDLER_H
