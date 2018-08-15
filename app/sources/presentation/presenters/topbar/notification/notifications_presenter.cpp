#include "notifications_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "notification_bus.h"
#include "notification_list_model.h"

using namespace presentation;

NotificationsPresenter::NotificationsPresenter(QObject* parent):
    BasePresenter(parent),
    m_model(new NotificationListModel(this))
{
    connect(notificationBus, &domain::NotificationBus::notificated,
            this, &NotificationsPresenter::addNotification);

    m_model->addNotifications(notificationBus->notifications());
}

void NotificationsPresenter::addNotification(const dto::Notification& notification)
{
    m_model->addNotification(notification);
}

void NotificationsPresenter::connectView(QObject* view)
{
    view->setProperty(PROPERTY(notifications), QVariant::fromValue(m_model));
}
