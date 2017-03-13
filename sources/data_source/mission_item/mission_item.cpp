#include "mission_item.h"

using namespace data_source;

MissionItem::MissionItem():
    m_command(domain::Command::UnknownCommand)
{}

domain::Command MissionItem::command() const
{
    return m_command;
}

void MissionItem::setCommand(const domain::Command& command)
{
    m_command = command;
}
