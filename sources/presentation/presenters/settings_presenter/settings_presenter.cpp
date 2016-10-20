#include "settings_presenter.h"

// Internal
#include "domain_entry.h"

#include "settings_provider.h"

#include "connection_settings_presenter.h"
#include "video_settings_presenter.h"
#include "network_settings_presenter.h"

using namespace presentation;

class SettingsPresenter::Impl
{
public:
    ConnectionSettingsPresenter* connections;
    VideoSettingsPresenter* video;
    NetworkSettingsPresenter* network;
};

SettingsPresenter::SettingsPresenter(domain::DomainEntry* entry, QObject* view):
    BasePresenter(view),
    d(new Impl())
{
    d->connections = new ConnectionSettingsPresenter(entry->communicator(),
                                                     this);
    d->video = new VideoSettingsPresenter(this);
    d->network = new NetworkSettingsPresenter(this);
}

SettingsPresenter::~SettingsPresenter()
{
    delete d;
}

void SettingsPresenter::connectView(QObject* view)
{
    d->connections->setView(view->findChild<QObject*>(NAME(connections)));
    d->video->setView(view->findChild<QObject*>(NAME(video)));
    d->network->setView(view->findChild<QObject*>(NAME(network)));

    connect(view, SIGNAL(makeDefaults()), this, SLOT(onMakeDefaults()));
}

void SettingsPresenter::onMakeDefaults()
{
    domain::SettingsProvider::makeDefaults();

    d->network->updateProxy();
}
