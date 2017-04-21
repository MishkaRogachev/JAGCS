#include "home_position_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QTimerEvent>
#include <QDebug>

// Internal
#include "vehicle_description.h"
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
                                data_source::MavLinkCommunicator* communicator):
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

    data_source::VehicleDescriptionPtr description =
            m_vehicleService->findDescriptiontByMavId(message.sysid);
    if (description.isNull()) return;

    BaseVehicle* vehicle = m_vehicleService->baseVehicle(description);

    mavlink_home_position_t home;
    mavlink_msg_home_position_decode(&message, &home);

    vehicle->setHomePosition(Position(
                                 QGeoCoordinate(decodeLatLon(home.latitude),
                                                decodeLatLon(home.longitude),
                                                decodeAltitude(home.altitude)),
                                 QVector3D(home.approach_x,
                                           home.approach_y,
                                           home.approach_z)));

    m_reqestTimers[description].stop();
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

    home.target_system = vehicle->mavId();

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

        this->sendHomePositionRequest(it.key()->mavId());
        return;
    }
}

void HomePositionHandler::onVehicleAdded(
        const data_source::VehicleDescriptionPtr& description)
{
    this->sendHomePositionRequest(description->mavId());

    BaseVehicle* baseVehicle = m_vehicleService->baseVehicle(description);

    connect(baseVehicle, &BaseVehicle::commandHomePosition,
            this, &HomePositionHandler::sendHomePositionSetting);

    m_reqestTimers[description].start(::reqestInterval, this);
}

void HomePositionHandler::onVehicleRemoved(
        const data_source::VehicleDescriptionPtr& description)
{
    m_reqestTimers.remove(description);
}
