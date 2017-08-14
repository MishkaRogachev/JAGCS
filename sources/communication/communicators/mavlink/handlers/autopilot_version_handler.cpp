#include "autopilot_version_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QMap>
#include <QTimerEvent>
#include <QDebug>

// Internal
#include "mavlink_communicator.h"

namespace
{
    const int interval = 2000;
}

using namespace comm;
using namespace domain;

class AutopilotVersionHandler::Impl
{
public:
    QMap<uint8_t, int> mavTimers;
    QMap<uint8_t, bool> obtainedMavs;
};

AutopilotVersionHandler::AutopilotVersionHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    d(new Impl())
{}

AutopilotVersionHandler::~AutopilotVersionHandler()
{}

void AutopilotVersionHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid == MAVLINK_MSG_ID_AUTOPILOT_VERSION)
    {
        d->obtainedMavs[message.sysid] = true;
        if (d->mavTimers.contains(message.sysid))
        {
            this->killTimer(d->mavTimers.take(message.sysid));
        }

        mavlink_autopilot_version_t version;
        mavlink_msg_autopilot_version_decode(&message, &version);

        if (version.capabilities & MAV_PROTOCOL_CAPABILITY_MAVLINK2) this->sendAck(message.sysid);
    }
    else if (!d->obtainedMavs.value(message.sysid, false) &&
             !d->mavTimers.contains(message.sysid))
    {
        d->mavTimers[message.sysid] = this->startTimer(::interval);
    }
}

void AutopilotVersionHandler::requestVersion(uint8_t mavId)
{
    mavlink_message_t message;
    mavlink_command_long_t mavCommand;

    mavCommand.target_system = mavId;
    mavCommand.target_component = 0;
    mavCommand.confirmation = 0;
    mavCommand.command = MAV_CMD_REQUEST_PROTOCOL_VERSION;

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_msg_command_long_encode_chan(m_communicator->systemId(),
                                         m_communicator->componentId(),
                                         m_communicator->linkChannel(link),
                                         &message, &mavCommand);
    m_communicator->sendMessage(message, link);
}

void AutopilotVersionHandler::sendAck(uint8_t mavId)
{
    mavlink_message_t message;
    mavlink_mission_ack_t ackItem;

    ackItem.target_system = mavId;
    ackItem.target_component = 0;
    ackItem.type = MAV_MISSION_ACCEPTED;

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_msg_mission_ack_encode_chan(m_communicator->systemId(),
                                        m_communicator->componentId(),
                                        m_communicator->linkChannel(link),
                                        &message, &ackItem);
    m_communicator->sendMessage(message, link);
}

void AutopilotVersionHandler::timerEvent(QTimerEvent* event)
{
    this->requestVersion(d->mavTimers.key(event->timerId()));
}
