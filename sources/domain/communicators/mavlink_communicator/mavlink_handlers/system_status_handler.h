#ifndef SYSTEM_STATUS_HANDLER_H
#define SYSTEM_STATUS_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class SystemStatusHandler: public AbstractMavLinkHandler
    {
    public:
        SystemStatusHandler();

    protected:
        int messageId() const override;
        void processMessage(const mavlink_message_t& message) override;
    };
}

#endif // SYSTEM_STATUS_HANDLER_H
