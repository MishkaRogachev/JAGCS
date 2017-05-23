#include "vfr_hud_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "telemetry_service.h"

using namespace comm;
using namespace domain;

VfrHudHandler::VfrHudHandler(TelemetryService* telemetryService,
                             MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(telemetryService)
{}

void VfrHudHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_VFR_HUD) return;

    int vehicleId = m_telemetryService->vehicleIdByMavId(message.sysid);
    if (!vehicleId) return;

    mavlink_vfr_hud_t vfrHud;
    mavlink_msg_vfr_hud_decode(&message, &vfrHud);

    // TODO: handle vfrHud data
//    vehicle->setIndicatedAirSpeed(vfrHud.airspeed);
//    // TODO: TAS from MAVLink TAS = IAS + [(IAS X 2/100) X (DA/1000)]
//    vehicle->setTrueAirSpeed(vfrHud.airspeed + (vfrHud.airspeed * 0.02 *
//                                                vfrHud.alt / 1000));
//    vehicle->setGroundSpeed(vfrHud.groundspeed);
//    vehicle->setBarometricAltitude(vfrHud.alt);
//    vehicle->setBarometricClimb(vfrHud.climb);
//    vehicle->setHeading(vfrHud.heading);
//    vehicle->setThrottle(vfrHud.throttle);
}
