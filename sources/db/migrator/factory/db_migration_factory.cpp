#include "db_migration_factory.h"

// Internal
#include "init_migration.h"
#include "default_params_migration.h"
#include "alter_mission_migration.h"

using namespace db;

MigrationList DbMigrationFactory::create()
{
    MigrationList list;

    list.append(new InitMigration());
    list.append(new DefaultParamsMigration());
    list.append(new AlterMissionMigration());

    return list;
}
