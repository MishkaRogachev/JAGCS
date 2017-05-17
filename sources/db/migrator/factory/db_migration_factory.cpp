#include "db_migration_factory.h"

// Internal
#include "init_migration.h"

using namespace db;

MigrationList DbMigrationFactory::create()
{
    MigrationList list;

    list.append(new InitMigration());

    return list;
}
