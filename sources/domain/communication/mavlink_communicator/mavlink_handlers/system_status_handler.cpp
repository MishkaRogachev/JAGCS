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
    if (message.msgid != MAVLINK_MSG_ID_SYS_STATUS ||
        message.sysid == 0) return;

    Vehicle* vehicle = m_vehicleService->requestVehicle(message.sysid);

    mavlink_sys_status_t status;
    mavlink_msg_sys_status_decode(&message, &status);

    vehicle->setPowerSystem(PowerSystem(decodeVoltage(status.voltage_battery),
                                        decodeCurrent(status.current_battery),
                                        status.battery_remaining));
}
