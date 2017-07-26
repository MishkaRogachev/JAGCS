#include "mavlink_communicator_factory.h"

// Internal
#include "domain_entry.h"
#include "mavlink_communicator.h"

#include "ping_handler.h"
#include "heartbeat_handler.h"
#include "system_status_handler.h"
#include "attitude_handler.h"
#include "pressure_handler.h"
#include "position_handler.h"
#include "home_position_handler.h"
#include "gps_handler.h"
#include "rangefinder_handler.h"
#include "vfr_hud_handler.h"
#include "wind_handler.h"
#include "battery_handler.h"
#include "radio_status_handler.h"
#include "nav_controller_handler.h"
#include "command_handler.h"
#include "mission_handler.h"

using namespace comm;

MavLinkCommunicatorFactory::MavLinkCommunicatorFactory(
        domain::DomainEntry* entry, quint8 systemId, quint8 componentId):
    ICommunicatorFactory(),
    m_entry(entry),
    m_systemId(systemId),
    m_componentId(componentId)
{}

AbstractCommunicator* MavLinkCommunicatorFactory::create()
{
    auto communicator = new MavLinkCommunicator(m_systemId, m_componentId);

    new PingHandler(communicator);
    new HeartbeatHandler(m_entry->vehicleService(), m_entry->telemetryService(), communicator);
    new SystemStatusHandler(m_entry->telemetryService(), communicator);
    new AttitudeHandler(m_entry->telemetryService(), communicator);
    new PressureHandler(m_entry->telemetryService(), communicator);
    new PositionHandler(m_entry->telemetryService(), communicator);
    new HomePositionHandler(m_entry->telemetryService(), communicator);
    new GpsHandler(m_entry->telemetryService(), communicator);
    new VfrHudHandler(m_entry->telemetryService(), communicator);
    new RangefinderHandler(m_entry->telemetryService(), communicator);
    new WindHandler(m_entry->telemetryService(), communicator);
    new BatteryHandler(m_entry->telemetryService(), communicator);
    new RadioStatusHandler(m_entry->telemetryService(), communicator);
    new NavControllerHandler(m_entry->telemetryService(), communicator);
    new CommandHandler(m_entry->vehicleService(), m_entry->commandService(), communicator);
    new MissionHandler(m_entry->vehicleService(), m_entry->telemetryService(),
                       m_entry->missionService(), m_entry->commandService(), communicator);

    return communicator;
}
