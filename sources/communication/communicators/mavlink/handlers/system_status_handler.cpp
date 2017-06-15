#include "system_status_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "mavlink_protocol_helpers.h"

#include "telemetry.h"

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

    TelemetryNode* node = m_telemetryService->nodeByMavId(message.sysid);
    if (!node) return;

    mavlink_sys_status_t status;
    mavlink_msg_sys_status_decode(&message, &status);

    node->setParameter({ TelemetryId::Ahrs, TelemetryId::Present },
                       status.onboard_control_sensors_present & MAV_SYS_STATUS_AHRS);
    node->setParameter({ TelemetryId::Ahrs, TelemetryId::Enabled },
                       status.onboard_control_sensors_enabled & MAV_SYS_STATUS_AHRS);
    node->setParameter({ TelemetryId::Ahrs, TelemetryId::Operational },
                       status.onboard_control_sensors_health & MAV_SYS_STATUS_AHRS);

    node->setParameter({ TelemetryId::Satellite, TelemetryId::Present },
                       status.onboard_control_sensors_present & MAV_SYS_STATUS_SENSOR_GPS);
    node->setParameter({ TelemetryId::Satellite, TelemetryId::Enabled },
                       status.onboard_control_sensors_enabled & MAV_SYS_STATUS_SENSOR_GPS);
    node->setParameter({ TelemetryId::Satellite, TelemetryId::Operational },
                       status.onboard_control_sensors_health & MAV_SYS_STATUS_SENSOR_GPS);

    node->setParameter({ TelemetryId::Compass, TelemetryId::Present },
                       status.onboard_control_sensors_present & MAV_SYS_STATUS_SENSOR_3D_MAG);
    node->setParameter({ TelemetryId::Compass, TelemetryId::Enabled },
                       status.onboard_control_sensors_enabled & MAV_SYS_STATUS_SENSOR_3D_MAG);
    node->setParameter({ TelemetryId::Compass, TelemetryId::Operational },
                       status.onboard_control_sensors_health & MAV_SYS_STATUS_SENSOR_3D_MAG);

    node->setParameter({ TelemetryId::Barometric, TelemetryId::Present },
                       status.onboard_control_sensors_present & MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE);
    node->setParameter({ TelemetryId::Barometric, TelemetryId::Enabled },
                       status.onboard_control_sensors_enabled & MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE);
    node->setParameter({ TelemetryId::Barometric, TelemetryId::Operational },
                       status.onboard_control_sensors_health & MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE);

    node->setParameter({ TelemetryId::Pitot, TelemetryId::Present },
                       status.onboard_control_sensors_present & MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE);
    node->setParameter({ TelemetryId::Pitot, TelemetryId::Enabled },
                       status.onboard_control_sensors_enabled & MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE);
    node->setParameter({ TelemetryId::Pitot, TelemetryId::Operational },
                       status.onboard_control_sensors_health & MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE);

    node->notify();

// TODO: MAV_SYS_STATUS_SENSOR_3D_ACCEL, MAV_SYS_STATUS_SENSOR_3D_GYRO, MAV_SYS_STATUS_SENSOR_LASER_POSITION
// TODO: battery
}
