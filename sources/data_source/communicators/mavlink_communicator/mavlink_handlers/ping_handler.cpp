#include "ping_handler.h"

// MAVLink
#include <mavlink.h>
#include <mavlink_msg_ping.h>

using namespace data_source;

PingHandler::PingHandler(int systemId, int componentId):
    AbstractMavLinkHandler(),
    m_systemId(systemId),
    m_componentId(componentId)
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
         mavlink_message_t msg;
         mavlink_msg_ping_pack(m_systemId, m_componentId, &msg,
                               ping.time_usec, ping.seq,
                               message.sysid, message.compid);

         // TODO: send ping response
    }
}

int PingHandler::componentId() const
{
    return m_componentId;
}

void PingHandler::setComponentId(int componentId)
{
    m_componentId = componentId;
}

int PingHandler::systemId() const
{
    return m_systemId;
}

void PingHandler::setSystemId(int systemId)
{
    m_systemId = systemId;
}
