#ifndef HEARTBEAT_HANDLER_H
#define HEARTBEAT_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace db
{
    class DbFacade;
}

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class HeartbeatHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        HeartbeatHandler(db::DbFacade* dbFacade, domain::TelemetryService* telemetryService,
                         MavLinkCommunicator* communicator);
        ~HeartbeatHandler() override;

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void sendHeartbeat();

    protected:
        void timerEvent(QTimerEvent* event) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // HEARTBEAT_HANDLER_H
