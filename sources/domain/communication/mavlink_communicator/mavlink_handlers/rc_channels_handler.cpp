#include "rc_channels_handler.h"

// MAVLink
#include <mavlink.h>

using namespace domain;

RcChannelsHandler::RcChannelsHandler(VehicleService* vehicleService,
                                     MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(vehicleService)
{}

void RcChannelsHandler::processMessage(const mavlink_message_t& message)
{
    // TODO: handle RC_CHANNELS_RAW/RC_CHANNELS_SCALED or SERVO_OUTPUT_RAW
}

void RcChannelsHandler::sendChannelsOverride(const QMap<int, int>& channels)
{
    mavlink_message_t message;
    mavlink_rc_channels_override_t override;

    override.chan1_raw = channels.value(1, UINT16_MAX);
    override.chan2_raw = channels.value(2, UINT16_MAX);
    override.chan3_raw = channels.value(3, UINT16_MAX);
    override.chan4_raw = channels.value(4, UINT16_MAX);
    override.chan5_raw = channels.value(5, UINT16_MAX);
    override.chan6_raw = channels.value(6, UINT16_MAX);
    override.chan7_raw = channels.value(7, UINT16_MAX);
    override.chan8_raw = channels.value(8, UINT16_MAX);

    mavlink_msg_rc_channels_override_encode(m_communicator->systemId(),
                                            m_communicator->componentId(),
                                            &message, &override);

    m_communicator->sendMessageAllLinks(message);
}
