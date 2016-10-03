#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class MavLinkCommunicator;

    class RequestHandler: public AbstractMavLinkHandler
    {
    public:
        RequestHandler(MavLinkCommunicator* communicator);

        void sendRequest(uint8_t targetSystem, uint8_t targetComponent = 0);

    protected:
        int messageId() const override;
        void processMessage(const mavlink_message_t& message) override;

    private:
        MavLinkCommunicator* m_communicator;
    };
}

#endif // REQUESTHANDLER_H
