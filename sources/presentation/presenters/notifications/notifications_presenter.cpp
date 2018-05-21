#include "notifications_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "log_bus.h"

using namespace presentation;

NotificationsPresenter::NotificationsPresenter(QObject* parent):
    BasePresenter(parent)
{
    connect(domain::LogBus::instance(), &domain::LogBus::logAdded,
            this, &NotificationsPresenter::onLogAdded);
}

void NotificationsPresenter::onLogAdded(const dto::LogMessage& message)
{
    this->invokeViewMethod(PROPERTY(addLog), QVariant::fromValue(message));
}
