#include "manual_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "mavlink_communicator.h"

#include "vehicle_service.h"
#include "abstract_vehicle.h"

using namespace domain;

ManualHandler::ManualHandler(VehicleService* vehicleService,
                               MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_vehicleService(vehicleService)
{
    connect(vehicleService, &VehicleService::vehicleAdded,
            this, &ManualHandler::onVehicleAdded);
}

void ManualHandler::processMessage(const mavlink_message_t& message)
{
    Q_UNUSED(message) // TODO: handle manual output
}

void ManualHandler::sendManualInput(int x, int y, int z, int r)
{
    auto vehicle = qobject_cast<domain::AbstractVehicle*>(this->sender());
    if (!vehicle) return;

    mavlink_message_t message;
    mavlink_manual_control_t manual;

    manual.target = vehicle->vehicleId();

    manual.x = x;
    manual.y = y;
    manual.z = z;
    manual.r = r;

    mavlink_msg_manual_control_encode(m_communicator->systemId(),
                                      m_communicator->componentId(),
                                      &message, &manual);
    m_communicator->sendMessageAllLinks(message);
}

void ManualHandler::onVehicleAdded(AbstractVehicle* vehicle)
{
    connect(vehicle, &AbstractVehicle::commandManualInput,
            this, &ManualHandler::sendManualInput);
}

void ManualHandler::onVehicleRemoved(AbstractVehicle* vehicle)
{
    disconnect(vehicle, 0, this, 0);
}
