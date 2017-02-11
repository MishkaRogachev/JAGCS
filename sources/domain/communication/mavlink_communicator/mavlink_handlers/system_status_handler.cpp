#include "system_status_handler.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "vehicle_service.h"
#include "vehicle.h"

#include "mavlink_protocol_helpers.h"

using namespace domain;

SystemStatusHandler::SystemStatusHandler(VehicleService* vehicleService,
                                         MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(vehicleService)
{}

void SystemStatusHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_SYS_STATUS) return;

    Vehicle* vehicle = m_vehicleService->vehicleForId(message.sysid);
    if (!vehicle) return;

    mavlink_sys_status_t status;
    mavlink_msg_sys_status_decode(&message, &status);

    vehicle->setPowerSystem(PowerSystem(decodeVoltage(status.voltage_battery),
                                        decodeCurrent(status.current_battery),
                                        status.battery_remaining));

    vehicle->setBarometerAvalible((status.onboard_control_sensors_present &
                                   MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE) &&
                                  (status.onboard_control_sensors_enabled &
                                   MAV_SYS_STATUS_SENSOR_ABSOLUTE_PRESSURE));

    vehicle->setAirSpeedAvalible((status.onboard_control_sensors_present &
                                  MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE) &&
                                 (status.onboard_control_sensors_enabled &
                                  MAV_SYS_STATUS_SENSOR_DIFFERENTIAL_PRESSURE));

    vehicle->setCompasAvalible((status.onboard_control_sensors_present &
                                MAV_SYS_STATUS_SENSOR_3D_MAG) &&
                               (status.onboard_control_sensors_enabled &
                                MAV_SYS_STATUS_SENSOR_3D_MAG));

    vehicle->setGpsAvalible((status.onboard_control_sensors_present &
                             MAV_SYS_STATUS_SENSOR_GPS) &&
                            (status.onboard_control_sensors_enabled &
                             MAV_SYS_STATUS_SENSOR_GPS));

    vehicle->setInsAvalible((status.onboard_control_sensors_present &
                             MAV_SYS_STATUS_SENSOR_3D_ACCEL) &&
                            (status.onboard_control_sensors_enabled &
                             MAV_SYS_STATUS_SENSOR_3D_ACCEL) &&
                            (status.onboard_control_sensors_present &
                             MAV_SYS_STATUS_SENSOR_3D_GYRO) &&
                            (status.onboard_control_sensors_enabled &
                             MAV_SYS_STATUS_SENSOR_3D_GYRO));

    vehicle->setAhrsAvalible((status.onboard_control_sensors_present &
                              MAV_SYS_STATUS_AHRS) &&
                             (status.onboard_control_sensors_enabled &
                              MAV_SYS_STATUS_AHRS));

    vehicle->setRangeFinderAvalible((status.onboard_control_sensors_present &
                                     MAV_SYS_STATUS_SENSOR_LASER_POSITION) &&
                                    (status.onboard_control_sensors_enabled &
                                     MAV_SYS_STATUS_SENSOR_LASER_POSITION));

    // TODO: handle sensors health
}
