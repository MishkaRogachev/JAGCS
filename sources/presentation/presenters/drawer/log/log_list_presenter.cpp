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

    for (const dto::Notification& message: domain::NotificationBus::logs())
    {
        logs.append(QVariant::fromValue(message));
    }

    this->setViewProperty(PROPERTY(logs), logs);
}

void LogListPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->updateLog();

    connect(domain::NotificationBus::instance(), &domain::NotificationBus::logAdded,
            this, &LogListPresenter::updateLog);
}
