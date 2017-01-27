#include "mission_view_helper.h"

// Qt
#include <QVariant>

// Internal
#include "mission_item.h"

using namespace presentation;

MissionViewHelper::MissionViewHelper(QObject* parent):
    QObject(parent)
{
    m_commandNames[domain::MissionItem::UnknownCommand] = tr("UNKNOWN");
    m_commandNames[domain::MissionItem::Home] = tr("HOME");
    m_commandNames[domain::MissionItem::Takeoff] = tr("TAKEOFF");
    m_commandNames[domain::MissionItem::Waypoint] = tr("WAYPOINT");
    m_commandNames[domain::MissionItem::LoiterAltitude] = tr("LOITER ALT");
    m_commandNames[domain::MissionItem::LoiterTurns] = tr("LOITER TURNS");
    m_commandNames[domain::MissionItem::Continue] = tr("CONTINUE");
    m_commandNames[domain::MissionItem::Return] = tr("RETURN");
    m_commandNames[domain::MissionItem::Landing] = tr("LANDING");
}

domain::MissionItem* MissionViewHelper::cast(QObject* item) const
{
    return qobject_cast<domain::MissionItem*>(item);
}

QStringList MissionViewHelper::avalibleCommands(QObject* item) const
{
    if (!item) return { tr("EMPTY") };
    QStringList commands;

    for (domain::MissionItem::Command command:
         this->cast(item)->avalibleCommands())
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
    QStringList avalibleCommands = this->avalibleCommands(item);
    int index = avalibleCommands.indexOf(command);

    if (index > -1)
    {
        domain::MissionItem* missionItem = this->cast(item);
        missionItem->replaceWithCommand(
                    this->cast(missionItem)->avalibleCommands()[index]);
    }
}
