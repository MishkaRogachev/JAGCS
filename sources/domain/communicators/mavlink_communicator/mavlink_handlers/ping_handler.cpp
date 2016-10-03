#include "ping_handler.h"

// MAVLink
#include <mavlink.h>
#include <mavlink_msg_ping.h>

// Internal
#include "mavlink_communicator.h"

using namespace domain;

PingHandler::PingHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_communicator(communicator)
{}

int PingHandler::messageId() const
{
    return MAVLINK_MSG_ID_PING;
}

void PingHandler::processMessage(const mavlink_message_t& message)
{
    mavlink_ping_t ping;
    mavlink_msg_ping_decode(&message, &ping);

    if (!ping.target_system && !ping.target_component)
    {
         mavlink_message_t response;
         mavlink_msg_ping_pack(m_communicator->systemId(),
                               m_communicator->componentId(),
                               &response, ping.time_usec, ping.seq,
                               message.sysid, message.compid);

         m_communicator->sendMessage(response);
    }
}
