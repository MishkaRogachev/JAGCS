#include "main_presenter.h"

// Internal
#include "domain_entry.h"

#include "status_presenter.h"
#include "flight_presenter.h"
#include "settings_presenter.h"

using namespace presentation;

class MainPresenter::Impl
{
public:
    StatusPresenter* status;
    FlightPresenter* flight;
    SettingsPresenter* settings;
};

MainPresenter::MainPresenter(domain::DomainEntry* entry, QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    d->status = new StatusPresenter(this);
    d->flight = new FlightPresenter(entry->vehicleService(), this);
    d->settings = new SettingsPresenter(entry, this);

    connect(d->status, &StatusPresenter::showSettings,
            d->settings, &SettingsPresenter::show);
    connect(d->status, &StatusPresenter::hideSettings,
            d->settings, &SettingsPresenter::hide);
}

MainPresenter::~MainPresenter()
{
    delete d;
}

void MainPresenter::connectView(QObject* view)
{
    d->status->setView(view->findChild<QObject*>(NAME(status)));
    d->flight->setView(view->findChild<QObject*>(NAME(flight)));
    d->settings->setView(view->findChild<QObject*>(NAME(settings)));
}
