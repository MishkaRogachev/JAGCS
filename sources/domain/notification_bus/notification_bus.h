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

        const QList<dto::Notification>& notifications();

    public slots:
        void notify(const dto::Notification& notification);
        void notify(const QString& head, const QString& message,
                    dto::Notification::Urgency urgency = dto::Notification::Common,
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
