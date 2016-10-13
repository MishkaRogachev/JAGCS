#ifndef PING_HANDLER_H
#define PING_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class MavLinkCommunicator;

    class PingHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        PingHandler(MavLinkCommunicator* communicator); // TODO: send ping

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        MavLinkCommunicator* m_communicator;
    };
}

#endif // PING_HANDLER_H
