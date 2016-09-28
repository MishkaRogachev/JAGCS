#include "attitude_handler.h"

// MAVLink
#include <mavlink.h>
#include <mavlink_msg_attitude.h>

// Qt
#include <QDebug>

// Internal
#include "vehicle_service.h"
#include "vehicle.h"

using namespace domain;

AttitudeHandler::AttitudeHandler(VehicleService* vehicleService):
    AbstractMavLinkHandler(),
    m_vehicleService(vehicleService)
{}

int AttitudeHandler::messageId() const
{
    return MAVLINK_MSG_ID_ATTITUDE;
}

void AttitudeHandler::processMessage(const mavlink_message_t& message)
{
    if (message.sysid == 0) return;
    Vehicle* vehicle = m_vehicleService->requestVehicle(message.sysid);

    mavlink_attitude_t attitude;
    mavlink_msg_attitude_decode(&message, &attitude);

    qDebug() << attitude.pitch << attitude.roll;

    vehicle->setAttitude(Attitude(attitude.pitch, attitude.roll, attitude.yaw));
}
