#include "flight_view_helper.h"

// Qt
#include <QVariant>

// Internal
#include "abstract_vehicle.h"

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
    auto  vehicle = qobject_cast<domain::AbstractVehicle*>(object);
    if (!vehicle) return;

    domain::Command cmd = m_commandNames.key(
                              command, domain::Command::UnknownCommand);
    vehicle->executeCommand(cmd, {} ); // TODO: args
}
