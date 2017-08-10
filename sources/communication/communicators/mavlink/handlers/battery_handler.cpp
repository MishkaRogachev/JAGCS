#include "battery_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "mavlink_protocol_helpers.h"

#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

using namespace comm;
using namespace domain;

BatteryHandler::BatteryHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(ServiceRegistry::telemetryService())
{}

void BatteryHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_BATTERY_STATUS) return;

    TelemetryPortion port(m_telemetryService->mavNode(message.sysid));

    mavlink_battery_status_t battery;
    mavlink_msg_battery_status_decode(&message, &battery);

    port.setParameter({ Telemetry::Battery, Telemetry::Percentage }, battery.battery_remaining);
    port.setParameter({ Telemetry::Battery, Telemetry::ConsumedCharge }, battery.current_consumed);
    port.setParameter({ Telemetry::Battery, Telemetry::Temperature }, battery.temperature);
    port.setParameter({ Telemetry::Battery, Telemetry::Current }, ::decodeCurrent(battery.current_battery));
}
