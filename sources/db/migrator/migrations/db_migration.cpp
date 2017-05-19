#include "db_migration.h"

// Qt
#include <QSqlError>

using namespace db;

const QString DbMigration::format = "hh:mm:ss-dd.MM.yyyy";

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
