#include "db_migrator.h"

// Qt
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

using namespace data_source;

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
        if (migration->version() <= m_version) continue;
        if (migration->version() > version) return true;

        if (!migration->up())
        {
            emit message(tr("Migrate error: version: %1, error: %2").arg(
                           migration->version().toString(migration->format)).arg(
                           migration->errorSring()));
            return false;
        } // TODO: rollback
        this->setVersion(migration->version());
    }

    emit message(tr("Migration version: %1").arg(m_version.toString(DbMigration::format)));
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
            emit message(tr("Drop migration error: version: %1, error: %2").arg(
                           migration->version().toString(migration->format)).arg(
                           migration->errorSring()));
            return false;
        } // TODO: rollback

        this->setVersion(migration->version());
    }

    return true;
}

bool DbMigrator::clarifyVersion()
{
    QSqlQuery query;
    if (query.exec("SELECT version FROM schema_versions ORDER BY version DESC LIMIT 1") &&
        query.next())
    {
        QString versionString = query.value("version").toString();
        if (versionString.isEmpty()) return false;
        QDateTime version = QDateTime::fromString(versionString, DbMigration::format);

        emit message(tr("Clarify version: ") + versionString);
        this->setVersion(version);
    }
    else
    {
        emit message(tr("Error: ") + query.lastError().text());
        return false;
    }
    return true;
}

void DbMigrator::reset()
{
    m_version = QDateTime();
    emit versionChanged(m_version);

    emit message(tr("Reset migrations"));
}

void DbMigrator::setVersion(const QDateTime& version)
{
    if (m_version.isNull())
    {
        emit message(tr("Establish migration %1").
                     arg(version.toString(DbMigration::format)));
    }
    else
    {
        emit message(tr("Migrate from %1 to %2").
                     arg(m_version.toString(DbMigration::format)).
                     arg(version.toString(DbMigration::format)));
    }

    m_version = version;
    emit versionChanged(version);
}

QDateTime DbMigrator::version() const
{
    return m_version;
}
