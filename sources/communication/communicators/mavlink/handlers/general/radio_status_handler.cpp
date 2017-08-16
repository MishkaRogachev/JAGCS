#include "radio_status_handler.h"

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

RadioStatusHandler::RadioStatusHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(ServiceRegistry::telemetryService())
{}

void RadioStatusHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_RADIO_STATUS) return;

    TelemetryPortion portion(m_telemetryService->radioNode());

    mavlink_radio_status_t radio;
    mavlink_msg_radio_status_decode(&message, &radio);

    portion.setParameter({ Telemetry::Rssi }, decodeRssi(radio.rssi));
    portion.setParameter({ Telemetry::Noise }, radio.noise);
    portion.setParameter({ Telemetry::RemoteRssi }, decodeRssi(radio.remrssi));
    portion.setParameter({ Telemetry::RemoteNoise }, radio.remnoise);
    portion.setParameter({ Telemetry::Errors }, radio.rxerrors);
    portion.setParameter({ Telemetry::Fixed }, radio.fixed);
}
