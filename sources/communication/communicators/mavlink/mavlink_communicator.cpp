#include "mavlink_communicator.h"

// MAVLink
#include <mavlink.h>
#include <mavlink_types.h>
#include <mavlink_helpers.h>

// Qt
#include <QMap>
#include <QDebug>

// Internal
#include "abstract_link.h"

// TODO: multiplexing

using namespace comm;

class MavLinkCommunicator::Impl
{
public:
    uint8_t systemId;
    uint8_t componentId;

    QMap<AbstractLink*, uint8_t> linkChannels;
    QList<uint8_t> avalibleChannels;
    AbstractLink* receivedLink = nullptr;
};

MavLinkCommunicator::MavLinkCommunicator(uint8_t systemId, uint8_t componentId,
                                         QObject* parent):
    AbstractCommunicator(parent),
    d(new Impl())
{
    qRegisterMetaType<mavlink_message_t>("mavlink_message_t");

    d->systemId = systemId;
    d->componentId = componentId;

    for (uint8_t channel = 0; channel < MAVLINK_COMM_NUM_BUFFERS; ++channel)
        d->avalibleChannels.append(channel);
}

MavLinkCommunicator::~MavLinkCommunicator()
{}

bool MavLinkCommunicator::isAddLinkEnabled()
{
    return !d->avalibleChannels.isEmpty();
}

uint8_t MavLinkCommunicator::componentId() const
{
    return d->componentId;
}

AbstractLink* MavLinkCommunicator::receivedLink() const
{
    return d->receivedLink;
}

uint8_t MavLinkCommunicator::systemId() const
{
    return d->systemId;
}

void MavLinkCommunicator::addLink(AbstractLink* link)
{
    if (d->linkChannels.contains(link) || d->avalibleChannels.isEmpty())
        return;

    d->linkChannels[link] = d->avalibleChannels.takeFirst();
    if (d->avalibleChannels.isEmpty()) emit addLinkEnabledChanged(false);

    AbstractCommunicator::addLink(link);
}

void MavLinkCommunicator::removeLink(AbstractLink* link)
{
    if (!d->linkChannels.contains(link)) return;

    uint8_t channel = d->linkChannels.value(link);
    d->linkChannels.remove(link);
    d->avalibleChannels.prepend(channel);
    mavlink_reset_channel_status(channel);

    if (link == d->receivedLink) d->receivedLink = nullptr;

    if (!d->avalibleChannels.isEmpty()) emit addLinkEnabledChanged(true);

    AbstractCommunicator::removeLink(link);
}

void MavLinkCommunicator::setSystemId(uint8_t systemId)
{
    if (d->systemId == systemId) return;

    d->systemId = systemId;
    emit systemIdChanged(systemId);
}

void MavLinkCommunicator::setComponentId(uint8_t componentId)
{
    if (d->componentId == componentId) return;

    d->componentId = componentId;
    emit componentIdChanged(componentId);
}

void MavLinkCommunicator::sendMessage(mavlink_message_t& message,
                                      AbstractLink* link)
{
    if (!link || !link->isConnected()) return;

    static const uint8_t messageKeys[256] = MAVLINK_MESSAGE_CRCS;
    mavlink_finalize_message_chan(&message,
                                  d->systemId,
                                  d->componentId,
                                  d->linkChannels.value(link, 0),
                                  message.len,
                                  message.len,
                                  messageKeys[message.msgid]);

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    int lenght = mavlink_msg_to_send_buffer(buffer, &message);

    if (!lenght) return;
    link->sendData(QByteArray((const char*)buffer, lenght));
}

void MavLinkCommunicator::sendMessageLastReceivedLink(mavlink_message_t& message)
{
    this->sendMessage(message, d->receivedLink);
}

void MavLinkCommunicator::sendMessageAllLinks(mavlink_message_t& message)
{
    for (AbstractLink* link: d->linkChannels.keys())
        this->sendMessage(message, link);
}

void MavLinkCommunicator::onDataReceived(const QByteArray& data)
{
    mavlink_message_t message;
    mavlink_status_t status;

    d->receivedLink = qobject_cast<AbstractLink*>(this->sender());
    if (!d->receivedLink) return;

    uint8_t channel = d->linkChannels.value(d->receivedLink);
    for (int pos = 0; pos < data.length(); ++pos)
    {
        if (!mavlink_parse_char(channel, (uint8_t)data[pos],
                                &message, &status))
            continue;

        emit messageReceived(message);
    }

    d->receivedLink->setPacketsReceived(status.packet_rx_success_count);
    d->receivedLink->setPacketsDrops(status.packet_rx_drop_count);
}
