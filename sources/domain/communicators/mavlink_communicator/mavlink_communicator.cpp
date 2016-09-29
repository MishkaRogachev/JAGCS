#include "mavlink_communicator.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QMap>
#include <QDebug>

// Internal
#include "abstract_link.h"

#include "heartbeat_handler.h"
#include "attitude_handler.h"

// TODO: emit heartbeat, multiplexing, pings

using namespace domain;

class MavLinkCommunicator::Impl
{
public:
    QList<AbstractMavLinkHandler*> handlers;

    QMap<QObject*, uint8_t> linkChannels;
    QList<uint8_t> avalibleChannels;

    int systemId = 255;
    int componentId = 0;
};

MavLinkCommunicator::MavLinkCommunicator(VehicleService* vehicleService,
                                         QObject* parent):
    AbstractCommunicator(vehicleService, parent),
    d(new Impl())
{
    d->handlers.append(new HeartbeatHandler(m_vehicleService));
    d->handlers.append(new AttitudeHandler(m_vehicleService));

    d->avalibleChannels.append(MAVLINK_COMM_0);
    d->avalibleChannels.append(MAVLINK_COMM_1);
    d->avalibleChannels.append(MAVLINK_COMM_2);
    d->avalibleChannels.append(MAVLINK_COMM_3);
}

MavLinkCommunicator::~MavLinkCommunicator()
{
    while (!d->handlers.isEmpty())
    {
        delete d->handlers.takeLast();
    }

    delete d;
}

int MavLinkCommunicator::componentId() const
{
    return d->componentId;
}

int MavLinkCommunicator::systemId() const
{
    return d->systemId;
}

void MavLinkCommunicator::addLink(AbstractLink* link)
{
    if (d->linkChannels.contains(link) || d->avalibleChannels.isEmpty())
        return;

    d->linkChannels[link] = d->avalibleChannels.takeFirst();

    AbstractCommunicator::addLink(link);
}

void MavLinkCommunicator::removeLink(AbstractLink* link)
{
    if (!d->linkChannels.contains(link)) return;

    uint8_t channel = d->linkChannels.value(link);
    d->linkChannels.remove(link);
    d->avalibleChannels.prepend(channel);

    AbstractCommunicator::removeLink(link);
}

void MavLinkCommunicator::onDataReceived(const QByteArray& data)
{
    mavlink_message_t message;
    mavlink_status_t status;

    qDebug() << data.toHex();

    for (int pos = 0; pos < data.length(); ++pos)
    {
        if (!mavlink_parse_char(d->linkChannels.value(this->sender()),
                                (uint8_t)data[pos],
                                &message,
                                &status))
            continue;

        qDebug() << "Received packet: SYS: " << message.sysid <<
                    ", COMP: " << message.compid << "MSG ID: " <<
                    message.msgid;
        for (AbstractMavLinkHandler* handler: d->handlers)
        {
            if (handler->handleMessage(message)) break;
        }
    }

    // TODO: Link status
}

void MavLinkCommunicator::setComponentId(int componentId)
{
    d->componentId = componentId;
}

void MavLinkCommunicator::sendMessage(const mavlink_message_t& message)
{
    static uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    int lenght = mavlink_msg_to_send_buffer(buffer, &message);

    this->sendData(QByteArray((const char*)buffer, lenght));
}

void MavLinkCommunicator::setSystemId(int systemId)
{
    d->systemId = systemId;
}
