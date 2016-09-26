#include "vfr_hud_handler.h"

// MAVLink
#include <mavlink.h>
#include <mavlink_msg_vfr_hud.h>

using namespace domain;

VfrHudHandler::VfrHudHandler():
    AbstractMavLinkHandler()
{}

int VfrHudHandler::messageId() const
{
    return MAVLINK_MSG_ID_VFR_HUD;
}

void VfrHudHandler::processMessage(const mavlink_message_t& message)
{
    mavlink_vfr_hud_t vfrHud;
    mavlink_msg_vfr_hud_decode(&message, &vfrHud);

    // TODO: handle HUD
}
