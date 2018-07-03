#include "command.h"

using namespace dto;

Command::CommandType Command::type() const
{
    return m_type;
}

void Command::setType(CommandType type)
{
    m_type = type;
}

Command::CommandStatus Command::status() const
{
    return m_status;
}

void Command::setStatus(CommandStatus status)
{
    m_status = status;
}

QVariantList Command::arguments() const
{
    return m_arguments;
}

void Command::setArguments(const QVariantList& arguments)
{
    m_arguments = arguments;
}

void Command::addArgument(const QVariant& argument)
{
    m_arguments.append(argument);
}

bool Command::isFinished() const
{
    return m_status == Rejected || m_status == Canceled || m_status == Completed;
}
