#include "main_presenter.h"

// Qt
#include <QMap>
#include <QVariant>

// Internal
#include "statusbar_presenter.h"
#include "control_presenter.h"
#include "planning_presenter.h"
#include "settings_presenter.h"

using namespace presentation;

class MainPresenter::Impl
{
public:
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
        d->modePresenter = new ControlPresenter(this);
    }
    if (mode == "planning")
    {
        d->modePresenter = new PlanningPresenter(this);
    }
    else if (mode == "settings")
    {
        d->modePresenter = new SettingsPresenter(this);
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
