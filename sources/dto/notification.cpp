#include "notification.h"

using namespace dto;

Notification::Notification(const QTime& timestamp,
                       const QString& message,
                       Notification::Urgency type,
                       int time):
    m_timestamp(timestamp),
    m_message(message),
    m_urgency(type),
    m_time(time)
{}

QTime Notification::timestamp() const
{
    return m_timestamp;
}

void Notification::setTimestamp(const QTime& timestamp)
{
    m_timestamp = timestamp;
}

QString Notification::message() const
{
    return m_message;
}

void Notification::setMessage(const QString& message)
{
    m_message = message;
}

Notification::Urgency Notification::urgency() const
{
    return m_urgency;
}

void Notification::setUrgency(Notification::Urgency urgency)
{
    m_urgency = urgency;
}

int Notification::time() const
{
    return m_time;
}

void Notification::setTime(int time)
{
    m_time = time;
}
