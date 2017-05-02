#include "mission.h"

// Internal
#include "mission_item.h"

using namespace db;

QString Mission::name() const
{
    return m_name;
}

void Mission::setName(const QString& name)
{
    m_name = name;
}

