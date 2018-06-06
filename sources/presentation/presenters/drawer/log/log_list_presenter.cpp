#include "log_list_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "notification_bus.h"

using namespace presentation;

LogListPresenter::LogListPresenter(QObject* parent):
    BasePresenter(parent)
{}

void LogListPresenter::updateLog() // TODO: to QAbstractListModel
{
    QVariantList logs;

    for (const dto::Notification& message: notificationBus->notifications())
    {
        logs.append(QVariant::fromValue(message));
    }

    this->setViewProperty(PROPERTY(logs), logs);
}

void LogListPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->updateLog();

    connect(notificationBus, &domain::NotificationBus::notificated,
            this, &LogListPresenter::updateLog);
}
