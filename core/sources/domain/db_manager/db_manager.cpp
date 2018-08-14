#include "db_manager.h"

// Qt
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

// Internal
#include "db_migrator.h"
#include "core_db_plugin.h"

namespace
{
    const QString connectionType = "QSQLITE";
}

using namespace domain;

class DbManager::Impl
{
public:
    QSqlDatabase db;
    data_source::DbMigrator migrator;
    QList<IDbPlugin*> plugins;

    Impl():
        db(QSqlDatabase::contains() ? QSqlDatabase::database() :
                                      QSqlDatabase::addDatabase(::connectionType))
    {}
};

DbManager* DbManager::lastCreatedManager = nullptr;

DbManager::DbManager(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    DbManager::lastCreatedManager = this;

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

bool DbManager::isOpen() const
{
    return d->db.isOpen();
}

bool DbManager::open(const QString& dbName)
{
    d->db.setDatabaseName(dbName);
    if (!d->db.open()) return false;

    for (IDbPlugin* plugin: d->plugins)
    {
        qDebug() << "addPlugin" << plugin;
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
    d->db.close();
}

void DbManager::addPlugin(IDbPlugin* plugin)
{
    qDebug() << "addPlugin" << plugin;
    d->plugins.append(plugin);
    if (d->db.isOpen()) d->migrator.addMigrations(plugin->migrations());
}

void DbManager::removePlugin(IDbPlugin* plugin, bool dropMigrations)
{
    qDebug() << "removePlugin" << plugin;

    d->plugins.removeOne(plugin);
    if (d->db.isOpen()) d->migrator.removeMigrations(plugin->migrations(), dropMigrations);
}
