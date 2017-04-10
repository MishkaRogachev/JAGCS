#include "domain_facade.h"

// Qt
#include <QFileInfo>
#include <QDebug>

// Internal
#include "db_manager.h"
#include "db_entry.h"

#include "settings_provider.h"

#include "communication_manager.h"
#include "mavlink_communicator_factory.h"

using namespace data_source;
using namespace domain;

class DomainFacade::Impl
{
public:
    DbManager dataBase;
    DbEntry dbEntry;
    QScopedPointer<CommunicationManager> manager;
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

    MavLinkCommunicatorFactory comFactory;
    d->manager.reset(new CommunicationManager(&comFactory, &d->dbEntry));
}

DomainFacade::~DomainFacade()
{}

CommunicationManager* DomainFacade::communicationManager() const
{
    return d->manager.data();
}
