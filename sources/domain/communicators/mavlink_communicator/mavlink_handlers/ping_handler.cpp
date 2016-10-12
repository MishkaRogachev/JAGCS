#include "ping_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "mavlink_communicator.h"

using namespace domain;

PingHandler::PingHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_communicator(communicator)
{}

void PingHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_PING) return;

    mavlink_ping_t ping;
    mavlink_msg_ping_decode(&message, &ping);

    if (!ping.target_system && !ping.target_component)
    {
         mavlink_message_t response;
         mavlink_msg_ping_pack(m_communicator->systemId(),
                               m_communicator->componentId(),
                               &response, ping.time_usec, ping.seq,
                               message.sysid, message.compid);

         emit sendMessage(response);
    }
}
