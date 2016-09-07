#include "mavlink_communicator.h"

// MAVLink
#include <mavlink_msg_ping.h>

// Qt
#include <QDebug>

using namespace data_source;
using namespace data_source::mavlink;

class Communicator::Impl
{
public:
    Communicator* p;
    QList<ILink*> links;
    int systemId = 0;
    int componentId = 0;

    Impl(Communicator* p):
        p(p)
    {}

    void processPingRequest(ILink* link, const mavlink_message_t& message)
    {
        mavlink_ping_t ping;
        mavlink_msg_ping_decode(&message, &ping);

        if (!ping.target_system && !ping.target_component)
        {
             mavlink_message_t msg;
             mavlink_msg_ping_pack(systemId, componentId, &msg,
                                   ping.time_usec, ping.seq,
                                   message.sysid, message.compid);
             static uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
             int lenght = mavlink_msg_to_send_buffer(buffer, &msg);
             QByteArray data((const char*)buffer, lenght);

             link->sendData(data);
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

    void processGpsRaw(const mavlink_message_t& message)
    {
        mavlink_gps_raw_int_t gps;
        mavlink_msg_gps_raw_int_decode(&message, &gps);

        emit p->gpsRawReceived(gps);
    }

    void processVfrHud(const mavlink_message_t& message)
    {
        mavlink_vfr_hud_t vfrHud;
        mavlink_msg_vfr_hud_decode(&message, &vfrHud);

        emit p->vfrHudReceived(vfrHud);
    }

    void processAttitude(const mavlink_message_t& message)
    {
        mavlink_attitude_t attitude;
        mavlink_msg_attitude_decode(&message, &attitude);

        emit p->attitudeReceived(attitude);
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

QList<ILink*> Communicator::links() const
{
    return d->links;
}

void Communicator::addLink(ILink* link)
{
    link->setParent(this);

    d->links.append(link);

    connect(link, &ILink::dataReceived, this, &Communicator::handleData);
}

void Communicator::removeLink(ILink* link)
{
    if (link->parent() == this) link->setParent(nullptr);

    d->links.removeOne(link);

    disconnect(link, &ILink::dataReceived, this, &Communicator::handleData);
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

    for (ILink* link: d->links)
    {
        if (link->isUp()) link->sendData(data);
    }
}

void Communicator::handleData(const QByteArray& data)
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

        this->handleMessage(message);
    }

    // TODO: status statusUpdated(status);
}

void Communicator::handleMessage(const mavlink_message_t& message)
{
    switch (message.msgid) {
    case MAVLINK_MSG_ID_PING:
        d->processPingRequest(qobject_cast<ILink*>(this->sender()), message);
        break;
    case MAVLINK_MSG_ID_HEARTBEAT: // custom_mode, base_mode
        d->processHeartbeat(message);
        break;
    case MAVLINK_MSG_ID_SYS_STATUS: // voltage, current, remaining
        d->processSystemStatus(message);
        break;
    case MAVLINK_MSG_ID_GPS_RAW_INT: // lat, lon, fix, satellites, cog, eph
        d->processGpsRaw(message);
        break;
    case MAVLINK_MSG_ID_VFR_HUD: // airspeed, groundspeed, heading, throttle, alt, climb
        d->processVfrHud(message);
        break;
    case MAVLINK_MSG_ID_ATTITUDE: // pitch, roll, yaw
        d->processAttitude(message);
        break;
    // TODO: MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT, MAVLINK_MSG_ID_MISSION_CURRENT, MAVLINK_MSG_ID_RC_CHANNELS_RAW
    //       MAVLINK_MSG_ID_WIND, MAVLINK_MSG_ID_SCALED_PRESSURE, MAVLINK_MSG_ID_GLOBAL_POSITION_INT
    //       MAVLINK_MSG_ID_BATTERY_STATUS, MAVLINK_MSG_ID_RADIO_STATUS, MAVLINK_MSG_ID_LOCAL_POSITION_NED,
    //       MAVLINK_MSG_ID_GLOBAL_POSITION_INT, MAVLINK_MSG_ID_POSITION_TARGET_LOCAL_NED,
    //       MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT, MAVLINK_MSG_ID_HIGHRES_IMU
    default:
        break;
    }

    emit messageReceived(message);
}
