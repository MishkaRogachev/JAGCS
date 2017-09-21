#include "manual_control_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "vehicle_service.h"

#include "mavlink_communicator.h"

namespace
{
    int normalize(float value)
    {
        return value * 1000;
    }
}

using namespace comm;

class ManualControlHandler::Impl
{
public:
    const domain::VehicleService* vehicleService = domain::ServiceRegistry::vehicleService();
};

ManualControlHandler::ManualControlHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    d(new Impl())
{
    connect(d->vehicleService, &domain::VehicleService::sendManualControl,
            this, [this](int vehicleId, float x, float y, float z, float r) {
        this->sendManualControl(d->vehicleService->mavIdByVehicleId(vehicleId), x, y, z, r);
    });
}

ManualControlHandler::~ManualControlHandler()
{}

void ManualControlHandler::processMessage(const mavlink_message_t& message)
{
    Q_UNUSED(message) // TODO: handle feedback
}

void ManualControlHandler::sendManualControl(int vehicledId, float pitch, float roll, float thrust, float yaw)
{
    mavlink_manual_control_t mavlink_manual_control;

    int mavId = d->vehicleService->mavIdByVehicleId(vehicledId);
    mavlink_manual_control.target = mavId;

    mavlink_manual_control.x = ::normalize(pitch);
    mavlink_manual_control.y = ::normalize(roll);
    mavlink_manual_control.z = ::normalize(thrust);
    mavlink_manual_control.r = ::normalize(yaw);

    qDebug() << "pitch" << mavlink_manual_control.x << "roll" << mavlink_manual_control.y;

    AbstractLink* link = m_communicator->mavSystemLink(mavId);
    if (!link) return;

    mavlink_message_t message;
    mavlink_msg_manual_control_encode_chan(m_communicator->systemId(),
                                           m_communicator->componentId(),
                                           m_communicator->linkChannel(link),
                                           &message, &mavlink_manual_control);
    m_communicator->sendMessage(message, link);
}

