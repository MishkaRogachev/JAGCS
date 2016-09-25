#include "abstract_mavlink_handler.h"

using namespace data_source;

AbstractMavLinkHandler::AbstractMavLinkHandler()
{}

AbstractMavLinkHandler::~AbstractMavLinkHandler()
{}

bool AbstractMavLinkHandler::handleMessage(const mavlink_message_t& message)
{
    if (message.msgid == this->messageId())
    {
        this->processMessage(message);
        return true;
    }
    return false;
}
