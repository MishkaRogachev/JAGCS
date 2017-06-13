#include "main_presenter.h"

// Qt
#include <QMap>
#include <QVariant>

// Internal
#include "domain_entry.h"

#include "statusbar_presenter.h"
#include "control_presenter.h"
#include "mission_presenter.h"
#include "settings_presenter.h"

using namespace presentation;

class MainPresenter::Impl
{
public:
    domain::DomainEntry* entry;

    StatusbarPresenter* statusbar;
    BasePresenter* modePresenter = nullptr;
};

MainPresenter::MainPresenter(domain::DomainEntry* entry, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->entry = entry;

    d->statusbar = new StatusbarPresenter(this);
    connect(d->statusbar, &StatusbarPresenter::setMode, this, &MainPresenter::setMode);
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

    if (mode == "control") // TODO: MainPresenter mode enum
    {
        d->modePresenter = new ControlPresenter(d->entry, this);
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
    d->statusbar->setView(view->findChild<QObject*>(NAME(statusbar)));

    this->invokeViewMethod(PROPERTY(updateUiSettings));
}
