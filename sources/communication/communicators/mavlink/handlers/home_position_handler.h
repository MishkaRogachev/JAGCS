#ifndef HOME_POSITION_HANDLER_H
#define HOME_POSITION_HANDLER_H

// Qt
#include <QMap>
#include <QBasicTimer>

// Internal
#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
    class Position;
}

namespace comm
{
    class HomePositionHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        HomePositionHandler(domain::TelemetryService* telemetryService,
                            MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void sendHomePositionRequest(uint8_t mavId);
        void sendHomePositionSetting(uint8_t mavId, const domain::Position& position);

    private:
        domain::TelemetryService* const m_telemetryService;
    };
}

#endif // HOMEPOSITIONHANDLER_H
