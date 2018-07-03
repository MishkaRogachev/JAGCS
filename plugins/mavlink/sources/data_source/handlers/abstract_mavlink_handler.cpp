#include "abstract_mavlink_handler.h"

using namespace comm;

AbstractMavLinkHandler::AbstractMavLinkHandler(MavLinkCommunicator* communicator):
    m_communicator(communicator)
{}

AbstractMavLinkHandler::~AbstractMavLinkHandler()
{}
