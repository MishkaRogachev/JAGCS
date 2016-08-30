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

void AbstractLink::resolveData(const QByteArray& data)
{
    mavlink_message_t message;
    mavlink_status_t status;

    for (int pos = 0; pos < data.length(); ++pos)
    {
        if (!mavlink_parse_char(MAVLINK_COMM_0,  // TODO: MAVLINK channel
                                (uint8_t)data[pos],
                                &message,
                                &status))
            continue;

        emit messageReceived(message);
    }
}
