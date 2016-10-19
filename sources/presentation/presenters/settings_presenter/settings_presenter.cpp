#include "settings_presenter.h"

// Internal
#include "domain_entry.h"

#include "connection_settings_presenter.h"
#include "video_settings_presenter.h"
#include "network_settings_presenter.h"

using namespace presentation;

class SettingsPresenter::Impl
{
public:
    domain::DomainEntry* entry;
};

SettingsPresenter::SettingsPresenter(domain::DomainEntry* entry, QObject* view):
    BasePresenter(view),
    d(new Impl())
{
    d->entry = entry;
}

SettingsPresenter::~SettingsPresenter()
{
    delete d;
}

QObject* SettingsPresenter::createConnectionSettings(QObject* view)
{
    auto presenter = new ConnectionSettingsPresenter(d->entry->communicator(),
                                                     this);
    presenter->setView(view);
    return presenter;
}

QObject* SettingsPresenter::createVideoSettings(QObject* view)
{
    return new VideoSettingsPresenter(view);
}

QObject* SettingsPresenter::createNetworkSettings(QObject* view)
{
    return new NetworkSettingsPresenter(view);
}
