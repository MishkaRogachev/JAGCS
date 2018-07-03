#include "land_target_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QtMath>
#include <QGeoCoordinate>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

using namespace comm;
using namespace domain;

LandTargetHandler::LandTargetHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(serviceRegistry->telemetryService())
{}

void LandTargetHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_LANDING_TARGET) return;

    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_landing_target_t landing;
    mavlink_msg_landing_target_decode(&message, &landing);

    portion.setParameter({ Telemetry::LandingSystem, Telemetry::Distance }, landing.distance);
    portion.setParameter({ Telemetry::LandingSystem, Telemetry::DeviationX },
                         qRadiansToDegrees(landing.angle_x));
    portion.setParameter({ Telemetry::LandingSystem, Telemetry::DeviationY },
                         qRadiansToDegrees(landing.angle_y));
    portion.setParameter({ Telemetry::LandingSystem, Telemetry::SizeX },
                         qRadiansToDegrees(landing.size_x));
    portion.setParameter({ Telemetry::LandingSystem, Telemetry::SizeY },
                         qRadiansToDegrees(landing.size_y));

    // TODO: handle MAV_FRAME, LANDING_TARGET_TYPE, ID(target_num)
#ifdef MAVLINK_V2
    if (landing.position_valid)
    {
        portion.setParameter({ Telemetry::LandingSystem, Telemetry::Coordinate },
                             QVariant::fromValue(QGeoCoordinate(landing.x, landing.y, landing.z)));
    }
    else
    {
        portion.setParameter({ Telemetry::LandingSystem, Telemetry::Coordinate },
                             QVariant::fromValue(QGeoCoordinate()));
    }
#endif
}
