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

void NotificationsPresenter::initLog()
{
    const QList<domain::LogMessage>& logs = domain::LogBus::instance()->logs();
    this->setViewProperty(PROPERTY(count), logs.count());

    if (!logs.isEmpty())
    {
        this->setViewProperty(PROPERTY(type), logs.last().type());
    }
}

void NotificationsPresenter::onLogAdded(const domain::LogMessage& message)
{
    this->invokeViewMethod(PROPERTY(logAdded));
    this->setViewProperty(PROPERTY(type), message.type());
}
