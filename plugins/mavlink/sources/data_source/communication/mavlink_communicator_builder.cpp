#include "mavlink_communicator_builder.h"

// Internal
#include "mavlink_communicator.h"

// MAVLink v1
#include "ping_handler.h"
#include "heartbeat_handler.h"
#include "system_status_handler.h"
#include "system_time_handler.h"
#include "autopilot_version_handler.h"
#include "attitude_handler.h"
#include "imu_handler.h"
#include "vibration_handler.h"
#include "ekf_status_handler.h"
#include "altitude_handler.h"
#include "pressure_handler.h"
#include "position_handler.h"
#include "home_position_handler.h"
#include "gps_handler.h"
#include "rangefinder_handler.h"
#include "vfr_hud_handler.h"
#include "high_latency_handler.h"
#include "wind_handler.h"
#include "radio_status_handler.h"
#include "radio_handler.h"
#include "nav_controller_handler.h"
#include "target_position_handler.h"
#include "command_handler.h"
#include "mission_handler.h"
#include "attitude_target_handler.h"
#include "land_target_handler.h"

#ifdef MAVLINK_V2
#include "flight_handler.h"
# endif

using namespace data_source;

MavLinkCommunicatorBuilder::MavLinkCommunicatorBuilder():
    m_communicator(nullptr)
{}

MavLinkCommunicatorBuilder::~MavLinkCommunicatorBuilder()
{
    if (m_communicator) delete m_communicator;
}

void MavLinkCommunicatorBuilder::initCommunicator()
{
    m_communicator = new MavLinkCommunicator();
}

MavLinkCommunicator* MavLinkCommunicatorBuilder::getCommunicator()
{
    MavLinkCommunicator* communicator = m_communicator;
    m_communicator = nullptr;
    return communicator;
}

void MavLinkCommunicatorBuilder::buildIdentification(quint8 systemId, quint8 componentId)
{
    m_communicator->setSystemId(systemId);
    m_communicator->setComponentId(componentId);
}

void MavLinkCommunicatorBuilder::buildHandlers()
{
    new PingHandler(m_communicator);
    new HeartbeatHandler(m_communicator);
    new SystemStatusHandler(m_communicator);
    new SystemTimeHandler(m_communicator);
    new AutopilotVersionHandler(m_communicator);
    new AttitudeHandler(m_communicator);
    new ImuHandler(m_communicator);
    new VibrationHandler(m_communicator);
    new EkfStatusHandler(m_communicator);
    new AltitudeHandler(m_communicator);
    new PressureHandler(m_communicator);
    new PositionHandler(m_communicator);
    new HomePositionHandler(m_communicator);
    new GpsHandler(m_communicator);
    new VfrHudHandler(m_communicator);
    new HighLatencyHandler(m_communicator);
    new RangefinderHandler(m_communicator);
    new WindHandler(m_communicator);
    new RadioStatusHandler(m_communicator);
    new RadioHandler(m_communicator);
    new NavControllerHandler(m_communicator);
    new TargetPositionHandler(m_communicator);
    new CommandHandler(m_communicator);
    new MissionHandler(m_communicator);
    new AttitudeTargetHandler(m_communicator);
    new LandTargetHandler(m_communicator);

#ifdef MAVLINK_V2
    new FlightHandler(m_communicator);
# endif
}
