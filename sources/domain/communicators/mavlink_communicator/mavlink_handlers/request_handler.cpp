#include "request_handler.h"

// MAVLink
#include <mavlink.h>
#include <mavlink_msg_request_data_stream.h>

// Internal
#include "mavlink_communicator.h"

typedef enum MAV_DATA_STREAM // FIXME: temporary
{
    MAV_DATA_STREAM_ALL=0, /* Enable all data streams | */
    MAV_DATA_STREAM_RAW_SENSORS=1, /* Enable IMU_RAW, GPS_RAW, GPS_STATUS packets. | */
    MAV_DATA_STREAM_EXTENDED_STATUS=2, /* Enable GPS_STATUS, CONTROL_STATUS, AUX_STATUS | */
    MAV_DATA_STREAM_RC_CHANNELS=3, /* Enable RC_CHANNELS_SCALED, RC_CHANNELS_RAW, SERVO_OUTPUT_RAW | */
    MAV_DATA_STREAM_RAW_CONTROLLER=4, /* Enable ATTITUDE_CONTROLLER_OUTPUT, POSITION_CONTROLLER_OUTPUT, NAV_CONTROLLER_OUTPUT. | */
    MAV_DATA_STREAM_POSITION=6, /* Enable LOCAL_POSITION, GLOBAL_POSITION/GLOBAL_POSITION_INT messages. | */
    MAV_DATA_STREAM_EXTRA1=10, /* Dependent on the autopilot | */
    MAV_DATA_STREAM_EXTRA2=11, /* Dependent on the autopilot | */
    MAV_DATA_STREAM_EXTRA3=12, /* Dependent on the autopilot | */
    MAV_DATA_STREAM_ENUM_END=13, /*  | */
} MAV_DATA_STREAM;

using namespace domain;

RequestHandler::RequestHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_communicator(communicator)
{}

void RequestHandler::sendRequest(uint8_t targetSystem, uint8_t targetComponent)
{
    mavlink_message_t message;
    const int  maxStreams = 6;
    // TODO: new-style request
    const uint8_t MAVStreams[maxStreams] = {MAV_DATA_STREAM_RAW_SENSORS,
                                            MAV_DATA_STREAM_EXTENDED_STATUS,
                                            MAV_DATA_STREAM_RC_CHANNELS,
                                            MAV_DATA_STREAM_POSITION,
                                            MAV_DATA_STREAM_EXTRA1,
                                            MAV_DATA_STREAM_EXTRA2};
    const uint16_t MAVRates[maxStreams] = {0x02, 0x02, 0x05, 0x02, 0x05, 0x02};

    for (int i=0; i < maxStreams; i++)
    {
        mavlink_msg_request_data_stream_pack(m_communicator->systemId(),
                                             m_communicator->componentId(),
                                             &message,
                                             targetSystem,
                                             targetComponent,
                                             MAVStreams[i], MAVRates[i], 1);

        emit sendMessage(message);
    }
}

void RequestHandler::sendRequest(uint8_t targetSystem)
{
    this->sendRequest(targetSystem, 0);
}

int RequestHandler::messageId() const
{
    return -1; // No request handle
}

void RequestHandler::processMessage(const mavlink_message_t& message)
{
    Q_UNUSED(message);
}
