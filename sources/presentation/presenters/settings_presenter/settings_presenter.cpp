#include "settings_presenter.h"

// Internal
#include "domain_entry.h"

#include "settings_provider.h"

#include "gui_settings_presenter.h"
#include "manual_settings_presenter.h"
#include "connection_settings_presenter.h"
#include "video_settings_presenter.h"
#include "network_settings_presenter.h"

using namespace presentation;

class SettingsPresenter::Impl
{
public:
    GuiSettingsPresenter* gui;
    ManualSettingsPresenter* manual;
    ConnectionSettingsPresenter* connections;
    VideoSettingsPresenter* video;
    NetworkSettingsPresenter* network;
};

SettingsPresenter::SettingsPresenter(domain::DomainEntry* entry, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->gui = new GuiSettingsPresenter(this);
    d->manual = new ManualSettingsPresenter(this);
    d->connections = new ConnectionSettingsPresenter(entry->communicator(), this);
    d->video = new VideoSettingsPresenter(this);
    d->network = new NetworkSettingsPresenter(entry->proxyManager(), this);
}

SettingsPresenter::~SettingsPresenter()
{
    delete d;
}

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
    d->manual->setView(view->findChild<QObject*>(NAME(manual)));
    d->connections->setView(view->findChild<QObject*>(NAME(connections)));
    d->video->setView(view->findChild<QObject*>(NAME(video)));
    d->network->setView(view->findChild<QObject*>(NAME(network)));

    connect(view, SIGNAL(makeDefaults()), this, SLOT(onMakeDefaults()));
}

void SettingsPresenter::onMakeDefaults()
{
    domain::SettingsProvider::makeDefaults();
}
