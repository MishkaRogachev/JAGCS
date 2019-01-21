#include "home_position_handler.h"

// SwarmLink
#include <swarmlink/mavlink.h>

// Qt
#include <QMap>
#include <QVariant>
#include <QVector3D>
#include <QTimerEvent>
#include <QDebug>

// Internal
#include "vehicle.h"

#include "mavlink_communicator.h"
#include "mavlink_protocol_helpers.h"

#include "service_registry.h"
#include "vehicle_service.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

namespace
{
    const int interval = 5000;
}

using namespace comm;
using namespace domain;

class HomePositionHandler::Impl
{
public:
    domain::VehicleService* vehicleService = serviceRegistry->vehicleService();
    domain::MissionService* missionService = serviceRegistry->missionService();

    QList<int> obtainedVehicles;
    QMap<int, int> vehiclesTimers;
};

HomePositionHandler::HomePositionHandler(MavLinkCommunicator* communicator):
    QObject(communicator),
    AbstractMavLinkHandler(communicator),
    d(new Impl())
{
    connect(d->vehicleService, &VehicleService::vehicleAdded,
            this, [this](const dto::VehiclePtr& vehicle) {
        this->sendHomePositionRequest(vehicle->mavId());
        this->addVehicleTimer(vehicle->id());
    });

    connect(d->vehicleService, &VehicleService::vehicleRemoved,
            this, [this](const dto::VehiclePtr& vehicle) {
        d->obtainedVehicles.removeOne(vehicle->id());
        this->removeVehicleTimer(vehicle->id());
    });

    connect(d->vehicleService, &VehicleService::vehicleChanged,
            this, [this](const dto::VehiclePtr& vehicle) {
        if (!vehicle->isOnline() || d->obtainedVehicles.contains(vehicle->id())) return;
        this->sendHomePositionRequest(vehicle->mavId());
        this->addVehicleTimer(vehicle->id());
    });
}

HomePositionHandler::~HomePositionHandler()
{}

void HomePositionHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_HOME_POSITION) return;

    TelemetryPortion port(serviceRegistry->telemetryService()->mavNode(message.sysid));

    mavlink_home_position_t home;
    mavlink_msg_home_position_decode(&message, &home);

    QGeoCoordinate coordinate(decodeLatLon(home.latitude), decodeLatLon(home.longitude),
                              decodeAltitude(home.altitude));
    QVector3D direction(home.approach_x, home.approach_y, home.approach_z);

    port.setParameter({ Telemetry::HomePosition, Telemetry::Coordinate },
                       QVariant::fromValue(coordinate));
    port.setParameter({ Telemetry::HomePosition, Telemetry::Direction },
                       QVariant::fromValue(direction));
    port.setParameter({ Telemetry::HomePosition, Telemetry::Altitude },
                       coordinate.altitude());

    int vehicleId = d->vehicleService->vehicleIdByMavId(message.sysid);

    this->removeVehicleTimer(vehicleId);
    d->obtainedVehicles.append(vehicleId);
}

void HomePositionHandler::sendHomePositionRequest(quint8 mavId)
{
    mavlink_message_t message;
    mavlink_command_long_t command;

     command.target_system = mavId;
     command.target_component = 0;
     command.confirmation = 0;

     command.command = MAV_CMD_GET_HOME_POSITION;

     AbstractLink* link = m_communicator->mavSystemLink(mavId);
     if (!link) return;

     mavlink_msg_command_long_encode_chan(m_communicator->systemId(),
                                          m_communicator->componentId(),
                                          m_communicator->linkChannel(link),
                                          &message, &command);
     m_communicator->sendMessage(message, link);
}

void HomePositionHandler::timerEvent(QTimerEvent* event)
{
    dto::VehiclePtr vehicle = d->vehicleService->vehicle(
                                  d->vehiclesTimers.key(event->timerId(), -1));
    if (vehicle.isNull()) return QObject::timerEvent(event);

    this->sendHomePositionRequest(vehicle->mavId());
}

void HomePositionHandler::addVehicleTimer(int vehicleId)
{
    if (d->vehiclesTimers.contains(vehicleId)) this->removeVehicleTimer(vehicleId);
    d->vehiclesTimers[vehicleId] = this->startTimer(::interval);
}

void HomePositionHandler::removeVehicleTimer(int vehicleId)
{
    if (d->vehiclesTimers.contains(vehicleId)) this->killTimer(d->vehiclesTimers.take(vehicleId));
}
