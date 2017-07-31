#include "radio_status_handler.h"

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

RadioStatusHandler::RadioStatusHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(ServiceRegistry::telemetryService())
{}

void RadioStatusHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_RADIO_STATUS) return;

    Telemetry* node = m_telemetryService->radioNode();
    if (!node) return;

    mavlink_radio_status_t radio;
    mavlink_msg_radio_status_decode(&message, &radio);

    node->setParameter({ Telemetry::Rssi }, decodeRssi(radio.rssi));
    node->setParameter({ Telemetry::Noise }, radio.noise);
    node->setParameter({ Telemetry::RemoteRssi }, decodeRssi(radio.remrssi));
    node->setParameter({ Telemetry::RemoteNoise }, radio.remnoise);
    node->setParameter({ Telemetry::Errors }, radio.rxerrors);
    node->setParameter({ Telemetry::Fixed }, radio.fixed);

    node->notify();
}
