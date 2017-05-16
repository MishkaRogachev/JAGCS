#include "mavlink_communicator_factory.h"

// Internal
#include "settings_provider.h"
#include "mavlink_communicator.h"

#include "ping_handler.h"
#include "heartbeat_handler.h"
#include "system_status_handler.h"
#include "attitude_handler.h"
#include "position_handler.h"
#include "home_position_handler.h"
#include "gps_handler.h"
#include "vfr_hud_handler.h"
#include "wind_handler.h"
#include "command_handler.h"
#include "mission_handler.h"

using namespace comm;

MavLinkCommunicatorFactory::MavLinkCommunicatorFactory(
        db::DbFacade* dbFacade,
        domain::VehicleService* vehicleServeice,
        domain::CommandService* commandService,
        quint8 systemId, quint8 componentId):
    ICommunicatorFactory(),
    m_dbFacade(dbFacade),
    m_vehicleService(vehicleServeice),
    m_commandService(commandService),
    m_systemId(systemId),
    m_componentId(componentId)
{}

AbstractCommunicator* MavLinkCommunicatorFactory::create()
{
    auto communicator = new MavLinkCommunicator(m_systemId, m_componentId);

    new PingHandler(communicator);
    new HeartbeatHandler(m_vehicleService, communicator);
    new SystemStatusHandler(m_vehicleService, communicator);
    new AttitudeHandler(m_vehicleService, communicator);
    new PositionHandler(m_vehicleService, communicator);
    new HomePositionHandler(m_vehicleService, communicator);
    new GpsHandler(m_vehicleService, communicator);
    new VfrHudHandler(m_vehicleService, communicator);
    new WindHandler(m_vehicleService, communicator);
    new CommandHandler(m_vehicleService, communicator);
    new MissionHandler(m_dbFacade, m_vehicleService, m_commandService, communicator);

    return communicator;
}
