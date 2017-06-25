#include "system_status_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QVariant>

// Internal
#include "mavlink_protocol_helpers.h"

#include "telemetry_service.h"
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

    Telemetry* node = m_telemetryService->mavNode(message.sysid);
    if (!node) return;

    mavlink_sys_status_t status;
    mavlink_msg_sys_status_decode(&message, &status);

    node->setParameter({ Telemetry::Ahrs, Telemetry::Present },
                       status.onboard_control_sensors_present & MAV_SYS_STATUS_AHRS);
    node->setParameter({ Telemetry::Ahrs, Telemetry::Enabled },
                       status.onboard_control_sensors_enabled & MAV_SYS_STATUS_AHRS);
    node->setParameter({ Telemetry::Ahrs, Telemetry::Operational },
                       status.onboard_control_sensors_health & MAV_SYS_STATUS_AHRS);

    node->setParameter({ Telemetry::Ahrs, Telemetry::Accel, Telemetry::Present },
                       status.onboard_control_sensors_present &
                       MAV_SYS_STATUS_SENSOR_3D_ACCEL);
    node->setParameter({ Telemetry::Ahrs, Telemetry::Accel, Telemetry::Enabled },
                       status.onboard_control_sensors_enabled &
                       MAV_SYS_STATUS_SENSOR_3D_ACCEL);
    node->setParameter({ Telemetry::Ahrs, Telemetry::Accel, Telemetry::Operational },
                       status.onboard_control_sensors_health &
                       MAV_SYS_STATUS_SENSOR_3D_ACCEL);

    node->setParameter({ Telemetry::Ahrs, Telemetry::Gyro, Telemetry::Present },
                       status.onboard_control_sensors_present &
                       MAV_SYS_STATUS_SENSOR_3D_GYRO);
    node->setParameter({ Telemetry::Ahrs, Telemetry::Gyro, Telemetry::Enabled },
                       status.onboard_control_sensors_enabled &
                       MAV_SYS_STATUS_SENSOR_3D_GYRO);
    node->setParameter({ Telemetry::Ahrs, Telemetry::Gyro, Telemetry::Operational },
                       status.onboard_control_sensors_health &
                       MAV_SYS_STATUS_SENSOR_3D_GYRO);

    node->setParameter({ Telemetry::Satellite, Telemetry::Present },
                       status.onboard_control_sensors_present &
                       MAV_SYS_STATUS_SENSOR_GPS);
    node->setParameter({ Telemetry::Satellite, Telemetry::Enabled },
                       status.onboard_control_sensors_enabled &
                       MAV_SYS_STATUS_SENSOR_GPS);
    node->setParameter({ Telemetry::Satellite, Telemetry::Operational },
                       status.onboard_control_sensors_health &
                       MAV_SYS_STATUS_SENSOR_GPS);

    node->setParameter({ Telemetry::Compass, Telemetry::Present },
                       status.onboard_control_sensors_present &
                       MAV_SYS_STATUS_SENSOR_3D_MAG);
    node->setParameter({ Telemetry::Compass, Telemetry::Enabled },
                       status.onboard_control_sensors_enabled &
                       MAV_SYS_STATUS_SENSOR_3D_MAG);
    node->setParameter({ Telemetry::Compass, Telemetry::Operational },
                       status.onboard_control_sensors_health &
                       MAV_SYS_STATUS_SENSOR_3D_MAG);

    node->setParameter({ Telemetry::Barometric, Telemetry::Present },
                       status.onboard_control_sensors_present &
                       MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE);
    node->setParameter({ Telemetry::Barometric, Telemetry::Enabled },
                       status.onboard_control_sensors_enabled &
                       MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE);
    node->setParameter({ Telemetry::Barometric, Telemetry::Operational },
                       status.onboard_control_sensors_health &
                       MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE);

    node->setParameter({ Telemetry::Pitot, Telemetry::Present },
                       status.onboard_control_sensors_present &
                       MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE);
    node->setParameter({ Telemetry::Pitot, Telemetry::Enabled },
                       status.onboard_control_sensors_enabled &
                       MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE);
    node->setParameter({ Telemetry::Pitot, Telemetry::Operational },
                       status.onboard_control_sensors_health &
                       MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE);

    node->setParameter({ Telemetry::Rangefinder, Telemetry::Present },
                       status.onboard_control_sensors_present &
                       MAV_SYS_STATUS_SENSOR_LASER_POSITION);
    node->setParameter({ Telemetry::Rangefinder, Telemetry::Enabled },
                       status.onboard_control_sensors_enabled &
                       MAV_SYS_STATUS_SENSOR_LASER_POSITION);
    node->setParameter({ Telemetry::Rangefinder, Telemetry::Operational },
                       status.onboard_control_sensors_health &
                       MAV_SYS_STATUS_SENSOR_LASER_POSITION);

    node->setParameter({ Telemetry::Battery, Telemetry::Voltage },
                       ::decodeVoltage(status.voltage_battery));
    node->setParameter({ Telemetry::Battery, Telemetry::Current },
                       ::decodeCurrent(status.current_battery));
    node->setParameter({ Telemetry::Battery, Telemetry::Percentage },
                       status.battery_remaining);

    node->notify();

    // TODO: load, drop rate, errors
}
