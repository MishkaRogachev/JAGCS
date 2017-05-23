#include "status.h"

using namespace domain;

Status::Status(bool armed, const QString& modeString):
    m_armed(armed),
    m_modeString(modeString)
{}

bool Status::armed() const
{
    return m_armed;
}

QString Status::modeString() const
{
    return m_modeString;
}

bool Status::operator ==(const Status& other)
{
    return m_armed == other.armed() && m_modeString == other.modeString();
}
