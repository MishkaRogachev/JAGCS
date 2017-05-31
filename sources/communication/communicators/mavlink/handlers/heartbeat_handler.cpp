#include "heartbeat_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QTimer>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "mavlink_communicator.h"
#include "mavlink_mode_helper.h"

#include "telemetry.h"

using namespace comm;
using namespace domain;

namespace
{
    // TODO:  db-vehicle type
    /*int decodeType(uint8_t type)
    {
        switch (type) //TODO: other vehicles
        {
        case MAV_TYPE_FIXED_WING:
            return AerialVehicle::FixedWingAircraft;
        case MAV_TYPE_TRICOPTER:
        case MAV_TYPE_QUADROTOR:
        case MAV_TYPE_HEXAROTOR:
        case MAV_TYPE_OCTOROTOR:
            return AerialVehicle::Multirotor;
        case MAV_TYPE_COAXIAL:
        case MAV_TYPE_HELICOPTER:
            return AerialVehicle::Helicopter;
        case MAV_TYPE_AIRSHIP:
        case MAV_TYPE_FREE_BALLOON:
            return AerialVehicle::Airship;
        case MAV_TYPE_VTOL_DUOROTOR:
        case MAV_TYPE_VTOL_QUADROTOR:
        case MAV_TYPE_VTOL_TILTROTOR:
        case MAV_TYPE_VTOL_RESERVED2:
        case MAV_TYPE_VTOL_RESERVED3:
        case MAV_TYPE_VTOL_RESERVED4:
        case MAV_TYPE_VTOL_RESERVED5:
            return AerialVehicle::Vtol;
        case MAV_TYPE_GENERIC:
        default:
            return BaseVehicle::UnknownType;
        }
    }

    BaseVehicle::State decodeState(uint8_t state)
    {
        switch (state)
        {
        case MAV_STATE_BOOT:
            return BaseVehicle::Boot;
        case MAV_STATE_CALIBRATING:
            return BaseVehicle::Calibrating;
        case MAV_STATE_STANDBY:
            return BaseVehicle::Standby;
        case MAV_STATE_ACTIVE:
            return BaseVehicle::Active;
        case MAV_STATE_CRITICAL:
            return BaseVehicle::Critical;
        case MAV_STATE_EMERGENCY:
            return BaseVehicle::Emergency;
        case MAV_STATE_UNINIT:
        default:
            return BaseVehicle::UnknownState;
        }
    }*/
}

HeartbeatHandler::HeartbeatHandler(TelemetryService* telemetryService,
                                   MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(telemetryService),
    m_timer(new QTimer(this))
{
    QObject::connect(m_timer, &QTimer::timeout, this, &HeartbeatHandler::sendHeartbeat);
    m_timer->start(1000); //TODO: heartbeat emit disabling and freqency selecting
}

HeartbeatHandler::~HeartbeatHandler()
{
    delete m_timer;
}

void HeartbeatHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_HEARTBEAT) return;

    TelemetryNode* node = m_telemetryService->nodeByMavId(message.sysid);
    if (!node) return;

    mavlink_heartbeat_t heartbeat;
    mavlink_msg_heartbeat_decode(&message, &heartbeat);

    // TODO: set vehicle type from ::decodeType(heartbeat.type);
    // TODO: add vehicle if not exist

    node->setValue(telemetry::online, true); // offline timer
    node->setValue(telemetry::armed, heartbeat.base_mode & MAV_MODE_FLAG_DECODE_POSITION_SAFETY);
    node->setValue(telemetry::mode, decodeCustomMode(heartbeat.autopilot, heartbeat.type, heartbeat.custom_mode));
}

void HeartbeatHandler::sendHeartbeat()
{
    mavlink_message_t message;
    mavlink_heartbeat_t heartbeat;

    heartbeat.type = MAV_TYPE_GCS;

    mavlink_msg_heartbeat_encode(m_communicator->systemId(),
                                 m_communicator->componentId(),
                                 &message, &heartbeat);

    m_communicator->sendMessageAllLinks(message);
}
