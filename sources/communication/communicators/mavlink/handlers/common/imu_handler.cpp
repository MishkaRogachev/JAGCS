#include "imu_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QVector3D>
#include <QVariant>

// Internal
#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

using namespace comm;
using namespace domain;

ImuHandler::ImuHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(serviceRegistry->telemetryService())
{}

void ImuHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_SCALED_IMU) return;

    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_scaled_imu_t imu;
    mavlink_msg_scaled_imu_decode(&message, &imu);

    portion.setParameter({ Telemetry::Ahrs, Telemetry::Accel, Telemetry::Acceleration },
                         QVector3D(imu.xacc, imu.yacc, imu.zacc));
    portion.setParameter({ Telemetry::Ahrs, Telemetry::Gyro, Telemetry::AngularSpeed },
                         QVector3D(imu.xgyro, imu.ygyro, imu.zgyro));
    portion.setParameter({ Telemetry::Ahrs, Telemetry::Compass, Telemetry::MagneticField },
                         QVector3D(imu.xmag, imu.ymag, imu.zmag));
}
