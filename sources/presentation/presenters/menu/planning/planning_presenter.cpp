#include "planning_presenter.h"

// Internal
#include "mission_list_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

class PlanningPresenter::Impl
{
public:
    MissionListPresenter* missions;
};

PlanningPresenter::PlanningPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->missions = new MissionListPresenter(this);
}

PlanningPresenter::~PlanningPresenter()
{}

void PlanningPresenter::connectView(QObject* view)
{
    d->missions->setView(this->view()->findChild<QObject*>("missions"));
}
