#include "presenters_factory.h"

// Internal
#include "topbar_presenter.h"

#include "location_map_presenter.h"
#include "active_video_presenter.h"

#include "communications_presenter.h"
#include "vehicles_presenter.h"
#include "planning_presenter.h"
#include "about_presenter.h"

using namespace presentation;

PresentersFactory::PresentersFactory(QObject* parent):
    QObject(parent)
{}

QObject* PresentersFactory::createTopbarPresenter(QObject* view)
{
    TopbarPresenter* topBar = new TopbarPresenter(view);
    topBar->setView(view);
    return topBar;
}

QObject* PresentersFactory::createMapPresenter(QObject* view)
{
    AbstractMapPresenter* map = new LocationMapPresenter(view);
    map->setView(view);
    return map;
}

QObject* PresentersFactory::createVideoPresenter(QObject* view)
{
    VideoPresenter* video = new ActiveVideoPresenter(view);
    video->setView(view);
    return video;
}

QObject* PresentersFactory::createCommunicationPresenter(QObject* view)
{
    CommunicationsPresenter* comm = new CommunicationsPresenter(view);
    comm->setView(view);
    return comm;
}

QObject*PresentersFactory::createVehiclesPresenter(QObject* view)
{
    VehiclesPresenter* vehicles = new VehiclesPresenter(view);
    vehicles->setView(view);
    return vehicles;
}

QObject* PresentersFactory::createPlanningPresenter(QObject* view)
{
    PlanningPresenter* planning = new PlanningPresenter(view);
    planning->setView(view);
    return planning;
}

QObject* PresentersFactory::createAboutPresenter(QObject* view)
{
    AboutPresenter* about = new AboutPresenter(view);
    about->setView(view);
    return about;
}
