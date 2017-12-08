#include "command.h"

using namespace domain;

Command::Command(CommandType type, CommandStatus status):
    m_type(type),
    m_status(status)
{}

Command::Command(const Command& command):
    m_type(command.type()),
    m_status(command.status()),
    m_arguments(command.arguments())
{}

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
