#include "vfr_hud_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "vehicle_service.h"
#include "aerial_vehicle.h"

using namespace db;
using namespace comm;
using namespace domain;

VfrHudHandler::VfrHudHandler(VehicleService* vehicleService,
                             MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(vehicleService)
{}

void VfrHudHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_VFR_HUD) return;

    auto vehicle = m_vehicleService->aerialVehicle(message.sysid);
    if (!vehicle) return;

    mavlink_vfr_hud_t vfrHud;
    mavlink_msg_vfr_hud_decode(&message, &vfrHud);

    vehicle->setIndicatedAirSpeed(vfrHud.airspeed);
    // TODO: TAS from MAVLink TAS = IAS + [(IAS X 2/100) X (DA/1000)]
    vehicle->setTrueAirSpeed(vfrHud.airspeed + (vfrHud.airspeed * 0.02 *
                                                vfrHud.alt / 1000));
    vehicle->setGroundSpeed(vfrHud.groundspeed);
    vehicle->setBarometricAltitude(vfrHud.alt);
    vehicle->setBarometricClimb(vfrHud.climb);
    vehicle->setHeading(vfrHud.heading);
    vehicle->setThrottle(vfrHud.throttle);
}
