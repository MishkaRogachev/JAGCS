#include "pressure_handler.h"

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

PressureHandler::PressureHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(ServiceRegistry::telemetryService())
{}

void PressureHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_SCALED_PRESSURE) return;

    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_scaled_pressure_t pressure;
    mavlink_msg_scaled_pressure_decode(&message, &pressure);

    portion.setParameter({ Telemetry::Barometric, Telemetry::AbsPressure },
                       pressure.press_abs);
    portion.setParameter({ Telemetry::Barometric, Telemetry::DiffPressure },
                       pressure.press_diff);
    portion.setParameter({ Telemetry::Barometric, Telemetry::Temperature },
                       decodeTemperature(pressure.temperature));
}
