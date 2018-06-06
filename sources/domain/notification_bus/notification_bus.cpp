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
    QMultiHash<QString, dto::Notification> messages;
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

QList<dto::Notification> NotificationBus::notifications()
{
    QMutexLocker locker(&d->mutex);
    return d->messages.values();
}

QList<dto::Notification> NotificationBus::notifications(const QString& head)
{
    QMutexLocker locker(&d->mutex);
    return d->messages.values(head);
}

void NotificationBus::notify(const dto::Notification& message)
{
    QMutexLocker locker(&d->mutex);

    d->messages.insertMulti(message.head(), message);
    emit notificated(message);
}

void NotificationBus::notify(const QString& head, const QString& message,
                          dto::Notification::Urgency type, int time)
{
    this->notify(dto::Notification(QTime::currentTime(), head, message, type, time));
}

