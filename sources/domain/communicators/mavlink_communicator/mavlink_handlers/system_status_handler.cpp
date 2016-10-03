#include "system_status_handler.h"

// MAVLink
#include <mavlink.h>
#include <mavlink_msg_sys_status.h>

using namespace domain;

SystemStatusHandler::SystemStatusHandler(QObject* parent):
    AbstractMavLinkHandler(parent)
{}

int SystemStatusHandler::messageId() const
{
    return MAVLINK_MSG_ID_SYS_STATUS;
}

void SystemStatusHandler::processMessage(const mavlink_message_t& message)
{
    mavlink_sys_status_t status;
    mavlink_msg_sys_status_decode(&message, &status);

    // TODO: handle system status
}
