#ifndef NOTIFICATION_BUS_H
#define NOTIFICATION_BUS_H

// Internal
#include "notification.h"

// Qt
#include <QMutex>

namespace domain
{
    class NotificationBus: public QObject
    {
        Q_OBJECT

    public:
        static NotificationBus* instance();

        static const QList<dto::Notification>& logs();

        static void log(const dto::Notification& message);
        static void log(const QString& message,
                        dto::Notification::Urgency type = dto::Notification::Common,
                        int time = 5000);

    signals:
        void logAdded(dto::Notification message);

    private:
        NotificationBus();

        QList<dto::Notification> m_messages;
        QMutex m_mutex;
    };
}

#endif // NOTIFICATION_BUS_H
