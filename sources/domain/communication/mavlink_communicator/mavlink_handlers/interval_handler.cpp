#include "interval_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "mavlink_communicator.h"

#include "mavlink_protocol_helpers.h"

using namespace domain;

IntervalHandler::IntervalHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator)
{}

void IntervalHandler::processMessage(const mavlink_message_t& message)
{
    //TODO: caluclate every recv message frequency
}

void IntervalHandler::requestMessageFrequency(int messageId, float frequency)
{
    mavlink_message_t message;
    mavlink_message_interval_t interval;

    interval.message_id = messageId;
    interval.interval_us = ::hzToUs(frequency);

    mavlink_msg_message_interval_encode(m_communicator->systemId(),
                                        m_communicator->componentId(),
                                        &message, &interval);

    m_communicator->sendMessageAllLinks(message);
}
