#ifndef PING_HANDLER_H
#define PING_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace comm
{
    class PingHandler: public AbstractMavLinkHandler
    {
    public:
        explicit PingHandler(MavLinkCommunicator* communicator); // TODO: send ping

        void processMessage(const mavlink_message_t& message) override;
    };
}

#endif // PING_HANDLER_H
