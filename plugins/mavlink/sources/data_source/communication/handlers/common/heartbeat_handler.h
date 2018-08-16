#ifndef HEARTBEAT_HANDLER_H
#define HEARTBEAT_HANDLER_H

// Qt
#include <QObject>

// Internal
#include "abstract_mavlink_handler.h"

namespace data_source
{
    class HeartbeatHandler: public QObject, public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        explicit HeartbeatHandler(MavLinkCommunicator* communicator);
        ~HeartbeatHandler() override;

        void processMessage(const mavlink_message_t& message) override;

    public slots:
        void sendHeartbeat();

    protected:
        void timerEvent(QTimerEvent* event) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // HEARTBEAT_HANDLER_H
