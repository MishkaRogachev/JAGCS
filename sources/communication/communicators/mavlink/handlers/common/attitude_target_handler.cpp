#include "attitude_target_handler.h"

// SwarmLink
#include <swarmlink/mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "vehicle_service.h"

#include "mavlink_communicator.h"

using namespace comm;

AttitudeTargetHandler::AttitudeTargetHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(serviceRegistry->vehicleService())
{
//    connect(d->vehicleService, &domain::VehicleService::sendManualControl,
//            this, &AttitudeTargetHandler::sendAttitude);
}

void AttitudeTargetHandler::processMessage(const mavlink_message_t& message)
{
    Q_UNUSED(message) // TODO: handle feedback
}

void AttitudeTargetHandler::sendAttitude(int vehicledId, float pitch, float roll, float thrust, float yaw)
{
    int mavId = m_vehicleService->mavIdByVehicleId(vehicledId);
    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_message_t message;

    float attitudeQuaternion[4];
    mavlink_euler_to_quaternion(roll, pitch, yaw, attitudeQuaternion);
    mavlink_msg_set_attitude_target_pack_chan(m_communicator->systemId(),
                                              m_communicator->componentId(),
                                              m_communicator->linkChannel(link),
                                              &message,
                                              0,//QGC::groundTimeUsecs(),
                                              mavId,
                                              0,
                                              0x7, // disable rate control
                                              attitudeQuaternion,
                                              0,
                                              0,
                                              0,
                                              thrust);
    m_communicator->sendMessage(message, link);
}
