#ifndef INTERVAL_HANDLER_H
#define INTERVAL_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class IntervalHandler: public AbstractMavLinkHandler
    {
    public:
        IntervalHandler(MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void requestMessageFrequency(int messageId, float frequency);
    };
}

#endif // INTERVAL_HANDLER_H
