#ifndef ATTITUDE_HANDLER_H
#define ATTITUDE_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class AttitudeHandler: public AbstractMavLinkHandler
    {
    public:
        AttitudeHandler();

    protected:
        int messageId() const override;
        void processMessage(const mavlink_message_t& message) override;
    };
}

#endif // ATTITUDE_HANDLER_H
