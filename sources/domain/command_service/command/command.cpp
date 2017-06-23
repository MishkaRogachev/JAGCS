#include "command.h"

using namespace domain;

Command::Command(CommandType type):
    m_type(type)
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
