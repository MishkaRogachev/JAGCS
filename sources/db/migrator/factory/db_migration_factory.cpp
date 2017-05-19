#include "db_migration_factory.h"

// Internal
#include "init_migration.h"
#include "default_params_migration.h"

using namespace db;

MigrationList DbMigrationFactory::create()
{
    MigrationList list;

    list.append(new InitMigration());
    list.append(new DefaultParamsMigration());

    return list;
}
