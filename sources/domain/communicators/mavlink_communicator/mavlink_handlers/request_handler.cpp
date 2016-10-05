#include "request_handler.h"

// MAVLink
#include <mavlink.h>
#include <mavlink_msg_request_data_stream.h>

// Internal
#include "mavlink_communicator.h"

using namespace domain;

RequestHandler::RequestHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_communicator(communicator)
{}

void RequestHandler::processMessage(const mavlink_message_t& message)
{
    Q_UNUSED(message);
}

void RequestHandler::sendRequest(uint8_t targetSystem, uint8_t targetComponent,
                                 uint8_t stream, uint16_t rate)
{
    mavlink_message_t message;
    mavlink_request_data_stream_t dataStream;

    dataStream.req_stream_id = stream;
    dataStream.req_message_rate = rate;
    dataStream.start_stop = 1;  // start
    dataStream.target_system = targetSystem;
    dataStream.target_component = targetComponent;

    mavlink_msg_request_data_stream_encode(m_communicator->systemId(),
                                           m_communicator->componentId(),
                                           &message,
                                           &dataStream);

    emit sendMessage(message);
}

void RequestHandler::sendRequest(uint8_t targetSystem)
{
    this->sendRequest(targetSystem, 0, 1, 2); // TODO: new style request
    this->sendRequest(targetSystem, 0, 2, 2);
    this->sendRequest(targetSystem, 0, 3, 2);
    this->sendRequest(targetSystem, 0, 6, 3);
    this->sendRequest(targetSystem, 0, 10, 10);
    this->sendRequest(targetSystem, 0, 11, 10);
    this->sendRequest(targetSystem, 0, 12, 3);
}
