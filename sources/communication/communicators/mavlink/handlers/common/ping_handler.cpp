#include "ping_handler.h"

// SwarmLink
#include <swarmlink/mavlink.h>

// Internal
#include "mavlink_communicator.h"

using namespace comm;

PingHandler::PingHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator)
{}

void PingHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_PING) return;

    mavlink_ping_t ping;
    mavlink_msg_ping_decode(&message, &ping);

    AbstractLink* link = m_communicator->lastReceivedLink();
    if (link &&
        (ping.target_system == m_communicator->systemId() || ping.target_system == 0) &&
        (ping.target_component == m_communicator->componentId() || ping.target_component == 0))
    {
        mavlink_message_t response;

        mavlink_msg_ping_pack_chan(m_communicator->systemId(),
                                   m_communicator->componentId(),
                                   m_communicator->linkChannel(link),
                                   &response, ping.time_usec, ping.seq,
                                   message.sysid, message.compid);

        m_communicator->sendMessage(response, link);
    }
}
