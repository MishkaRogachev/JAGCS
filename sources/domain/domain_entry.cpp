#include "domain_entry.h"

// Internal
#include "settings_provider.h"

#include "vehicle_service.h"
#include "mavlink_communicator.h"

using namespace domain;

class DomainEntry::Impl
{
public:
    SettingsProvider settings;
    VehicleService vehicleService;
    MavLinkCommunicator communicator;

    Impl():
        communicator(&settings, &vehicleService)
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

AbstractCommunicator* DomainEntry::communicator() const
{
    return &d->communicator;
}

VehicleService* DomainEntry::vehicleService() const
{
    return &d->vehicleService;
}
