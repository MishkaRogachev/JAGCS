#include "db_migrator.h"

// Qt
#include <QSqlQuery>
#include <QSqlError>
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

        this->setVersion(migration->version());
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

        this->setVersion(migration->version());
    }

    return true;
}

bool DbMigrator::readVersion()
{
    QSqlQuery query;
    if (query.exec("SELECT version FROM schema_versions LIMIT 1") && query.next())
    {
        QString versionString = query.value("version").toString();
        if (versionString.isEmpty()) return false;
        QDateTime version = QDateTime::fromString(versionString, DbMigration::format);
        this->setVersion(version);
    }
    else
    {
        emit error(query.lastError().text());
        return false;
    }
    return true;
}

void DbMigrator::setVersion(const QDateTime& version)
{
    m_version = version;
    emit versionChanged(version);
}
