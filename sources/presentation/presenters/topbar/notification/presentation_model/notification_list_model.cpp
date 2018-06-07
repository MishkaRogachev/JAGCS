#include "notification_list_model.h"

// Qt
#include <QVariant>
#include <QDebug>

namespace
{
    const int maxHeadMessages = 5;
}

using namespace presentation;

NotificationListModel::NotificationListModel(QObject* parent):
    QAbstractListModel(parent)
{}

int NotificationListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return m_headers.count();
}

QVariant NotificationListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_headers.count()) return QVariant();

    QString header = m_headers.at(index.row());

    if (role == HeaderRole) return header;
    if (role == MessagesRole)
    {
        QList<dto::Notification> notifications = m_notifications.values(header);
        QStringList messages;

        for (const dto::Notification& notification: notifications)
        {
            messages.append(notification.message());
        }

        return messages;
    }
    if (role == UrgencyRole || role == TimeRole)
    {
        dto::Notification notification = m_notifications.value(header);
        return role == UrgencyRole ? notification.urgency() : notification.time();
    }
    return QVariant();
}

void NotificationListModel::addNotification(const dto::Notification& notification)
{
    QString head = notification.head();
    m_notifications.insertMulti(head, notification);

    if (m_headers.contains(head))
    {
        if (m_notifications.count(head) > ::maxHeadMessages)
        {
            dto::Notification firstNotification = m_notifications.values(head).first();
            m_notifications.remove(head, firstNotification);
        }

        QModelIndex index = this->index(m_headers.indexOf(head));
        emit dataChanged(index, index, { MessagesRole, UrgencyRole, TimeRole });
    }
    else
    {
        this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
        m_headers.append(head);
        this->endInsertRows();
    }
}

void NotificationListModel::remove(const QString& header)
{
    int row = m_headers.indexOf(header);
    if (row == -1) return;

    this->beginRemoveRows(QModelIndex(), row, row);

    m_headers.removeOne(header);
    m_notifications.remove(header);

    this->endRemoveRows();
}

void NotificationListModel::removeLast()
{
    this->remove(m_headers.last());
}

QHash<int, QByteArray> NotificationListModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[HeaderRole] = "header";
    roles[MessagesRole] = "messages";
    roles[UrgencyRole] = "urgency";
    roles[TimeRole] = "time";

    return roles;
}
