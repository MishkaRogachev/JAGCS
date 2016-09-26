#include "domain_entry.h"

// Internal
#include "settings_provider.h"

#include "mavlink_communicator.h"
#include "link_manager.h"

using namespace domain;

class DomainEntry::Impl
{
public:
    SettingsProvider settings;
    MavLinkCommunicator communicator;
    LinkManager manager;

    Impl():
        manager(&communicator)
    {}
};

DomainEntry::DomainEntry():
    d(new Impl())
{}

DomainEntry::~DomainEntry()
{
    delete d;
}

SettingsProvider* DomainEntry::settings() const
{
    return &d->settings;
}

LinkManager* DomainEntry::manager() const
{
    return &d->manager;
}
