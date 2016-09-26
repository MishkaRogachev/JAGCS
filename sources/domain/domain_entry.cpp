#include "domain_entry.h"

// Internal
#include "settings_provider.h"

#include "vehicle_service.h"
#include "mavlink_communicator.h"
#include "link_manager.h"

using namespace domain;

class DomainEntry::Impl
{
public:
    SettingsProvider settings;
    VehicleService vehicleService;
    MavLinkCommunicator communicator;
    LinkManager manager;

    Impl():
        communicator(&vehicleService),
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
