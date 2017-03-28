#include "mission_view_helper.h"

// Qt
#include <QVariant>

// Internal
#include "abstract_mission_item.h"

using namespace presentation;

MissionViewHelper::MissionViewHelper(QObject* parent):
    QObject(parent)
{
    m_commandNames[Command::UnknownCommand] = tr("UNKNOWN");
    m_commandNames[Command::Home] = tr("HOME");
    m_commandNames[Command::Takeoff] = tr("TAKEOFF");
    m_commandNames[Command::Waypoint] = tr("WAYPOINT");
    m_commandNames[Command::LoiterAltitude] = tr("LOITER ALT");
    m_commandNames[Command::LoiterTurns] = tr("LOITER TURNS");
    m_commandNames[Command::Continue] = tr("CONTINUE");
    m_commandNames[Command::Return] = tr("RETURN");
    m_commandNames[Command::Landing] = tr("LANDING");
}

domain::AbstractMissionItem* MissionViewHelper::cast(QObject* item) const
{
    return qobject_cast<domain::AbstractMissionItem*>(item);
}

QStringList MissionViewHelper::avaliableCommands(QObject* item) const
{
    if (!item) return { tr("EMPTY") };
    QStringList commands;

    for (Command command: this->cast(item)->avalibleCommands())
    {
        commands << m_commandNames.value(command, tr("ERROR"));
    }

    return commands;
}

QString MissionViewHelper::command(QObject* item) const
{
    if (!item) return tr("EMPTY");
    return m_commandNames.value(this->cast(item)->command(), tr("ERROR"));;
}

void MissionViewHelper::setCommand(QObject* item, const QString& command)
{
    if (!item) return;
    QStringList avalibleCommands = this->avaliableCommands(item);
    int index = avalibleCommands.indexOf(command);

    if (index > -1)
    {
        domain::AbstractMissionItem* missionItem = this->cast(item);
        missionItem->replaceWithCommand(
                    this->cast(missionItem)->avalibleCommands()[index]);
    }
}
