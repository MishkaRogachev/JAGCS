#include "system_status_handler.h"

// MAVLink
#include <mavlink.h>
#include <mavlink_msg_sys_status.h>

using namespace domain;

SystemStatusHandler::SystemStatusHandler(QObject* parent):
    AbstractMavLinkHandler(parent)
{}

void SystemStatusHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_SYS_STATUS) return;

    mavlink_sys_status_t status;
    mavlink_msg_sys_status_decode(&message, &status);

    // TODO: handle system status
}
