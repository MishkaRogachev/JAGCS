#include "system_status_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "mavlink_protocol_helpers.h"

#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

using namespace comm;
using namespace domain;

SystemStatusHandler::SystemStatusHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(ServiceRegistry::telemetryService())
{}

void SystemStatusHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_SYS_STATUS) return;

    TelemetryPortion port(m_telemetryService->mavNode(message.sysid));

    mavlink_sys_status_t status;
    mavlink_msg_sys_status_decode(&message, &status);

    port.setParameter({ Telemetry::Ahrs, Telemetry::Present },
                      status.onboard_control_sensors_present & MAV_SYS_STATUS_AHRS);

    port.setParameter({ Telemetry::Ahrs, Telemetry::Enabled },
                      status.onboard_control_sensors_enabled & MAV_SYS_STATUS_AHRS);
    port.setParameter({ Telemetry::Ahrs, Telemetry::Operational },
                      status.onboard_control_sensors_health & MAV_SYS_STATUS_AHRS);

    port.setParameter({ Telemetry::Ahrs, Telemetry::Accel, Telemetry::Present },
                      status.onboard_control_sensors_present &
                      MAV_SYS_STATUS_SENSOR_3D_ACCEL);
    port.setParameter({ Telemetry::Ahrs, Telemetry::Accel, Telemetry::Enabled },
                      status.onboard_control_sensors_enabled &
                      MAV_SYS_STATUS_SENSOR_3D_ACCEL);
    port.setParameter({ Telemetry::Ahrs, Telemetry::Accel, Telemetry::Operational },
                      status.onboard_control_sensors_health &
                      MAV_SYS_STATUS_SENSOR_3D_ACCEL);

    port.setParameter({ Telemetry::Ahrs, Telemetry::Gyro, Telemetry::Present },
                      status.onboard_control_sensors_present &
                      MAV_SYS_STATUS_SENSOR_3D_GYRO);
    port.setParameter({ Telemetry::Ahrs, Telemetry::Gyro, Telemetry::Enabled },
                      status.onboard_control_sensors_enabled &
                      MAV_SYS_STATUS_SENSOR_3D_GYRO);
    port.setParameter({ Telemetry::Ahrs, Telemetry::Gyro, Telemetry::Operational },
                      status.onboard_control_sensors_health &
                      MAV_SYS_STATUS_SENSOR_3D_GYRO);

    port.setParameter({ Telemetry::Satellite, Telemetry::Present },
                      status.onboard_control_sensors_present &
                      MAV_SYS_STATUS_SENSOR_GPS);
    port.setParameter({ Telemetry::Satellite, Telemetry::Enabled },
                      status.onboard_control_sensors_enabled &
                      MAV_SYS_STATUS_SENSOR_GPS);
    port.setParameter({ Telemetry::Satellite, Telemetry::Operational },
                      status.onboard_control_sensors_health &
                      MAV_SYS_STATUS_SENSOR_GPS);

    port.setParameter({ Telemetry::Compass, Telemetry::Present },
                      status.onboard_control_sensors_present &
                      MAV_SYS_STATUS_SENSOR_3D_MAG);
    port.setParameter({ Telemetry::Compass, Telemetry::Enabled },
                      status.onboard_control_sensors_enabled &
                      MAV_SYS_STATUS_SENSOR_3D_MAG);
    port.setParameter({ Telemetry::Compass, Telemetry::Operational },
                      status.onboard_control_sensors_health &
                      MAV_SYS_STATUS_SENSOR_3D_MAG);

    port.setParameter({ Telemetry::Barometric, Telemetry::Present },
                      status.onboard_control_sensors_present &
                      MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE);
    port.setParameter({ Telemetry::Barometric, Telemetry::Enabled },
                      status.onboard_control_sensors_enabled &
                      MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE);
    port.setParameter({ Telemetry::Barometric, Telemetry::Operational },
                      status.onboard_control_sensors_health &
                      MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE);

    port.setParameter({ Telemetry::Pitot, Telemetry::Present },
                      status.onboard_control_sensors_present &
                      MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE);
    port.setParameter({ Telemetry::Pitot, Telemetry::Enabled },
                      status.onboard_control_sensors_enabled &
                      MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE);
    port.setParameter({ Telemetry::Pitot, Telemetry::Operational },
                      status.onboard_control_sensors_health &
                      MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE);

    port.setParameter({ Telemetry::Rangefinder, Telemetry::Present },
                      status.onboard_control_sensors_present &
                      MAV_SYS_STATUS_SENSOR_LASER_POSITION);
    port.setParameter({ Telemetry::Rangefinder, Telemetry::Enabled },
                      status.onboard_control_sensors_enabled &
                      MAV_SYS_STATUS_SENSOR_LASER_POSITION);
    port.setParameter({ Telemetry::Rangefinder, Telemetry::Operational },
                      status.onboard_control_sensors_health &
                      MAV_SYS_STATUS_SENSOR_LASER_POSITION);

    port.setParameter({ Telemetry::Battery, Telemetry::Present },
                      status.onboard_control_sensors_present &
                      MAV_SYS_STATUS_SENSOR_BATTERY);
    port.setParameter({ Telemetry::Battery, Telemetry::Enabled },
                      status.onboard_control_sensors_enabled &
                      MAV_SYS_STATUS_SENSOR_BATTERY);
    port.setParameter({ Telemetry::Battery, Telemetry::Operational },
                      status.onboard_control_sensors_health &
                      MAV_SYS_STATUS_SENSOR_BATTERY);
    port.setParameter({ Telemetry::Battery, Telemetry::Voltage },
                      ::decodeVoltage(status.voltage_battery));
    port.setParameter({ Telemetry::Battery, Telemetry::Current },
                      ::decodeCurrent(status.current_battery));
    port.setParameter({ Telemetry::Battery, Telemetry::Percentage },
                      ::decodeCurrent(status.battery_remaining));

    // TODO: load, drop rate, errors
}
