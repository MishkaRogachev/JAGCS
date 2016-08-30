#include "mavlink_abstract_link.h"

// MAVLink
#include <mavlink.h>

using namespace data_source::mavlink;

AbstractLink::AbstractLink(QObject* parent):
    QObject(parent)
{}

void AbstractLink::sendMessage(const mavlink_message_t& message)
{
    static uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    int lenght = mavlink_msg_to_send_buffer(buffer, &message);

    this->sendData(QByteArray((const char*)buffer, lenght));
}
