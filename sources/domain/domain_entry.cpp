#include "domain_entry.h"

// Qt
#include <QGuiApplication>
#include <QDebug>

// Internal
#include "db_manager.h"
#include "db_facade.h"

#include "settings_provider.h"

#include "proxy_manager.h"

#include "vehicle_service.h"
#include "command_service.h"
#include "telemetry_service.h"

#include "communication_service.h"
#include "mavlink_communicator_factory.h"

using namespace db;
using namespace domain;

class DomainEntry::Impl
{
public:
    DbManager dataBase;
    DbFacade dbFacade;
    ProxyManager proxyManager;

    QScopedPointer<VehicleService> vehicleService;
    TelemetryService telemetryService;
    CommandService commandService;

    QScopedPointer<CommunicationService> commService;

    Impl():
        telemetryService(&dbFacade)
    {}
};

DomainEntry::DomainEntry():
    d(new Impl())
{
    if (!d->dataBase.open(SettingsProvider::value(settings::data_base::name).toString()))
    {
        qFatal("Unable to estblish DB connection");
        qApp->quit(); // TODO: quit gently
    }

    d->vehicleService.reset(new VehicleService(&d->dbFacade));

    comm::MavLinkCommunicatorFactory comFactory(
                &d->dbFacade,
                d->vehicleService.data(),
                &d->commandService,
                SettingsProvider::value(settings::communication::systemId).toInt(),
                SettingsProvider::value(settings::communication::componentId).toInt());

    d->commService.reset(new CommunicationService(&comFactory, &d->dbFacade));
}

DomainEntry::~DomainEntry()
{}

DbFacade* DomainEntry::dbFacade() const
{
    return &d->dbFacade;
}

CommunicationService* DomainEntry::commService() const
{
    return d->commService.data();
}

VehicleService* DomainEntry::vehicleService() const
{
    return d->vehicleService.data();
}

TelemetryService* DomainEntry::telemetryService() const
{
    return &d->telemetryService;
}

CommandService*DomainEntry::commandService() const
{
    return &d->commandService;
}

ProxyManager*DomainEntry::proxyManager() const
{
    return &d->proxyManager;
}
