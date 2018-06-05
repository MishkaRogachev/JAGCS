#include "notifications_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "notification_bus.h"

using namespace presentation;

NotificationsPresenter::NotificationsPresenter(QObject* parent):
    BasePresenter(parent)
{
    connect(domain::NotificationBus::instance(), &domain::NotificationBus::logAdded,
            this, &NotificationsPresenter::onLogAdded);
}

void NotificationsPresenter::onLogAdded(const dto::Notification& message)
{
    this->invokeViewMethod(PROPERTY(addLog), QVariant::fromValue(message));
}
