#include "abstract_mavlink_handler.h"

// Internal
#include "mavlink_communicator.h"

using namespace domain;

AbstractMavLinkHandler::AbstractMavLinkHandler(MavLinkCommunicator* communicator):
    QObject(communicator),
    m_communicator(communicator)
{
    Q_ASSERT(communicator);
    connect(communicator, &MavLinkCommunicator::messageReceived,
            this, &AbstractMavLinkHandler::processMessage);
}

AbstractMavLinkHandler::~AbstractMavLinkHandler()
{}
