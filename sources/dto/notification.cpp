#include "notification.h"

using namespace dto;

Notification::Notification(const QTime& timestamp,
                           const QString& head,
                           const QString& message,
                           Notification::Urgency type,
                           int time):
    m_timestamp(timestamp),
    m_head(head),
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

QString Notification::head() const
{
    return m_head;
}

void Notification::setHead(const QString& head)
{
    m_head = head;
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

bool Notification::operator ==(const Notification& other)
{
    return m_timestamp == other.m_timestamp &&
            m_head == other.m_head &&
            m_message == other.m_message &&
            m_urgency == other.m_urgency &&
            m_time == other.m_time;
}
