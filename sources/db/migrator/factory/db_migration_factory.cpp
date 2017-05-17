#include "db_migration_factory.h"

// Internal
#include "init_migration.h"

using namespace db;

MigrationMap DbMigrationFactory::create()
{
    MigrationMap map;

    map[QDateTime::fromString("14:37:15-17.05.2017", "hh:mm:ss-dd.MM.yyyy")] = new InitMigration();

    return map;
}
