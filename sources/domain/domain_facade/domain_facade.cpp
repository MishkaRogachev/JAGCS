#include "domain_facade.h"

// Qt
#include <QFileInfo>

// Internal
#include "db_manager.h"
#include "identity_map.h"

#include "settings_provider.h"

using namespace data_source;
using namespace domain;

class DomainFacade::Impl
{
public:
    DbManager dataBase;
    IdentityMap iMap;
};

DomainFacade::DomainFacade():
    d(new Impl())
{
    // TODO: replace by migrations

    QString dbName = SettingsProvider::value(settings::data_base::name);
    QFileInfo file(dbName);
    bool exist = file.exists();

    d->dataBase.open(dbName);
    if (!exist) d->dataBase.create();
}

DomainFacade::~DomainFacade()
{}
