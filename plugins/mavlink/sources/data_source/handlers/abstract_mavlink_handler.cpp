#include "abstract_mavlink_handler.h"

using namespace data_source;

AbstractMavLinkHandler::AbstractMavLinkHandler(MavLinkCommunicator* communicator):
    m_communicator(communicator)
{}

AbstractMavLinkHandler::~AbstractMavLinkHandler()
{}
