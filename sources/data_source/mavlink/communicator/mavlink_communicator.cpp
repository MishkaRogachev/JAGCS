#include "mavlink_communicator.h"

// MAVLink
#include <mavlink_msg_ping.h>

// Qt
#include <QDebug>

using namespace data_source::mavlink;

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

    void processPingRequest(AbstractLink* link,
                            const mavlink_message_t& message)
    {
        mavlink_ping_t ping;
        mavlink_msg_ping_decode(&message, &ping);

        if (!ping.target_system && !ping.target_component)
        {
             mavlink_message_t msg;
             mavlink_msg_ping_pack(systemId, componentId, &msg,
                                   ping.time_usec, ping.seq,
                                   message.sysid, message.compid);
             link->sendMessage(msg);
        }
    }

    void processHeartbeat(const mavlink_message_t& message)
    {
        mavlink_heartbeat_t heartBeat;
        mavlink_msg_heartbeat_decode(&message, &heartBeat);

        emit p->heartBeatReceived(heartBeat);
    }

    void processSystemStatus(const mavlink_message_t& message)
    {
        mavlink_sys_status_t status;
        mavlink_msg_sys_status_decode(&message, &status);

        emit p->systemStatusReceived(status);
    }
};

Communicator::Communicator(QObject* parent):
    QObject(parent),
    d(new Impl(this))
{}

Communicator::~Communicator()
{
    delete d;
}

void Communicator::addLink(AbstractLink* link)
{
    link->setParent(this);

    d->links.append(link);

    connect(link, &AbstractLink::messageReceived,
            this, &Communicator::handleMessage);
}

void Communicator::removeLink(AbstractLink* link)
{
    if (link->parent() == this) link->setParent(nullptr);

    d->links.removeOne(link);

    disconnect(link, &AbstractLink::messageReceived,
               this, &Communicator::handleMessage);
}

void Communicator::sendMessage(const mavlink_message_t& message)
{
    for (AbstractLink* link: d->links)
    {
        if (link->isUp()) link->sendMessage(message);
    }
}

void Communicator::handleMessage(const mavlink_message_t& message)
{
    qDebug() << message.msgid;

    switch (message.msgid) {
    case MAVLINK_MSG_ID_PING:
        d->processPingRequest(qobject_cast<AbstractLink*>(this->sender()), message);
        break;
    case MAVLINK_MSG_ID_HEARTBEAT:
        d->processHeartbeat(message);
        break;
    case MAVLINK_MSG_ID_SYS_STATUS:
        d->processSystemStatus(message);
        break;
    default:
        break;
    }

    emit messageReceived(message);
}
