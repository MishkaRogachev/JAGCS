#include "menu_presenter.h"

// Qt
#include <QMap>
#include <QDebug>

// Internal
#include "communications_presenter.h"
#include "vehicles_presenter.h"

#include "mission_presenter.h"

#include "database_presenter.h"
#include "map_settings_presenter.h"
#include "video_settings_presenter.h"
#include "joystick_settings_presenter.h"
#include "gui_settings_presenter.h"
#include "network_settings_presenter.h"

#include "about_presenter.h"

using namespace presentation;

class MenuPresenter::Impl
{
public:
    MapHandle* handle;

    BasePresenter* presenter = nullptr;
};

MenuPresenter::MenuPresenter(MapHandle* handle, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->handle = handle;
}

MenuPresenter::~MenuPresenter()
{}

void MenuPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(requestPresenter(QString)), this, SLOT(onRequestPresenter(QString)));
}

void MenuPresenter::onRequestPresenter(const QString& view)
{
    if (d->presenter)
    {
        delete d->presenter;
        d->presenter = nullptr;
    }

    if (view == "communications") d->presenter = new CommunicationsPresenter(this);
    else if (view == "vehicles") d->presenter = new VehiclesPresenter(this);

    else if (view == "mission") d->presenter = new MissionPresenter(d->handle, this);

    else if (view == "database") d->presenter = new DatabasePresenter(this);
    else if (view == "map") d->presenter = new MapSettingsPresenter(this);
    else if (view == "video") d->presenter = new VideoSettingsPresenter(this);
    else if (view == "joystick") d->presenter = new JoystickSettingsPresenter(this);
    else if (view == "gui") d->presenter = new GuiSettingsPresenter(this);
    else if (view == "network") d->presenter = new NetworkSettingsPresenter(this);

    else if (view == "about") d->presenter = new AboutPresenter(this);
    else return;

    d->presenter->setView(this->view()->findChild<QObject*>(view));
}

