#include "mission_item.h"

using namespace data_source;

MissionItem::MissionItem(int id, domain::Command command):
    m_id(id),
    m_command(command)
{}

int MissionItem::id() const
{
    return m_id;
}

domain::Command MissionItem::command() const
{
    return m_command;
}

void MissionItem::setCommand(domain::Command command)
{
    m_command = command;
}

