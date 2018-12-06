#include "mavlink_communicator_factory.h"

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

using namespace comm;

MavLinkCommunicatorFactory::MavLinkCommunicatorFactory(quint8 systemId, quint8 componentId,
                                                       bool retranslationEnabled):
    ICommunicatorFactory(),
    m_systemId(systemId),
    m_componentId(componentId),
    m_retranslationEnabled(retranslationEnabled)
{}

MavLinkCommunicator* MavLinkCommunicatorFactory::create()
{
    MavLinkCommunicator* communicator = new MavLinkCommunicator(m_systemId, m_componentId,
                                                                m_retranslationEnabled);

    communicator->addHandler(new PingHandler(communicator));
    communicator->addHandler(new HeartbeatHandler(communicator));
    communicator->addHandler(new SystemStatusHandler(communicator));
    communicator->addHandler(new SystemTimeHandler(communicator));
    communicator->addHandler(new AutopilotVersionHandler(communicator));
    communicator->addHandler(new AttitudeHandler(communicator));
    communicator->addHandler(new ImuHandler(communicator));
    communicator->addHandler(new VibrationHandler(communicator));
    communicator->addHandler(new EkfStatusHandler(communicator));
    communicator->addHandler(new AltitudeHandler(communicator));
    communicator->addHandler(new PressureHandler(communicator));
    communicator->addHandler(new PositionHandler(communicator));
    communicator->addHandler(new HomePositionHandler(communicator));
    communicator->addHandler(new GpsHandler(communicator));
    communicator->addHandler(new VfrHudHandler(communicator));
    communicator->addHandler(new HighLatencyHandler(communicator));
    communicator->addHandler(new RangefinderHandler(communicator));
    communicator->addHandler(new WindHandler(communicator));
    communicator->addHandler(new RadioStatusHandler(communicator));
    communicator->addHandler(new RadioHandler(communicator));
    communicator->addHandler(new NavControllerHandler(communicator));
    communicator->addHandler(new TargetPositionHandler(communicator));
    communicator->addHandler(new CommandHandler(communicator));
    communicator->addHandler(new MissionHandler(communicator));
    communicator->addHandler(new AttitudeTargetHandler(communicator));
    communicator->addHandler(new LandTargetHandler(communicator));

#ifdef MAVLINK_V2
    communicator->addHandler(new FlightHandler(communicator));
# endif

    return communicator;
}
