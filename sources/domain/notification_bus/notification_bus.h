#ifndef NOTIFICATION_BUS_H
#define NOTIFICATION_BUS_H

// Internal
#include "notification.h"

namespace domain
{
    class NotificationBus: public QObject
    {
        Q_OBJECT

    public:
        explicit NotificationBus(QObject* parent = nullptr);
        ~NotificationBus() override;

        static NotificationBus* instance();

        QList<dto::Notification> notifications();
        QList<dto::Notification> notifications(const QString& head);

        void notify(const dto::Notification& message);
        void notify(const QString& head, const QString& message,
                 dto::Notification::Urgency type = dto::Notification::Common,
                 int time = 5000);

    signals:
        void notificated(dto::Notification message);

    private:
        class Impl;
        QScopedPointer<Impl> const d;

        static NotificationBus* lastCreatedBus;

        Q_DISABLE_COPY(NotificationBus)
    };
}

#define notificationBus (domain::NotificationBus::instance())

#endif // NOTIFICATION_BUS_H
