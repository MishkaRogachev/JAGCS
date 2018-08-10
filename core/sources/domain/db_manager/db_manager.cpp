#include "db_manager.h"

// Qt
#include <QFileInfo>
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
    QStringList dbLog;

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

    connect(&d->migrator, &data_source::DbMigrator::message, this, &DbManager::onMigratorMessage);

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

bool DbManager::open(const QString& dbName)
{
    QFileInfo file(dbName);
    bool exist = file.exists();

    d->db.setDatabaseName(dbName);
    bool ok = d->db.open();

    if (ok && exist)
    {
        ok = d->migrator.clarifyVersion();
    }

    if (!ok)
    {
        this->onMigratorMessage(d->db.lastError().text());
        return false;
    }

    return d->migrator.migrate();
}

bool DbManager::migrateLastVersion()
{
    return d->migrator.migrate();
}

bool DbManager::drop()
{
    this->close();
    return d->migrator.drop();
}

void DbManager::clarify()
{
    d->migrator.clarifyVersion();
}

void DbManager::close()
{
    d->migrator.reset();
    d->db.close();
}

void DbManager::clearLog()
{
    d->dbLog.clear();
    emit logChanged(d->dbLog);
}

bool DbManager::isOpen() const
{
    return d->db.isOpen();
}

QDateTime DbManager::migrationVersion() const
{
    return d->migrator.version();
}

void DbManager::onMigratorMessage(const QString& error)
{
    qDebug() << "DB:" << error;
    d->dbLog << error;
    emit logChanged(d->dbLog);
}

QStringList DbManager::dbLog() const
{
    return d->dbLog;
}

void DbManager::addPlugin(IDbPlugin* plugin)
{
    d->migrator.migrate(plugin->migrations());
}

void DbManager::removePlugin(IDbPlugin* plugin)
{
    d->migrator.drop(plugin->migrations());
}
