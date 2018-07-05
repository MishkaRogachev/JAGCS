#include "notification_bus.h"

// Qt
#include <QMultiHash>
#include <QMutexLocker>
#include <QDebug>

using namespace domain;

NotificationBus* NotificationBus::lastCreatedBus = nullptr;

class NotificationBus::Impl
{
public:
    QList<dto::Notification> notifications;
    QMutex mutex;

    Impl():
        mutex(QMutex::Recursive)
    {}
};

NotificationBus::NotificationBus(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    NotificationBus::lastCreatedBus = this;

    qRegisterMetaType<dto::Notification>("dto::Notification");
}

NotificationBus::~NotificationBus()
{}

NotificationBus* NotificationBus::instance()
{
    return NotificationBus::lastCreatedBus;
}

const QList<dto::Notification>& NotificationBus::notifications()
{
    QMutexLocker locker(&d->mutex);
    return d->notifications;
}

void NotificationBus::notify(const dto::Notification& notification)
{
    QMutexLocker locker(&d->mutex);

    d->notifications.append(notification);
    emit notificated(notification);
}

void NotificationBus::notify(const QString& head, const QString& message,
                          dto::Notification::Urgency type, int time)
{
    this->notify(dto::Notification(QTime::currentTime(), head, message, type, time));
}

