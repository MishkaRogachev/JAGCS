#include "mission_view_helper.h"

// Qt
#include <QVariant>

// Internal
#include "mission_item.h"

using namespace presentation;

MissionViewHelper::MissionViewHelper(QObject* parent):
    QObject(parent)
{
    m_commandNames[domain::Command::UnknownCommand] = tr("UNKNOWN");
    m_commandNames[domain::Command::Home] = tr("HOME");
    m_commandNames[domain::Command::Takeoff] = tr("TAKEOFF");
    m_commandNames[domain::Command::Waypoint] = tr("WAYPOINT");
    m_commandNames[domain::Command::LoiterAltitude] = tr("LOITER ALT");
    m_commandNames[domain::Command::LoiterTurns] = tr("LOITER TURNS");
    m_commandNames[domain::Command::Continue] = tr("CONTINUE");
    m_commandNames[domain::Command::Return] = tr("RETURN");
    m_commandNames[domain::Command::Landing] = tr("LANDING");
}

domain::MissionItem* MissionViewHelper::cast(QObject* item) const
{
    return qobject_cast<domain::MissionItem*>(item);
}

QStringList MissionViewHelper::avaliableCommands(QObject* item) const
{
    if (!item) return { tr("EMPTY") };
    QStringList commands;

    for (domain::Command command: this->cast(item)->avalibleCommands())
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
        domain::MissionItem* missionItem = this->cast(item);
        missionItem->replaceWithCommand(
                    this->cast(missionItem)->avalibleCommands()[index]);
    }
}
