#include "main_presenter.h"

// Qt
#include <QMap>
#include <QVariant>

// Internal
#include "domain_entry.h"

#include "status_presenter.h"
#include "flight_presenter.h"
#include "mission_presenter.h"
#include "settings_presenter.h"

using namespace presentation;

class MainPresenter::Impl
{
public:
    domain::DomainEntry* entry;

    StatusPresenter* status;
    BasePresenter* modePresenter = nullptr;
};

MainPresenter::MainPresenter(domain::DomainEntry* entry, QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    d->entry = entry;

    d->status = new StatusPresenter(this);
    connect(d->status, &StatusPresenter::setMode, this, &MainPresenter::setMode);
}

MainPresenter::~MainPresenter()
{}

void MainPresenter::setMode(const QString& mode)
{
    if (mode == this->viewProperty(PROPERTY(mode))) return;

    if (d->modePresenter)
    {
        delete d->modePresenter;
        d->modePresenter = nullptr;
    }

    this->setViewProperty(PROPERTY(mode), mode);

    if (mode == "flight") // TODO: MainPresenter mode enum
    {
        d->modePresenter = new FlightPresenter(d->entry->vehicleService(),
                                               this);
    }
    if (mode == "mission")
    {
        d->modePresenter = new MissionPresenter(d->entry, this);
    }
    else if (mode == "settings")
    {
        d->modePresenter = new SettingsPresenter(d->entry, this);
    }

    if (d->modePresenter)
    {
        d->modePresenter->setView(m_view->findChild<QObject*>(mode));
    }
}

void MainPresenter::connectView(QObject* view)
{
    d->status->setView(view->findChild<QObject*>(NAME(status)));

    this->invokeViewMethod(PROPERTY(updateUiSettings));
}
