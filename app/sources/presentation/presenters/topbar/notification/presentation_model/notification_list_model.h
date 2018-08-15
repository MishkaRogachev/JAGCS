#ifndef NOTIFICATION_LIST_MODEL_H
#define NOTIFICATION_LIST_MODEL_H

// Qt
#include <QAbstractListModel>
#include <QMultiMap>

// Internal
#include "notification.h"

namespace presentation
{
    class NotificationListModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum VideoSourceListRoles
        {
            HeaderRole = Qt::UserRole + 1,
            MessagesRole,
            UrgencyRole,
            TimeRole
        };

        explicit NotificationListModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void addNotification(const dto::Notification& notification);
        void addNotifications(const QList<dto::Notification>& notifications);
        void remove(const QString& header);
        void removeLast();

    protected:
        QHash<int, QByteArray> roleNames() const override;

    private:
        QStringList m_headers;
        QMultiMap<QString, dto::Notification> m_notifications;
    };
}

#endif // NOTIFICATION_LIST_MODEL_H
