#ifndef ABSTRACT_MAVLINK_HANDLER_H
#define ABSTRACT_MAVLINK_HANDLER_H

// MAVLink
#include <mavlink_types.h>

namespace domain
{
    class AbstractMavLinkHandler
    {
    public:
        AbstractMavLinkHandler();
        virtual ~AbstractMavLinkHandler();

        bool handleMessage(const mavlink_message_t& message);

    protected:
        virtual int messageId() const = 0;
        virtual void processMessage(const mavlink_message_t& message) = 0;
    };
}

#endif // ABSTRACT_MAVLINK_HANDLER_H
