#include "log_message.h"

using namespace domain;

LogMessage::LogMessage(const QTime& timestamp, const QString& message, LogMessage::LogType type):
    m_timestamp(timestamp),
    m_message(message),
    m_type(type)
{}

QTime LogMessage::timestamp() const
{
    return m_timestamp;
}

void LogMessage::setTimestamp(const QTime& timestamp)
{
    m_timestamp = timestamp;
}

QString LogMessage::message() const
{
    return m_message;
}

void LogMessage::setMessage(const QString& message)
{
    m_message = message;
}

LogMessage::LogType LogMessage::type() const
{
    return m_type;
}

void LogMessage::setType(LogMessage::LogType type)
{
    m_type = type;
}
