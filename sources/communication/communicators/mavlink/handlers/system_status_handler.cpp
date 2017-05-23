#include "system_status_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "telemetry_service.h"

#include "mavlink_protocol_helpers.h"

namespace
{
    bool avalible(const mavlink_sys_status_t& status, int subsystem)
    {
        return (status.onboard_control_sensors_present & subsystem) &&
               (status.onboard_control_sensors_enabled & subsystem);
    }
}

using namespace comm;
using namespace domain;

SystemStatusHandler::SystemStatusHandler(TelemetryService* telemetryService,
                                         MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(telemetryService)
{}

void SystemStatusHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_SYS_STATUS) return;

    int vehicleId = m_telemetryService->vehicleIdByMavId(message.sysid);
    if (!vehicleId) return;

    mavlink_sys_status_t status;
    mavlink_msg_sys_status_decode(&message, &status);

    m_telemetryService->setAvailables(vehicleId, Availables(
                    ::avalible(status, MAV_SYS_STATUS_AHRS),
                    ::avalible(status, MAV_SYS_STATUS_SENSOR_3D_ACCEL) &&
                    ::avalible(status, MAV_SYS_STATUS_SENSOR_3D_GYRO),
                    ::avalible(status, MAV_SYS_STATUS_SENSOR_GPS),
                    ::avalible(status, MAV_SYS_STATUS_SENSOR_3D_MAG),
                    ::avalible(status, MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE),
                    ::avalible(status, MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE),
                    ::avalible(status, MAV_SYS_STATUS_SENSOR_LASER_POSITION)));

    // TODO: battery
}
