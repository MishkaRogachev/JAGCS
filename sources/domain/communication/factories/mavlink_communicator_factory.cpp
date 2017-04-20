#include "mavlink_communicator_factory.h"

// Internal
#include "settings_provider.h"
#include "mavlink_communicator.h"

#include "ping_handler.h"
#include "heartbeat_handler.h"
#include "attitude_handler.h"
#include "vfr_hud_handler.h"

using namespace data_source;
using namespace domain;

MavLinkCommunicatorFactory::MavLinkCommunicatorFactory(
        VehicleService* vehicleServeice):
    ICommunicatorFactory(),
    m_vehicleServeice(vehicleServeice)
{}

AbstractCommunicator* MavLinkCommunicatorFactory::create()
{
    auto communicator = new MavLinkCommunicator(
         SettingsProvider::value(settings::communication::systemId).toInt(),
         SettingsProvider::value(settings::communication::componentId).toInt());

    new PingHandler(communicator);
    new HeartbeatHandler(m_vehicleServeice, communicator);
    new AttitudeHandler(m_vehicleServeice, communicator);
    new VfrHudHandler(m_vehicleServeice, communicator);

    return communicator;
}
