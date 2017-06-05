#include "pressure_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "mavlink_protocol_helpers.h"
#include "telemetry.h"

using namespace comm;
using namespace domain;

PressureHandler::PressureHandler(TelemetryService* telemetryService,
                                 MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(telemetryService)
{}

void PressureHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_SCALED_PRESSURE) return;

    TelemetryNode* node = m_telemetryService->nodeByMavId(message.sysid);
    if (!node) return;

    mavlink_scaled_pressure_t pressure;
    mavlink_msg_scaled_pressure_decode(&message, &pressure);

    node->setParameter({ telemetry::barometric, telemetry::absPressure },
                       pressure.press_abs);
    node->setParameter({ telemetry::barometric, telemetry::diffPressure },
                       pressure.press_diff);
    node->setParameter({ telemetry::barometric, telemetry::temperature },
                       decodeTemperature(pressure.temperature));

    node->notify();
}
