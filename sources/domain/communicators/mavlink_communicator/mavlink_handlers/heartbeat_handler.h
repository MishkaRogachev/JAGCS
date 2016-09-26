#ifndef HEARTBEAT_HANDLER_H
#define HEARTBEAT_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class HeartbeatHandler: public AbstractMavLinkHandler
    {
    public:
        HeartbeatHandler();

    protected:
        int messageId() const override;
        void processMessage(const mavlink_message_t& message) override;
    };
}

#endif // HEARTBEAT_HANDLER_H
