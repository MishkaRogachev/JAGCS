#include "vfr_hud_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "vehicle_service.h"
#include "vehicle.h"

using namespace domain;

VfrHudHandler::VfrHudHandler(VehicleService* vehicleService,
                             MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(vehicleService)
{}

void VfrHudHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_VFR_HUD ||
        message.sysid == 0) return;

    Vehicle* vehicle = m_vehicleService->requestVehicle(message.sysid);

    mavlink_vfr_hud_t vfrHud;
    mavlink_msg_vfr_hud_decode(&message, &vfrHud);

    vehicle->setTrueAirSpeed(vfrHud.airspeed);
    vehicle->setGroundSpeed(vfrHud.groundspeed);
    vehicle->setBarometricAltitude(vfrHud.alt);
    vehicle->setBarometricClimb(vfrHud.climb);
    vehicle->setHeading(vfrHud.heading);
}
