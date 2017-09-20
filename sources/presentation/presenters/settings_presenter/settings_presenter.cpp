#include "settings_presenter.h"

// Internal
#include "settings_provider.h"

#include "data_base_presenter.h"
#include "vehicles_presenter.h"
#include "communication_settings_presenter.h"
#include "video_settings_presenter.h"

#include "map_settings_presenter.h"
#include "joystick_settings_presenter.h"
#include "gui_settings_presenter.h"
#include "network_settings_presenter.h"
#include "about_presenter.h"

using namespace presentation;

class SettingsPresenter::Impl
{
public:
    DataBasePresenter* dataBase;
    CommunicationSettingsPresenter* communications;
    VehiclesPresenter* vehicles;
    VideoSettingsPresenter* video;

    MapSettingsPresenter* map;
    JoystickSettingsPresenter* joystick;
    GuiSettingsPresenter* gui;
    NetworkSettingsPresenter* network;
    AboutPresenter* about;
};

SettingsPresenter::SettingsPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->dataBase = new DataBasePresenter(this);
    d->communications = new CommunicationSettingsPresenter(this);
    d->vehicles = new VehiclesPresenter(this);
    d->video = new VideoSettingsPresenter(this);

    d->map = new MapSettingsPresenter(this);
    d->joystick = new JoystickSettingsPresenter(this);
    d->gui = new GuiSettingsPresenter(this);
    d->network = new NetworkSettingsPresenter(this);
    d->about = new AboutPresenter(this);
}

SettingsPresenter::~SettingsPresenter()
{}

void SettingsPresenter::show()
{
    this->setViewProperty(PROPERTY(visible), true);
}

void SettingsPresenter::hide()
{
    this->setViewProperty(PROPERTY(visible), false);
}

void SettingsPresenter::connectView(QObject* view)
{
    d->dataBase->setView(view->findChild<QObject*>(NAME(dataBase)));
    d->communications->setView(view->findChild<QObject*>(NAME(communications)));
    d->vehicles->setView(view->findChild<QObject*>(NAME(vehicles)));
    d->video->setView(view->findChild<QObject*>(NAME(video)));

    d->map->setView(view->findChild<QObject*>(NAME(map)));
    d->joystick->setView(view->findChild<QObject*>(NAME(joystick)));
    d->gui->setView(view->findChild<QObject*>(NAME(gui)));
    d->network->setView(view->findChild<QObject*>(NAME(network)));
    d->about->setView(view->findChild<QObject*>(NAME(about)));

    connect(view, SIGNAL(makeDefaults()), this, SLOT(onMakeDefaults()));
}

void SettingsPresenter::onMakeDefaults()
{
    settings::Provider::makeDefaults();
}
