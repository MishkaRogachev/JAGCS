#include "battery_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "mavlink_protocol_helpers.h"

#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry.h"

using namespace comm;
using namespace domain;

BatteryHandler::BatteryHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(ServiceRegistry::telemetryService())
{}

void BatteryHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_BATTERY_STATUS) return;

    Telemetry* node = m_telemetryService->mavNode(message.sysid);
    if (!node) return;

    mavlink_battery_status_t battery;
    mavlink_msg_battery_status_decode(&message, &battery);

    node->setParameter({ Telemetry::Battery, Telemetry::Percentage },
                       battery.battery_remaining);
    node->setParameter({ Telemetry::Battery, Telemetry::ConsumedCharge },
                       battery.current_consumed);
    node->setParameter({ Telemetry::Battery, Telemetry::Temperature },
                       battery.temperature);
    node->setParameter({ Telemetry::Battery, Telemetry::Temperature },
                       ::decodeCurrent(battery.current_battery));

    node->notify();
}
