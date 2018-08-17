#include "db_manager.h"

// Qt
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

// Internal
#include "db_migrator.h"
#include "core_db_plugin.h"

#include "notification_bus.h"

namespace
{
    const QString connectionType = "QSQLITE";
}

using namespace domain;

class DbManager::Impl
{
public:
    QSqlDatabase database;
    data_source::DbMigrator migrator;
    QList<IDbPlugin*> plugins;

    Impl():
        database(QSqlDatabase::contains() ? QSqlDatabase::database() :
                                      QSqlDatabase::addDatabase(::connectionType)),
        migrator(database)
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

const QSqlDatabase& DbManager::database() const
{
    return d->database;
}

bool DbManager::isOpen() const
{
    return d->database.isOpen();
}

bool DbManager::open(const QString& dbName)
{
    QFileInfo info(dbName);
    bool exists = info.exists();

    d->database.setDatabaseName(dbName);
    if (!d->database.open()) return false;

    if (exists) d->migrator.clarifyVersions();

    for (IDbPlugin* plugin: d->plugins)
    {
        d->migrator.addMigrations(plugin->migrations());
    }

    return true;
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
    d->database.close();
}

void DbManager::addPlugin(IDbPlugin* plugin)
{
    d->plugins.append(plugin);
    if (d->database.isOpen()) d->migrator.addMigrations(plugin->migrations());
}

void DbManager::removePlugin(IDbPlugin* plugin, bool dropMigrations)
{
    d->plugins.removeOne(plugin);
    if (d->database.isOpen()) d->migrator.removeMigrations(plugin->migrations(), dropMigrations);
}
