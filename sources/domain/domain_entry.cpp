#include "domain_entry.h"

// Qt
#include <QGuiApplication>
#include <QDebug>

// Internal
#include "db_manager.h"
#include "db_facade.h"

#include "settings_provider.h"

#include "proxy_manager.h"

#include "command_service.h"
#include "telemetry_service.h"
#include "vehicle_service.h"
#include "mission_service.h"

#include "communication_service.h"
#include "mavlink_communicator_factory.h"

using namespace db;
using namespace domain;

class DomainEntry::Impl
{
public:
    DbManager dbManager;
    DbFacade dbFacade;
    ProxyManager proxyManager;

    VehicleService vehicleService;
    MissionService missionService;
    TelemetryService telemetryService;
    CommandService commandService;

    QScopedPointer<CommunicationService> commService;

    Impl():
        telemetryService(&vehicleService)
    {}
};

DomainEntry::DomainEntry():
    d(new Impl())
{
    if (!d->dbManager.open(settings::Provider::value(settings::data_base::name).toString()))
    {
        qFatal("Unable to estblish DB connection");
        qApp->quit(); // TODO: quit gently
    }

    comm::MavLinkCommunicatorFactory comFactory(this,
                settings::Provider::value(settings::communication::systemId).toInt(),
                settings::Provider::value(settings::communication::componentId).toInt());

    d->commService.reset(new CommunicationService(&comFactory, &d->dbFacade));
}

DomainEntry::~DomainEntry()
{}

DbFacade* DomainEntry::dbFacade() const
{
    return &d->dbFacade;
}

DbManager*DomainEntry::dbManager() const
{
    return &d->dbManager;
}

CommunicationService* DomainEntry::commService() const
{
    return d->commService.data();
}

TelemetryService* DomainEntry::telemetryService() const
{
    return &d->telemetryService;
}

VehicleService* DomainEntry::vehicleService() const
{
    return &d->vehicleService;
}

MissionService* DomainEntry::missionService() const
{
    return &d->missionService;
}

CommandService*DomainEntry::commandService() const
{
    return &d->commandService;
}

ProxyManager*DomainEntry::proxyManager() const
{
    return &d->proxyManager;
}
