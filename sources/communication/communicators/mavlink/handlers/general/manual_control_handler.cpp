#include "manual_control_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "vehicle_service.h"

#include "mavlink_communicator.h"

using namespace comm;

class ManualControlHandler::Impl
{
public:
    const domain::VehicleService* vehicleSrevice = domain::ServiceRegistry::vehicleService();
};

ManualControlHandler::ManualControlHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    d(new Impl())
{}

ManualControlHandler::~ManualControlHandler()
{}

void ManualControlHandler::processMessage(const mavlink_message_t& message)
{
    Q_UNUSED(message) // TODO: handle feedback
}

void ManualControlHandler::sendManualControl(int vehicledId)
{
    mavlink_manual_control_t mavlink_manual_control;

    int mavId = d->vehicleSrevice->mavIdByVehicleId(vehicledId);
    mavlink_manual_control.target = mavId;

    // TODO: set target channels

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_message_t message;
    mavlink_msg_manual_control_encode_chan(m_communicator->systemId(),
                                           m_communicator->componentId(),
                                           m_communicator->linkChannel(link),
                                           &message, &mavlink_manual_control);
    m_communicator->sendMessage(message, link);
}

