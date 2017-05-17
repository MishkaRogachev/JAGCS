#include "db_migrator.h"

// Qt
#include <QDebug>

using namespace db;

DbMigrator::DbMigrator(DbMigrationFactory* factory, QObject* parent):
    QObject(parent),
    m_migrations(factory->create())
{}

DbMigrator::~DbMigrator()
{
    while (!m_migrations.isEmpty()) delete m_migrations.takeLast();
}

bool DbMigrator::migrate(const QDateTime& version)
{
    for (DbMigration* migration: m_migrations)
    {
        if (migration->version() < m_version) continue;
        if (migration->version() > version) return true;

        if (!migration->up())
        {
            emit error(tr("Migrate version: %1, error: %2").arg(
                           migration->version().toString(migration->format)).arg(
                           migration->errorSring()));
            return false;
        }

        m_version = migration->version();
        emit versionChanged(m_version);
    }

    return true;
}

bool DbMigrator::drop()
{
    MigrationList migrations = m_migrations;
    std::reverse(migrations.begin(), migrations.end());

    for (DbMigration* migration: migrations)
    {
        if (!migration->down())
        {
            emit error(tr("Drop migration version: %1, error: %2").arg(
                           migration->version().toString(migration->format)).arg(
                           migration->errorSring()));
            return false;
        }

        m_version = migration->version();
        emit versionChanged(m_version);
    }

    return true;
}
