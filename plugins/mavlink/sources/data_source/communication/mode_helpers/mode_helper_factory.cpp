#include "mode_helper_factory.h"

// Mavlink
#include "mavlink.h"

// Internal
#include "apm_copter_mode_helper.h"
#include "apm_plane_mode_helper.h"
#include "px4_mode_helper.h"

using namespace data_source;

IModeHelper* ModeHelperFactory::create(uint8_t autopilot, uint8_t type)
{
    if (autopilot == MAV_AUTOPILOT_PX4)
    {
        return new Px4ModeHelper();
    }

    if (autopilot == MAV_AUTOPILOT_ARDUPILOTMEGA)
    {
        switch (type)
        {
        case MAV_TYPE_FIXED_WING:
            return new ApmPlaneModeHelper();
        case MAV_TYPE_TRICOPTER:
        case MAV_TYPE_QUADROTOR:
        case MAV_TYPE_HEXAROTOR:
        case MAV_TYPE_OCTOROTOR:
        case MAV_TYPE_COAXIAL:
        case MAV_TYPE_HELICOPTER:
            return new ApmCopterModeHelper();
        default:
            break;
        }
    }
    return nullptr;
}
