#include "abstract_mavlink_handler.h"

// Internal
#include "mavlink_communicator.h"

using namespace domain;

AbstractMavLinkHandler::AbstractMavLinkHandler(
        data_source::MavLinkCommunicator* communicator):
    QObject(communicator),
    m_communicator(communicator)
{
    Q_ASSERT(communicator);
    connect(communicator, &data_source::MavLinkCommunicator::messageReceived,
            this, &AbstractMavLinkHandler::processMessage);
}

AbstractMavLinkHandler::~AbstractMavLinkHandler()
{}
