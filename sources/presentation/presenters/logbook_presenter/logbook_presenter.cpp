#include "logbook_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "log_bus.h"

using namespace presentation;

LogbookPresenter::LogbookPresenter(QObject* parent):
    BasePresenter(parent)
{}

void LogbookPresenter::updateLog()
{
    QVariantList logs;

    for (const domain::LogMessage& message: domain::LogBus::logs())
    {
        logs.append(QVariant::fromValue(message));
    }

    this->setViewProperty(PROPERTY(logs), logs);
}

void LogbookPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->updateLog();

    connect(domain::LogBus::instance(), &domain::LogBus::logAdded,
            this, &LogbookPresenter::updateLog);
}
