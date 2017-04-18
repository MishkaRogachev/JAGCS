#include "settings_presenter.h"

// Internal
#include "domain_facade.h"

#include "settings_provider.h"

#include "gui_settings_presenter.h"
#include "communications_presenter.h"
//#include "video_settings_presenter.h"
//#include "network_settings_presenter.h"
#include "about_presenter.h"

using namespace presentation;

class SettingsPresenter::Impl
{
public:
    GuiSettingsPresenter* gui;
    CommunicationsPresenter* communications;
//    VideoSettingsPresenter* video;
//    NetworkSettingsPresenter* network;
    AboutPresenter* about;
};

SettingsPresenter::SettingsPresenter(domain::DomainFacade* facade, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->gui = new GuiSettingsPresenter(this);
    d->communications = new CommunicationsPresenter(
                            facade->communicationManager(),
                            this);
//    d->video = new VideoSettingsPresenter(this);
//    d->network = new NetworkSettingsPresenter(entry->proxyManager(), this);
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
    // TODO: check unsaved changes
    this->setViewProperty(PROPERTY(visible), false);
}

void SettingsPresenter::connectView(QObject* view)
{
    d->gui->setView(view->findChild<QObject*>(NAME(gui)));
    d->communications->setView(view->findChild<QObject*>(NAME(communications)));
//    d->video->setView(view->findChild<QObject*>(NAME(video)));
//    d->network->setView(view->findChild<QObject*>(NAME(network)));
    d->about->setView(view->findChild<QObject*>(NAME(about)));

    connect(view, SIGNAL(makeDefaults()), this, SLOT(onMakeDefaults()));
}

void SettingsPresenter::onMakeDefaults()
{
    domain::SettingsProvider::makeDefaults();
}
