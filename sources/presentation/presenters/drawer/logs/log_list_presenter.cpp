#include "log_list_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "notification_bus.h"

using namespace presentation;

class LogListPresenter::Impl
{
public:
    domain::NotificationBus* bus = domain::NotificationBus::instance();
};

LogListPresenter::LogListPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    connect(d->bus, &domain::NotificationBus::notificated, this, &LogListPresenter::updateLogs);
}

LogListPresenter::~LogListPresenter()
{}

void LogListPresenter::updateLogs() // TODO: to QAbstractListModel
{
    QVariantList logs;

    for (const dto::Notification& notifications: d->bus->notifications())
    {
        logs.append(QVariant::fromValue(notifications));
    }

    this->setViewProperty(PROPERTY(logs), logs);
}
