#include "abstract_migration.h"

// Qt
#include <QSqlError>
#include <QDebug>

using namespace data_source;

AbstractMigration::AbstractMigration()
{}

AbstractMigration::~AbstractMigration()
{}

QString AbstractMigration::errorSring() const
{
    return m_query.lastError().text();
}

bool AbstractMigration::up()
{
    if (!this->upImpl()) return false;

    if (!this->exec(QString("INSERT INTO schema_versions (version) VALUES (\'%1\');").arg(
                        this->version()))) return false;

    m_query.clear();
    return true;
}

bool AbstractMigration::down()
{
    if (!this->downImpl()) return false;

    if (this->exec(QString("DELETE FROM schema_versions WHERE version=\'%1\';").arg(
                       this->version()))) return false;

    m_query.clear();
    return true;
}

bool AbstractMigration::exec(const QString& sql)
{
    return (m_query.prepare(sql) && m_query.exec());
}

