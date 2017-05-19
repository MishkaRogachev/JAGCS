#ifndef DEFAULT_PARAMS_MIGRATION_H
#define DEFAULT_PARAMS_MIGRATION_H

#include "db_migration.h"

namespace db
{
    class DefaultParamsMigration: public DbMigration
    {
    public:
        bool up();
        bool down();

        QDateTime version() const override;
    };
}

#endif // DEFAULT_PARAMS_MIGRATION_H
