#include "db_migrator.h"

// Qt
#include <QMap>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// Internal
#include "abstract_migration.h"

using namespace data_source;

class DbMigrator::Impl
{
public:
    QMap<QString, DbMigrationPtr> migrations;
    QStringList versions;
    QSqlDatabase& db;

    Impl(QSqlDatabase& db):
        db(db)
    {}
};

DbMigrator::DbMigrator(IDbProvider* provider, QObject* parent):
    QObject(parent),
    d(new Impl(provider->database()))
{}

DbMigrator::~DbMigrator()
{}

QStringList DbMigrator::versions() const
{
    return d->versions;
}

void DbMigrator::checkMissing()
{
    for (const QString& version: d->migrations.keys())
    {
        if (d->versions.contains(version)) continue;

        d->db.transaction();

        DbMigrationPtr migration = d->migrations[version];
        if (migration->up(d->db))
        {
            this->commit(version);
            continue;
        }

        emit error(tr("Migration %1 up failed: %2").arg(version).arg(migration->errorSring()));
        this->rollback(version);
    }

    this->clarifyVersions();
}

void DbMigrator::addMigrations(const DbMigrationPtrList& migrations)
{
    for (const DbMigrationPtr& migration: migrations)
    {
        if (d->migrations.contains(migration->version())) continue;

        d->migrations.insert(migration->version(), migration);
    }

    this->checkMissing();
}

void DbMigrator::removeMigrations(const DbMigrationPtrList& migrations, bool drop)
{
    for (const DbMigrationPtr& migration: migrations)
    {
        QString version = d->migrations.key(migration);
        if (version.isEmpty()) continue;

        if (drop)
        {
            d->db.transaction();

            if (migration->down(d->db))
            {
                this->commit(version);
            }
            else
            {
                emit error(tr("Migration %1 down failed: %2").arg(
                                                   version).arg(migration->errorSring()));
                this->rollback(version);
            }
        }

        d->migrations.remove(version);
    }

    this->clarifyVersions();
}

void DbMigrator::removeAll()
{
    this->removeMigrations(d->migrations.values(), false);
}

void DbMigrator::clarifyVersions()
{
    d->versions.clear();

    QSqlQuery query;
    if (!query.exec("SELECT version FROM schema_versions ORDER BY version"))
    {
        emit error(tr("Error: ") + query.lastError().text());
        return;
    }

    while (query.next())
    {
        QString versionString = query.value("version").toString();
        if (versionString.isEmpty()) continue;

        d->versions.append(versionString);
    }
}

void DbMigrator::commit(const QString& version)
{
    if (d->db.commit()) return;

    emit error(tr("Commit %1 error").arg(version));
}

void DbMigrator::rollback(const QString& version)
{
    emit error(tr("Rollback %1 %2").arg(version).arg(d->db.rollback() ? tr("succeed") : tr("failed")));
}


