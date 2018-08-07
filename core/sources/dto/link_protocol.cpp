#include "link_protocol.h"

// Qt
#include <QDebug>

using namespace dto;

QString LinkProtocol::name() const
{
    return m_name;
}

void LinkProtocol::setName(const QString& name)
{
    m_name = name;
}

QString LinkProtocol::description() const
{
    return m_description;
}

void LinkProtocol::setDescription(const QString& description)
{
    m_description = description;
}
