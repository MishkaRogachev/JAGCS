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
#include "abstract_mavlink_handler.h"

using namespace comm;

class MavLinkCommunicator::Impl
{
public:
    quint8 systemId;
    quint8 componentId;

    QMap<AbstractLink*, quint8> linkChannels;
    QMap<quint8, AbstractLink*> mavSystemLinks;
    QList<quint8> avalibleChannels;
    AbstractLink* receivedLink = nullptr;

    QList<AbstractMavLinkHandler*> handlers;

    int oldPacketsReceived = 0;
    int oldPacketsDrops = 0;
};

MavLinkCommunicator::MavLinkCommunicator(quint8 systemId, quint8 componentId, QObject* parent):
    AbstractCommunicator(parent),
    d(new Impl())
{
    qRegisterMetaType<mavlink_message_t>("mavlink_message_t");

    d->systemId = systemId;
    d->componentId = componentId;

    for (quint8 channel = 0; channel < MAVLINK_COMM_NUM_BUFFERS; ++channel)
    {
        d->avalibleChannels.append(channel);
    }
}

MavLinkCommunicator::~MavLinkCommunicator()
{
    while (!d->handlers.isEmpty())
    {
        delete d->handlers.takeLast();
    }
}

bool MavLinkCommunicator::isAddLinkEnabled()
{
    return !d->avalibleChannels.isEmpty();
}

quint8 MavLinkCommunicator::systemId() const
{
    return d->systemId;
}

quint8 MavLinkCommunicator::componentId() const
{
    return d->componentId;
}

quint8 MavLinkCommunicator::linkChannel(AbstractLink* link) const
{
    return d->linkChannels.value(link, 0);
}

AbstractLink* MavLinkCommunicator::lastReceivedLink() const
{
    return d->receivedLink;
}

AbstractLink* MavLinkCommunicator::mavSystemLink(quint8 systemId)
{
    return d->mavSystemLinks.value(systemId, nullptr);
}

void MavLinkCommunicator::addLink(AbstractLink* link)
{
    if (d->linkChannels.contains(link) || d->avalibleChannels.isEmpty()) return;

    d->linkChannels[link] = d->avalibleChannels.takeFirst();
    if (d->avalibleChannels.isEmpty()) emit addLinkEnabledChanged(false);

    AbstractCommunicator::addLink(link);
}

void MavLinkCommunicator::removeLink(AbstractLink* link)
{
    if (!d->linkChannels.contains(link)) return;

    quint8 channel = d->linkChannels.value(link);
    d->linkChannels.remove(link);
    d->avalibleChannels.prepend(channel);

    quint8 mavId = d->mavSystemLinks.key(link, 0);
    if (mavId) d->mavSystemLinks.remove(mavId);

    if (link == d->receivedLink) d->receivedLink = nullptr;

    if (!d->avalibleChannels.isEmpty()) emit addLinkEnabledChanged(true);

    AbstractCommunicator::removeLink(link);
}

void MavLinkCommunicator::switchLinkProtocol(AbstractLink* link, AbstractCommunicator::Protocol protocol)
{
#ifdef MAVLINK_V2
    mavlink_status_t* channelStatus = mavlink_get_channel_status(this->linkChannel(link));
    bool outMavlink1 = channelStatus->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1;

    if (protocol == AbstractCommunicator::MavLink1 && !outMavlink1)
    {
        channelStatus->flags |= MAVLINK_STATUS_FLAG_OUT_MAVLINK1;
    }
    else if (protocol == AbstractCommunicator::MavLink2 && outMavlink1)
    {
        channelStatus->flags &= ~MAVLINK_STATUS_FLAG_OUT_MAVLINK1;
    }

    emit mavLinkProtocolChanged(link, channelStatus->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1 ?
                                    MavLink1 : MavLink2);
#endif
    emit mavLinkProtocolChanged(link, MavLink1);
}

void MavLinkCommunicator::setSystemId(quint8 systemId)
{
    if (d->systemId == systemId) return;

    d->systemId = systemId;
    emit systemIdChanged(systemId);
}

void MavLinkCommunicator::setComponentId(quint8 componentId)
{
    if (d->componentId == componentId) return;

    d->componentId = componentId;
    emit componentIdChanged(componentId);
}

void MavLinkCommunicator::addHandler(AbstractMavLinkHandler* handler)
{
    d->handlers.append(handler);
}

void MavLinkCommunicator::sendMessage(mavlink_message_t& message, AbstractLink* link)
{
    if (!link || !link->isConnected()) return;

    this->finalizeMessage(message);

    quint8 buffer[MAVLINK_MAX_PACKET_LEN];
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

    quint8 channel = this->linkChannel(d->receivedLink);
    for (int pos = 0; pos < data.length(); ++pos)
    {
        if (!mavlink_parse_char(channel, (quint8)data[pos], &message, &status)) continue;

#ifdef MAVLINK_V2
        // if we got MavLink v2, switch to on it!
        mavlink_status_t* channelStatus = mavlink_get_channel_status(channel);
        if (!(channelStatus->flags & MAVLINK_STATUS_FLAG_IN_MAVLINK1))
        {
            this->switchLinkProtocol(d->receivedLink, MavLink2);
        }
#endif

        d->mavSystemLinks[message.sysid] = d->receivedLink;

        for (AbstractMavLinkHandler* handler: d->handlers)
        {
            handler->processMessage(message);
        }
    }

    if (d->oldPacketsReceived != status.packet_rx_success_count ||
        d->oldPacketsDrops != status.packet_rx_drop_count)
    {
        emit mavLinkStatisticsChanged(d->receivedLink,
                                      status.packet_rx_success_count,
                                      status.packet_rx_drop_count);

        d->oldPacketsReceived = status.packet_rx_success_count;
        d->oldPacketsDrops = status.packet_rx_drop_count;
    }
}

void MavLinkCommunicator::finalizeMessage(mavlink_message_t& message)
{
    Q_UNUSED(message)
}
