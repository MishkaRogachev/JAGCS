#ifndef ABSTRACT_MAVLINK_HANDLER_H
#define ABSTRACT_MAVLINK_HANDLER_H

// MAVLink
#include <mavlink_types.h>

namespace data_source
{
    class MavLinkCommunicator;

    class AbstractMavLinkHandler // To Processor
    {
    public:
        explicit AbstractMavLinkHandler(MavLinkCommunicator* communicator);
        virtual ~AbstractMavLinkHandler();

        virtual void processMessage(const mavlink_message_t& message) = 0;

    protected:
        MavLinkCommunicator* const m_communicator;
    };
}

#endif // ABSTRACT_MAVLINK_HANDLER_H
