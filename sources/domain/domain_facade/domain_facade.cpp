#include "domain_facade.h"

// Qt
#include <QFileInfo>
#include <QDebug>

// Internal
#include "db_manager.h"
#include "db_entry.h"

#include "settings_provider.h"

#include "proxy_manager.h"

#include "communication_manager.h"
#include "mavlink_communicator_factory.h"

#include "vehicle_service.h"

using namespace data_source;
using namespace domain;

class DomainFacade::Impl
{
public:
    DbManager dataBase;
    DbEntry dbEntry;
    ProxyManager proxyManager;

    QScopedPointer<CommunicationManager> communicationManager;
    QScopedPointer<VehicleService> vehicleService;
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

    MavLinkCommunicatorFactory comFactory(d->vehicleService.data());
    d->communicationManager.reset(new CommunicationManager(&comFactory,
                                                           &d->dbEntry));
}

DomainFacade::~DomainFacade()
{}

CommunicationManager* DomainFacade::communicationManager() const
{
    return d->communicationManager.data();
}

VehicleService* DomainFacade::vehicleService() const
{
    return d->vehicleService.data();
}

ProxyManager*DomainFacade::proxyManager() const
{
    return &d->proxyManager;
}
