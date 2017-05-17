#include "db_migrator.h"

using namespace db;

DbMigrator::DbMigrator(DbMigrationFactory* factory, QObject* parent):
    QObject(parent),
    m_migrations(factory->create())
{}

DbMigrator::~DbMigrator()
{
    for (DbMigration* migration: m_migrations.values())
        delete migration;
}

bool DbMigrator::migrate(const QDateTime& time)
{
    for (const QDateTime& version: m_migrations.keys())
    {
        if (version < m_version) continue;
        if (version > time) return true;

        DbMigration* migration = m_migrations[version];
        if (!migration->up())
        {
            emit error(tr("Migrate version: %1, error: %2").
                       arg(version.toString("hh:mm:ss-dd.MM.yyyy").arg(migration->errorSring())));
            return false;
        }

        m_version = version;
        emit versionChanged(version);
    }

    return true;
}

bool DbMigrator::drop()
{
    QList<QDateTime> versions = m_migrations.keys();
    std::reverse(versions.begin(), versions.end());

    for (const QDateTime& version: versions)
    {
        DbMigration* migration = m_migrations[version];
        if (!migration->down())
        {
            emit error(tr("Drop migration version: %1, error: %2").
                       arg(version.toString("hh:mm:ss-dd.MM.yyyy")).arg(migration->errorSring()));
            return false;
        }

        m_version = version;
        emit versionChanged(version);
    }

    return true;
}
