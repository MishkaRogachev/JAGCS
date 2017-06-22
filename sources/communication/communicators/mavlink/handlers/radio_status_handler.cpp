#include "radio_status_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "mavlink_protocol_helpers.h"

#include "telemetry_service.h"
#include "telemetry.h"

using namespace comm;
using namespace domain;

RadioStatusHandler::RadioStatusHandler(TelemetryService* telemetryService,
                                       MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(telemetryService)
{}

void RadioStatusHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_RADIO_STATUS) return;

    Telemetry* node = m_telemetryService->nodeByMavId(message.sysid);
    if (!node) return;

    mavlink_radio_status_t radio;
    mavlink_msg_radio_status_decode(&message, &radio);

    node->setParameter({ Telemetry::Rangefinder, Telemetry::Rssi },
                       decodeRssi(radio.rssi));
    node->setParameter({ Telemetry::Radio, Telemetry::Noise },
                       radio.noise);
    node->setParameter({ Telemetry::Rangefinder, Telemetry::RemoteRssi },
                       decodeRssi(radio.remrssi));
    node->setParameter({ Telemetry::Radio, Telemetry::RemoteNoise },
                       radio.remnoise);
    node->setParameter({ Telemetry::Radio, Telemetry::Errors },
                       radio.rxerrors);
    node->setParameter({ Telemetry::Radio, Telemetry::Fixed },
                       radio.fixed);

    node->notify();
}
