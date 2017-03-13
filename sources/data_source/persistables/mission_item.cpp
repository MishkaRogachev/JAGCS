#include "mission_item.h"

using namespace data_source;

MissionItem::MissionItem():
    Persistable(),
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

const char* MissionItem::tableName() const
{
    return "mission_items";
}

const char* MissionItem::tableParams() const
{
    return "command INTEGER";
}

QString MissionItem::params() const
{
    return QString::number(int(m_command));
}
