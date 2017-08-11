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
    QMap<uint8_t, AbstractLink*> mavSystemLinks;
    QList<uint8_t> avalibleChannels;
    AbstractLink* receivedLink = nullptr;
};

MavLinkCommunicator::MavLinkCommunicator(uint8_t systemId, uint8_t componentId, QObject* parent):
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

uint8_t MavLinkCommunicator::linkChannel(AbstractLink* link) const
{
    return d->linkChannels.value(link, 0);
}

AbstractLink* MavLinkCommunicator::lastReceivedLink() const
{
    return d->receivedLink;
}

AbstractLink* MavLinkCommunicator::mavSystemLink(uint8_t systemId)
{
    return d->mavSystemLinks.value(systemId, nullptr);
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

void MavLinkCommunicator::sendMessage(mavlink_message_t& message, AbstractLink* link)
{
    if (!link || !link->isConnected()) return;

    this->finalizeMessage(message);

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    int lenght = mavlink_msg_to_send_buffer(buffer, &message);

    if (!lenght) return;
    link->sendData(QByteArray((const char*)buffer, lenght));
}

void MavLinkCommunicator::onDataReceived(const QByteArray& data)
{
    d->receivedLink = qobject_cast<AbstractLink*>(this->sender());
    if (!d->receivedLink) return;

    mavlink_message_t message;
    mavlink_status_t status;

    uint8_t channel = this->linkChannel(d->receivedLink);
    for (int pos = 0; pos < data.length(); ++pos)
    {
        if (!mavlink_parse_char(channel, (uint8_t)data[pos],
                                &message, &status))
            continue;

        d->mavSystemLinks[message.sysid] = d->receivedLink;
        emit messageReceived(message);
    }

    d->receivedLink->setPacketsReceived(status.packet_rx_success_count);
    d->receivedLink->setPacketsDrops(status.packet_rx_drop_count);
}

void MavLinkCommunicator::finalizeMessage(mavlink_message_t& message)
{
    Q_UNUSED(message)
}
