#include "domain_facade.h"

// Qt
#include <QFileInfo>
#include <QDebug>

// Internal
#include "db_manager.h"
#include "db_entry.h"

#include "settings_provider.h"

#include "proxy_manager.h"

#include "vehicle_service.h"
#include "mission_service.h"

#include "communication_service.h"
#include "mavlink_communicator_factory.h"

using namespace db;
using namespace domain;

class DomainFacade::Impl
{
public:
    DbManager dataBase;
    DbEntry dbEntry;
    ProxyManager proxyManager;

    QScopedPointer<VehicleService> vehicleService;
    QScopedPointer<MissionService> missionService;

    QScopedPointer<CommunicationService> commService;
};

DomainFacade::DomainFacade():
    d(new Impl())
{
    // TODO: replace by migrations
    QString dbName = SettingsProvider::value(settings::data_base::name).toString();
    QFileInfo file(dbName);
    bool exist = file.exists();

    d->dataBase.open(dbName);
    if (!exist) exist = d->dataBase.create();

    if (!exist)
    {
        qCritical() << "Error while creating DB" << dbName;
    }

    d->vehicleService.reset(new VehicleService(&d->dbEntry));
    d->missionService.reset(new MissionService(&d->dbEntry));

    comm::MavLinkCommunicatorFactory comFactory(d->vehicleService.data(),
             SettingsProvider::value(settings::communication::systemId).toInt(),
             SettingsProvider::value(settings::communication::componentId).toInt());

    d->commService.reset(new CommunicationService(&comFactory, &d->dbEntry));
}

DomainFacade::~DomainFacade()
{}

CommunicationService* DomainFacade::commService() const
{
    return d->commService.data();
}

VehicleService* DomainFacade::vehicleService() const
{
    return d->vehicleService.data();
}

MissionService* DomainFacade::missionService() const
{
    return d->missionService.data();
}

ProxyManager*DomainFacade::proxyManager() const
{
    return &d->proxyManager;
}
