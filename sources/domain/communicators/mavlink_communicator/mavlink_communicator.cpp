#include "mavlink_communicator.h"

// MAVLink
#include <mavlink.h>
#include <mavlink_types.h>

// Qt
#include <QMap>
#include <QDebug>

// Internal
#include "abstract_link.h"

#include "heartbeat_handler.h"
#include "ping_handler.h"
#include "attitude_handler.h"
#include "gps_raw_handler.h"
#include "system_status_handler.h"
#include "vfr_hud_handler.h"
#include "request_handler.h"

#include "vehicle_service.h"

// TODO: multiplexing

using namespace domain;

class MavLinkCommunicator::Impl
{
public:
    QList<AbstractMavLinkHandler*> handlers;
    RequestHandler* requestHandler;

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
    d->handlers.append(new HeartbeatHandler(vehicleService, this));
    d->handlers.append(new PingHandler(this));
    d->handlers.append(new AttitudeHandler(vehicleService));
    d->handlers.append(new GpsRawHandler());
    d->handlers.append(new SystemStatusHandler());
    d->handlers.append(new VfrHudHandler(vehicleService));

    d->requestHandler = new RequestHandler(this);

    d->avalibleChannels.append(MAVLINK_COMM_0);
    d->avalibleChannels.append(MAVLINK_COMM_1);
    d->avalibleChannels.append(MAVLINK_COMM_2);
    d->avalibleChannels.append(MAVLINK_COMM_3);

    connect(vehicleService, &VehicleService::vehicleAdded,
            this, &MavLinkCommunicator::onVehicleAdded);
}

MavLinkCommunicator::~MavLinkCommunicator()
{
    while (!d->handlers.isEmpty())
    {
        delete d->handlers.takeLast();
    }

    delete d->requestHandler;

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
    this->setAddEnabled(!d->avalibleChannels.isEmpty());

    AbstractCommunicator::addLink(link);
}

void MavLinkCommunicator::removeLink(AbstractLink* link)
{
    if (!d->linkChannels.contains(link)) return;

    uint8_t channel = d->linkChannels.value(link);
    d->linkChannels.remove(link);
    d->avalibleChannels.prepend(channel);
    this->setAddEnabled(!d->avalibleChannels.isEmpty());

    AbstractCommunicator::removeLink(link);
}

void MavLinkCommunicator::setSystemId(int systemId)
{
    if (d->systemId == systemId) return;

    d->systemId = systemId;
    emit systemIdChanged(systemId);
}

void MavLinkCommunicator::setComponentId(int componentId)
{
    if (d->componentId == componentId) return;

    d->componentId = componentId;
    emit componentIdChanged(componentId);
}

void MavLinkCommunicator::sendMessage(const mavlink_message_t& message)
{
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    int lenght = mavlink_msg_to_send_buffer(buffer, &message);

    if (!lenght) return;
    this->sendData(QByteArray((const char*)buffer, lenght));

    qDebug() << "Sent packet: SYS: " << message.sysid <<
                ", COMP: " << message.compid << "MSG ID: " <<
                message.msgid;
}

void MavLinkCommunicator::onDataReceived(const QByteArray& data)
{
    mavlink_message_t message;
    mavlink_status_t status;

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

void MavLinkCommunicator::onVehicleAdded(int vehicleId)
{
    d->requestHandler->sendRequest(vehicleId);
}
