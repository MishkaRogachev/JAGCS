#include "db_manager.h"

// Qt
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

// Internal
#include "db_migrator.h"
#include "core_db_plugin.h"
#include "sqlite_provider.h"

#include "notification_bus.h"

using namespace domain;

class DbManager::Impl
{
public:
    data_source::SqliteProvider provider;
    data_source::DbMigrator migrator;
    QList<IDbPlugin*> plugins;

    Impl():
        migrator(&provider)
    {}
};

DbManager* DbManager::lastCreatedManager = nullptr;

DbManager::DbManager(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    DbManager::lastCreatedManager = this;

    connect(&d->migrator, &data_source::DbMigrator::error, [=](const QString& error) {
        notificationBus->notify(tr("DB"), error, dto::Notification::Critical);
    });

    this->addPlugin(new CoreDbPlugin(this));
}

DbManager::~DbManager()
{
    if (DbManager::lastCreatedManager == this)
    {
        DbManager::lastCreatedManager = nullptr;
    }
}

DbManager* DbManager::instance()
{
    return DbManager::lastCreatedManager;
}

data_source::IDbProvider* DbManager::provider() const
{
    return &d->provider;
}

void DbManager::dropDatabase()
{
    d->migrator.removeAll();

    this->closeConnection();
}

QStringList DbManager::migrationVersions() const
{
    return d->migrator.versions();
}

bool DbManager::open(const QString& dbName)
{
    d->provider.setName(dbName);

    bool exists = false;
    if (!d->provider.open(exists)) return false;

    if (exists) d->migrator.clarifyVersions();

    for (IDbPlugin* plugin: d->plugins)
    {
        d->migrator.addMigrations(plugin->migrations());
    }

    return true;
}

void DbManager::checkMissing()
{
    return d->migrator.checkMissing();
}

void DbManager::clarifyVersions()
{
    d->migrator.clarifyVersions();
}

void DbManager::closeConnection()
{
    d->provider.database().close();
}

void DbManager::addPlugin(IDbPlugin* plugin)
{
    d->plugins.append(plugin);
    if (d->provider.database().isOpen())
    {
        d->migrator.addMigrations(plugin->migrations());
    }
}

void DbManager::removePlugin(IDbPlugin* plugin, bool dropMigrations)
{
    d->plugins.removeOne(plugin);
    if (d->provider.database().isOpen())
    {
        d->migrator.removeMigrations(plugin->migrations(), dropMigrations);
    }
}
