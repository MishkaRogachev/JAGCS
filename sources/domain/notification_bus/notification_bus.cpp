#include "notification_bus.h"

// Qt
#include <QMutexLocker>
#include <QDebug>

using namespace domain;

NotificationBus* NotificationBus::instance()
{
    static NotificationBus bus;
    return &bus;
}

const QList<dto::Notification>& NotificationBus::logs()
{
    QMutexLocker locker(&instance()->m_mutex);
    return instance()->m_messages;
}

void NotificationBus::log(const dto::Notification& message)
{
    QMutexLocker locker(&instance()->m_mutex);
    instance()->m_messages.append(message);
    emit instance()->logAdded(message);
}

void NotificationBus::log(const QString& message, dto::Notification::Urgency type, int time)
{
    NotificationBus::log(dto::Notification(QTime::currentTime(), message, type, time));
}

NotificationBus::NotificationBus():
    m_mutex(QMutex::Recursive)
{
    qRegisterMetaType<dto::Notification>("dto::Notification");
}
