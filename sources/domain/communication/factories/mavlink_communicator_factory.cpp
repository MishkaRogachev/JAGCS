#include "mavlink_communicator_factory.h"

// Internal
#include "settings_provider.h"
#include "mavlink_communicator.h"

#include "ping_handler.h"
#include "heartbeat_handler.h"
#include "system_status_handler.h"
#include "attitude_handler.h"
#include "position_handler.h"
#include "gps_handler.h"
#include "vfr_hud_handler.h"
#include "wind_handler.h"
#include "command_handler.h"

using namespace data_source;
using namespace domain;

MavLinkCommunicatorFactory::MavLinkCommunicatorFactory(
        VehicleService* vehicleServeice):
    ICommunicatorFactory(),
    m_vehicleService(vehicleServeice)
{}

AbstractCommunicator* MavLinkCommunicatorFactory::create()
{
    auto communicator = new MavLinkCommunicator(
         SettingsProvider::value(settings::communication::systemId).toInt(),
         SettingsProvider::value(settings::communication::componentId).toInt());

    new PingHandler(communicator);
    new HeartbeatHandler(m_vehicleService, communicator);
    new SystemStatusHandler(m_vehicleService, communicator);
    new AttitudeHandler(m_vehicleService, communicator);
    new PositionHandler(m_vehicleService, communicator);
    new GpsHandler(m_vehicleService, communicator);
    new VfrHudHandler(m_vehicleService, communicator);
    new WindHandler(m_vehicleService, communicator);
    new CommandHandler(m_vehicleService, communicator);

    return communicator;
}
