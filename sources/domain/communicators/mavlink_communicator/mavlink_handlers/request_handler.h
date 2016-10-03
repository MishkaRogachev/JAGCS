#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class MavLinkCommunicator;

    class RequestHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        RequestHandler(MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void sendRequest(uint8_t targetSystem, uint8_t targetComponent);
        void sendRequest(uint8_t targetSystem);

    private:
        MavLinkCommunicator* m_communicator;
    };
}

#endif // REQUESTHANDLER_H
