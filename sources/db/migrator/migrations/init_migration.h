#ifndef INIT_MIGRATION_H
#define INIT_MIGRATION_H

#include "db_migration.h"

namespace db
{
    class InitMigration: public DbMigration
    {
    public:
        bool up();
        bool down();

    };
}

#endif // INIT_MIGRATION_H
