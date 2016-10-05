#include "request_handler.h"

// MAVLink
#include <mavlink.h>
// #include <mavlink_msg_request_data_stream.h>
#include <mavlink_msg_param_request_read.h>

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
{/*
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

    emit sendMessage(message);*/
}

void RequestHandler::sendRequest(uint8_t targetSystem)
{/*
    this->sendRequest(targetSystem, 1, 1, 2); // TODO: new style request
    this->sendRequest(targetSystem, 1, 2, 2);
    this->sendRequest(targetSystem, 1, 3, 2);
    this->sendRequest(targetSystem, 1, 6, 3);
    this->sendRequest(targetSystem, 1, 10, 10);
    this->sendRequest(targetSystem, 1, 11, 10);
    this->sendRequest(targetSystem, 1, 12, 3);*/

    mavlink_message_t message;
    mavlink_msg_param_request_read_pack(m_communicator->systemId(),
                                        m_communicator->componentId(),
                                        &message,
                                        targetSystem,
                                        1,
                                        "SYSID_SW_TYPE",
                                        -1);
}
