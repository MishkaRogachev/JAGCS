#include "db_migrator.h"

// Qt
#include <QMap>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// Internal
#include "db_migration.h"

using namespace data_source;

class DbMigrator::Impl
{
public:
    QMap<QString, DbMigrationPtr> migrations;
    QStringList versions;
};

DbMigrator::DbMigrator(QObject* parent):
    QObject(parent),
    d(new Impl())
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

        DbMigrationPtr migration = d->migrations[version];
        if (migration->up()) continue;

        emit error(tr("Migration %1 up failed: %2").arg(version).arg(migration->errorSring()));
    }

    this->clarifyVersions();
}

void DbMigrator::addMigrations(const DbMigrationPtrList& migrations)
{
    for (const DbMigrationPtr& migration: migrations)
    {
        if (d->versions.contains(migration->version())) continue;

        qDebug() << "insert migration" << migration->version();
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

        qDebug() << "remove migration" << migration->version();
        if (drop)
        {
            qDebug() << "drop migration" << migration->version();
            if (!migration->down()) emit error(tr("Migration %1 down failed: %2").arg(
                                                   version).arg(migration->errorSring()));
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



