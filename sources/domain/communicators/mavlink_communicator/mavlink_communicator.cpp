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

// TODO: send packets, emit heartbeat, systemId=255, multiplexing

using namespace domain;

class MavLinkCommunicator::Impl
{
public:
    QList<AbstractMavLinkHandler*> handlers;
    QMap<AbstractLink*, uint8_t> linkChannels;
    QList<uint8_t> avalibleChannels;
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

QList<AbstractLink*> MavLinkCommunicator::links() const
{
    return d->linkChannels.keys();
}

void MavLinkCommunicator::addLink(AbstractLink* link)
{
    if (d->linkChannels.contains(link) || d->avalibleChannels.isEmpty())
        return;

    d->linkChannels[link] = d->avalibleChannels.takeFirst();

    link->setParent(this);

    connect(link, &AbstractLink::dataReceived,
            this, &MavLinkCommunicator::onDataReceived);

    emit linksChanged(this->links());
}

void MavLinkCommunicator::removeLink(AbstractLink* link)
{
    if (!d->linkChannels.contains(link)) return;

    uint8_t channel = d->linkChannels.value(link);
    d->linkChannels.remove(link);
    d->avalibleChannels.prepend(channel);

    if (link->parent() == this) link->setParent(nullptr);

    disconnect(link, &AbstractLink::dataReceived,
            this, &MavLinkCommunicator::onDataReceived);

    emit linksChanged(this->links());
}

void MavLinkCommunicator::onDataReceived(const QByteArray& data)
{
    mavlink_message_t message;
    mavlink_status_t status;

    qDebug() << data.toHex();

    AbstractLink* link = qobject_cast<AbstractLink*>(this->sender());

    for (int pos = 0; pos < data.length(); ++pos)
    {
        if (!mavlink_parse_char(d->linkChannels.value(link),
                                data[pos],
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


/*
// MAVLink
#include <mavlink_msg_ping.h>

// Qt
#include <QDebug>

using namespace domain;
using namespace domain::mavlink;

class Communicator::Impl
{
public:
    Communicator* p;
    QList<AbstractLink*> links;
    int systemId = 0;
    int componentId = 0;

    Impl(Communicator* p):
        p(p)
    {}


};

Communicator::Communicator(QObject* parent):
    QObject(parent),
    d(new Impl(this))
{}

Communicator::~Communicator()
{
    delete d;
}

QList<AbstractLink*> Communicator::links() const
{
    return d->links;
}

void Communicator::addLink(AbstractLink* link)
{
    link->setParent(this);

    d->links.append(link);

    connect(link, &AbstractLink::dataReceived, this, &Communicator::handleData);
}

void Communicator::removeLink(AbstractLink* link)
{
    if (link->parent() == this) link->setParent(nullptr);

    d->links.removeOne(link);

    disconnect(link, &AbstractLink::dataReceived, this, &Communicator::handleData);
}

void Communicator::sendSetPositionTargetLocal(
        const mavlink_set_position_target_local_ned_t& setPoint)
{
    mavlink_message_t message;
    mavlink_msg_set_position_target_local_ned_encode(
                d->systemId, d->componentId, &message, &setPoint);

    this->sendMessage(message);
}

void Communicator::sendCommandLong(const mavlink_command_long_t& com)
{
    mavlink_message_t message;
    mavlink_msg_command_long_encode(d->systemId, d->componentId, &message, &com);

    this->sendMessage(message);
}

void Communicator::sendMessage(const mavlink_message_t& message)
{
    static uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    int lenght = mavlink_msg_to_send_buffer(buffer, &message);
    QByteArray data((const char*)buffer, lenght);

    for (AbstractLink* link: d->links)
    {
        if (link->isUp()) link->sendData(data);
    }
}
*/
