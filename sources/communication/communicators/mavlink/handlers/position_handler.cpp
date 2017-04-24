#include "position_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "vehicle_service.h"
#include "base_vehicle.h"

#include "mavlink_protocol_helpers.h"

using namespace db;
using namespace comm;
using namespace domain;

PositionHandler::PositionHandler(VehicleService* vehicleService,
                                 MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(vehicleService)
{}

void PositionHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_GLOBAL_POSITION_INT) return;

    BaseVehicle* vehicle = m_vehicleService->baseVehicle(message.sysid);
    if (!vehicle) return;

    mavlink_global_position_int_t position;
    mavlink_msg_global_position_int_decode(&message, &position);

    vehicle->setPosition(Position(
                    decodeCoordinate(position.lat, position.lon, position.alt),
                    QVector3D(position.vx, position.vy, position.vz)));
}
