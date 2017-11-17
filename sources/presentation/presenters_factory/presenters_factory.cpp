#include "presenters_factory.h"

// Internal
#include "topbar_presenter.h"

#include "location_map_presenter.h"
#include "active_video_presenter.h"

#include "communications_presenter.h"
#include "vehicles_presenter.h"
#include "planning_presenter.h"
#include "about_presenter.h"

#include "database_presenter.h"
#include "gui_settings_presenter.h"
#include "joystick_settings_presenter.h"
#include "map_settings_presenter.h"
#include "network_settings_presenter.h"
#include "video_settings_presenter.h"

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

QObject* PresentersFactory::createDatabasePresenter(QObject* view)
{
    DatabasePresenter* db = new DatabasePresenter(view);
    db->setView(view);
    return db;
}

QObject* PresentersFactory::createGuiSettingsPresenter(QObject* view)
{
    GuiSettingsPresenter* gui = new GuiSettingsPresenter(view);
    gui->setView(view);
    return gui;
}

QObject* PresentersFactory::createJoystickSettingsPresenter(QObject* view)
{
    JoystickSettingsPresenter* joystick = new JoystickSettingsPresenter(view);
    joystick->setView(view);
    return joystick;
}

QObject* PresentersFactory::createMapSettingsPresenter(QObject* view)
{
    MapSettingsPresenter* mapSettings = new MapSettingsPresenter(view);
    mapSettings->setView(view);
    return mapSettings;
}

QObject* PresentersFactory::createNetworkSettingsPresenter(QObject* view)
{
    NetworkSettingsPresenter* network = new NetworkSettingsPresenter(view);
    network->setView(view);
    return network;
}

QObject* PresentersFactory::createVideoSettingsPresenter(QObject* view)
{
    VideoSettingsPresenter* video = new VideoSettingsPresenter(view);
    video->setView(view);
    return video;
}
