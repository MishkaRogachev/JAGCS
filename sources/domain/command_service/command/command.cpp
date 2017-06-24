#include "command.h"

using namespace domain;

Command::Command(CommandType type, int vehicleId):
    m_type(type),
    m_vehicleId(vehicleId)
{}

Command::CommandType Command::type() const
{
    return m_type;
}

void Command::setType(CommandType type)
{
    m_type = type;
}

QVariantList Command::arguments() const
{
    return m_arguments;
}

void Command::setArguments(const QVariantList& arguments)
{
    m_arguments = arguments;
}

int Command::vehicleId() const
{
    return m_vehicleId;
}

void Command::setVehicleId(int vehicleId)
{
    m_vehicleId = vehicleId;
}
