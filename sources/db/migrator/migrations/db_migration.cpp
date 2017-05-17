#include "db_migration.h"

// Qt
#include <QSqlError>

using namespace db;

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
    return true;
}

bool DbMigration::down()
{
    return true;
}
