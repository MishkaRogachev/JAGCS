#include "notifications_presenter.h"

// Qt
#include <QDebug>
#include <QSortFilterProxyModel>

// Internal
#include "notification_bus.h"
#include "notification_list_model.h"

using namespace presentation;

class NotificationsPresenter::Impl
{
public:
    NotificationListModel notificationsModel;
    QSortFilterProxyModel filterModel;
};

NotificationsPresenter::NotificationsPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->filterModel.setSourceModel(&d->notificationsModel);
    d->filterModel.setSortRole(NotificationListModel::UrgencyRole);
    d->filterModel.setDynamicSortFilter(true);
    d->filterModel.sort(0, Qt::DescendingOrder);

    connect(notificationBus, &domain::NotificationBus::notificated,
            this, &NotificationsPresenter::addNotification);
}

NotificationsPresenter::~NotificationsPresenter()
{}

void NotificationsPresenter::addNotification(const dto::Notification& notification)
{
    d->notificationsModel.addNotification(notification);
}

void NotificationsPresenter::remove(const QString& header)
{
    d->notificationsModel.remove(header);
}

void NotificationsPresenter::removeLast()
{
    d->notificationsModel.removeLast();
}

void NotificationsPresenter::connectView(QObject* view)
{
    view->setProperty(PROPERTY(notifications), QVariant::fromValue(&d->filterModel));
}
