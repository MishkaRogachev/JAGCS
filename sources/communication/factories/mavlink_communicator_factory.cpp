#include "mavlink_communicator_factory.h"

// Internal
#include "mavlink_communicator.h"

#include "ping_handler.h"
#include "heartbeat_handler.h"
#include "system_status_handler.h"
#include "autopilot_version_handler.h"
#include "attitude_handler.h"
#include "pressure_handler.h"
#include "position_handler.h"
#include "home_position_handler.h"
#include "gps_handler.h"
#include "rangefinder_handler.h"
#include "vfr_hud_handler.h"
#include "wind_handler.h"
#include "radio_status_handler.h"
#include "nav_controller_handler.h"
#include "command_handler.h"
#include "mission_handler.h"
#include "attitude_target_handler.h"

using namespace comm;

MavLinkCommunicatorFactory::MavLinkCommunicatorFactory(quint8 systemId, quint8 componentId):
    ICommunicatorFactory(),
    m_systemId(systemId),
    m_componentId(componentId)
{}

AbstractCommunicator* MavLinkCommunicatorFactory::create()
{
    auto communicator = new MavLinkCommunicator(m_systemId, m_componentId);

    new PingHandler(communicator);
    new HeartbeatHandler(communicator);
    new SystemStatusHandler(communicator);
    new AutopilotVersionHandler(communicator);
    new AttitudeHandler(communicator);
    new PressureHandler(communicator);
    new PositionHandler(communicator);
    new HomePositionHandler(communicator);
    new GpsHandler(communicator);
    new VfrHudHandler(communicator);
    new RangefinderHandler(communicator);
    new WindHandler(communicator);
    new RadioStatusHandler(communicator);
    new NavControllerHandler(communicator);
    new CommandHandler(communicator);
    new MissionHandler(communicator);
    new AttitudeTargetHandler(communicator);

    return communicator;
}
