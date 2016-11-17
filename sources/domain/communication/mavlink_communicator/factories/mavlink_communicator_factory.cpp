#include "mavlink_communicator_factory.h"

// Internal
#include "mavlink_communicator.h"

#include "heartbeat_handler.h"
#include "ping_handler.h"
#include "attitude_handler.h"
#include "global_position_handler.h"
#include "gps_raw_handler.h"
#include "system_status_handler.h"
#include "vfr_hud_handler.h"
#include "home_position_handler.h"

using namespace domain;

MavLinkCommunicatorFactory::MavLinkCommunicatorFactory(
        VehicleService* vehicleService):
    IMavLinkCommunicatorFactory(vehicleService)
{}

MavLinkCommunicator* MavLinkCommunicatorFactory::create()
{
    auto communicator = new MavLinkCommunicator();

    new HeartbeatHandler(m_vehicleService, communicator);
    new PingHandler(communicator);
    new AttitudeHandler(m_vehicleService, communicator);
    new GlobalPositionHandler(m_vehicleService, communicator);
    new GpsRawHandler(m_vehicleService, communicator);
    new SystemStatusHandler(communicator);
    new VfrHudHandler(m_vehicleService, communicator);
    new HomePositionHandler(m_vehicleService, communicator);
    // TODO: NAV_CONTROLLER_OUTPUT

    return communicator;
}
