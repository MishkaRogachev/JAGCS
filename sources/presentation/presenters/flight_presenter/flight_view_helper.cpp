#include "flight_view_helper.h"

// Qt
#include <QVariant>

// Internal
#include "vehicle.h"

using namespace presentation;

FlightViewHelper::FlightViewHelper(QObject* parent):
    QObject(parent)
{
    m_commandNames[domain::Command::Return] = tr("RETURN");
    m_commandNames[domain::Command::Arm] = tr("ARM");
    m_commandNames[domain::Command::Disarm] = tr("DISARM");
}

QStringList FlightViewHelper::avaliableCommands() const
{
    return m_commandNames.values();
}

void FlightViewHelper::executeCommand(const QString& command, QObject* object)
{
    domain::Vehicle* vehicle = qobject_cast<domain::Vehicle*>(object);
    if (!vehicle) return;

    domain::Command cmd = m_commandNames.key(
                              command, domain::Command::UnknownCommand);
    vehicle->executeCommand(cmd, {} ); // TODO: args
}
