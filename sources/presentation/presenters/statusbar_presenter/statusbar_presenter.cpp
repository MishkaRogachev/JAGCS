#include "statusbar_presenter.h"

// Qt
#include <QGuiApplication>

// Internal
#include "service_registry.h"
#include "telemetry_service.h"

#include "radio_presenter.h"
#include "logbook_presenter.h"

using namespace presentation;

class StatusbarPresenter::Impl
{
public:
    RadioPresenter* radio;
    LogbookPresenter* logbook;
};

StatusbarPresenter::StatusbarPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->radio = new RadioPresenter(domain::ServiceRegistry::telemetryService()->radioNode(), this);
    d->logbook = new LogbookPresenter(this);
}

StatusbarPresenter::~StatusbarPresenter()
{}

void StatusbarPresenter::setStatusbarEnabled(bool enabled)
{
    this->setViewProperty(PROPERTY(enabled), enabled);
}

void StatusbarPresenter::connectView(QObject* view)
{
    d->radio->setView(view->findChild<QObject*>(NAME(radio)));
    d->logbook->setView(view->findChild<QObject*>(NAME(logbook)));

    connect(view, SIGNAL(setMode(int)), this, SIGNAL(setMode(int)));
    connect(view, SIGNAL(quit()), qApp, SLOT(quit()));
}
