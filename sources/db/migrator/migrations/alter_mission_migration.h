#ifndef ALTER_MISSION_MIGRATION_H
#define ALTER_MISSION_MIGRATION_H

#include "db_migration.h"

namespace db
{
    class AlterMissionMigration: public DbMigration
    {
    public:
        bool up() override;
        bool down() override;

        QDateTime version() const override;
    };
}

#endif // ALTER_MISSION_MIGRATION_H
