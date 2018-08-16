#ifndef IMU_HANDLER_H
#define IMU_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace data_source
{
    class ImuHandler: public AbstractMavLinkHandler
    {
    public:
        explicit ImuHandler(MavLinkCommunicator* communicator);

        void processMessage(const mavlink_message_t& message) override;

    private:
        const domain::TelemetryService* m_telemetryService;
    };
}

#endif // IMU_HANDLER_H
