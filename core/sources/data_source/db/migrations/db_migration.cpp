#include "db_migration.h"

// Qt
#include <QSqlError>
#include <QDebug>

using namespace data_source;

const QString DbMigration::format = "yyyy.MM.dd-hh:mm:ss";

DbMigration::DbMigration()
{}

DbMigration::~DbMigration()
{}

QString DbMigration::errorSring() const
{
    return m_query.lastError().text();
}

bool DbMigration::up()
{
    if (!m_query.prepare("INSERT INTO schema_versions (version) "
                         "VALUES (\"" + this->version().toString(format) + "\");") ||
        !m_query.exec()) return false;

    return true;
}

bool DbMigration::down()
{
    return true;
}
