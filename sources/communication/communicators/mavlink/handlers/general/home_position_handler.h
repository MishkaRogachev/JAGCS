#ifndef HOME_POSITION_HANDLER_H
#define HOME_POSITION_HANDLER_H

// Internal
#include "abstract_mavlink_handler.h"

namespace comm
{
    class HomePositionHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        HomePositionHandler(MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void sendHomePositionRequest(quint8 mavId);
    };
}

#endif // HOME_POSITION_HANDLER_H
