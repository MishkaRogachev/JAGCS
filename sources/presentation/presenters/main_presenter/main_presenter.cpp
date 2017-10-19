#include "main_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "statusbar_presenter.h"
#include "control_presenter.h"
#include "planning_presenter.h"
#include "settings_presenter.h"

using namespace presentation;

class MainPresenter::Impl
{
public:
    MainPresenter::Mode mode = MainPresenter::NoMode;

    StatusbarPresenter* statusbar;
    BasePresenter* modePresenter = nullptr;
};

MainPresenter::MainPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->statusbar = new StatusbarPresenter(this);
    connect(d->statusbar, &StatusbarPresenter::setMode, this, &MainPresenter::setMode);
}

MainPresenter::~MainPresenter()
{}

MainPresenter::Mode MainPresenter::mode() const
{
    return d->mode;
}

void MainPresenter::setMode(int iMode)
{
    Mode mode = static_cast<Mode>(iMode);
    if (mode == d->mode) return;
    d->mode = mode;

    if (d->modePresenter)
    {
        delete d->modePresenter;
        d->modePresenter = nullptr;
    }

    switch (d->mode) {
    case Control:
        d->modePresenter = new ControlPresenter(this);
        d->modePresenter->setView(m_view->findChild<QObject*>("control"));
        break;
    case Planning:
        d->modePresenter = new PlanningPresenter(this);
        d->modePresenter->setView(m_view->findChild<QObject*>("planning"));
        break;
    case Settings:
        d->modePresenter = new SettingsPresenter(this);
        d->modePresenter->setView(m_view->findChild<QObject*>("settings"));
        break;
    default:
        break;
    }

    this->setViewProperty(PROPERTY(mode), d->mode);
}

void MainPresenter::connectView(QObject* view)
{
    d->statusbar->setView(view->findChild<QObject*>(NAME(statusbar)));
}
