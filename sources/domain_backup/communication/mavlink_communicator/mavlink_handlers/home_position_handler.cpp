#include "home_position_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QTimerEvent>
#include <QDebug>

// Internal
#include "mavlink_communicator.h"

#include "vehicle_service.h"
#include "base_vehicle.h"

#include "mavlink_protocol_helpers.h"

namespace
{
    const int reqestInterval = 1000; // 1 Hz
}

using namespace domain;

HomePositionHandler::HomePositionHandler(VehicleService* vehicleService,
                                         MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(vehicleService)
{
    connect(vehicleService, &VehicleService::vehicleAdded,
            this, &HomePositionHandler::onVehicleAdded);
    connect(vehicleService, &VehicleService::vehicleRemoved,
            this, &HomePositionHandler::onVehicleRemoved);
}

void HomePositionHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_HOME_POSITION) return;

    BaseVehicle* vehicle = m_vehicleService->baseVehicle(message.sysid);
    if (!vehicle) return;

    mavlink_home_position_t home;
    mavlink_msg_home_position_decode(&message, &home);

    vehicle->setHomePosition(Position(
                                 QGeoCoordinate(decodeLatLon(home.latitude),
                                                decodeLatLon(home.longitude),
                                                decodeAltitude(home.altitude)),
                                 QVector3D(home.approach_x,
                                           home.approach_y,
                                           home.approach_z)));

    m_reqestTimers[message.sysid].stop();
}

void HomePositionHandler::sendHomePositionRequest(uint8_t id)
{
     mavlink_message_t message;
     mavlink_command_long_t command;

     command.target_system = id;
     command.target_component = 0;
     command.confirmation = 0;

     command.command = MAV_CMD_GET_HOME_POSITION;

     mavlink_msg_command_long_encode(m_communicator->systemId(),
                                     m_communicator->componentId(),
                                     &message, &command);
     m_communicator->sendMessageAllLinks(message);
}

void HomePositionHandler::sendHomePositionSetting(const Position& position)
{
    auto vehicle = qobject_cast<domain::BaseVehicle*>(this->sender());
    if (!vehicle) return;

    mavlink_message_t message;
    mavlink_set_home_position_t home;

    home.target_system = vehicle->vehicleId();

    home.latitude = encodeLatLon(position.coordinate().latitude());
    home.longitude = encodeLatLon(position.coordinate().longitude());
    home.altitude = encodeAltitude(position.coordinate().altitude());

    home.approach_x = position.vector().x();
    home.approach_y = position.vector().y();
    home.approach_z = position.vector().z();

    mavlink_msg_set_home_position_encode(m_communicator->systemId(),
                                         m_communicator->componentId(),
                                         &message, &home);

    m_communicator->sendMessageAllLinks(message);
}

void HomePositionHandler::timerEvent(QTimerEvent* event)
{
    for (auto it = m_reqestTimers.begin(); it != m_reqestTimers.end(); ++it)
    {
        if (it.value().timerId() != event->timerId()) continue;

        this->sendHomePositionRequest(it.key());
        return;
    }
}

void HomePositionHandler::onVehicleAdded(AbstractVehicle* vehicle)
{
    this->sendHomePositionRequest(vehicle->vehicleId());

    auto baseVehicle = qobject_cast<BaseVehicle*>(vehicle);
    if (baseVehicle)
    {
        connect(baseVehicle, &BaseVehicle::commandHomePosition,
                this, &HomePositionHandler::sendHomePositionSetting);
    }

    m_reqestTimers[vehicle->vehicleId()].start(::reqestInterval, this);
}

void HomePositionHandler::onVehicleRemoved(AbstractVehicle* vehicle)
{
    m_reqestTimers.remove(vehicle->vehicleId());
    disconnect(vehicle, 0, this, 0);
}
