#include "ekf_status_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

using namespace comm;
using namespace domain;

EkfStatusHandler::EkfStatusHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(ServiceRegistry::telemetryService())
{}

void EkfStatusHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_EKF_STATUS_REPORT) return;

    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_ekf_status_report_t ekf;
    mavlink_msg_ekf_status_report_decode(&message, &ekf);

    portion.setParameter({ Telemetry::Ahrs, Telemetry::Ekf, Telemetry::VelocityVariance },
                         ekf.velocity_variance);
    portion.setParameter({ Telemetry::Ahrs, Telemetry::Ekf, Telemetry::VerticalVariance },
                         ekf.pos_vert_variance);
    portion.setParameter({ Telemetry::Ahrs, Telemetry::Ekf, Telemetry::HorizontVariance },
                         ekf.pos_horiz_variance);
    portion.setParameter({ Telemetry::Ahrs, Telemetry::Ekf, Telemetry::CompassVariance },
                         ekf.compass_variance);
    portion.setParameter({ Telemetry::Ahrs, Telemetry::Ekf, Telemetry::TerrainAltitudeVariance },
                         ekf.terrain_alt_variance);

    // TODO: ekf.flags
}
