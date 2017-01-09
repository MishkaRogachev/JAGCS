#include "domain_entry.h"

// Qt
#include <QScopedPointer>

// Internal
#include "settings_provider.h"

#include "vehicle_service.h"
#include "mission_service.h"

#include "mavlink_communicator.h"
#include "mavlink_communicator_factory.h"

#include "endpoint.h"

using namespace domain;

class DomainEntry::Impl
{
public:
    VehicleService vehicleService;
    MissionService missionService;

    QScopedPointer<MavLinkCommunicator> communicator;
};

DomainEntry::DomainEntry():
    d(new Impl())
{
    qRegisterMetaType<Endpoint>("Endpoint");
    qRegisterMetaType<EndpointList>("EndpointList");

    // TODO: temporary mission creation by vehicle id
    QObject::connect(&d->vehicleService, &VehicleService::vehicleAdded,
                     [this](uint8_t id) { d->missionService.missionForVehicle(id); });

    QObject::connect(&d->vehicleService, &VehicleService::vehicleAdded,
                     &d->missionService, &MissionService::commandDownloadMission);

    MavLinkCommunicatorFactory factory(&d->vehicleService, &d->missionService);
    d->communicator.reset(factory.create());
}

DomainEntry::~DomainEntry()
{
    delete d;
}

AbstractCommunicator* DomainEntry::communicator() const
{
    return d->communicator.data();
}

VehicleService* DomainEntry::vehicleService() const
{
    return &d->vehicleService;
}

MissionService*DomainEntry::missionService() const
{
    return &d->missionService;
}
