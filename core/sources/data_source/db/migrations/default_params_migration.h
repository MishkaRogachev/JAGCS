#ifndef DEFAULT_PARAMS_MIGRATION_H
#define DEFAULT_PARAMS_MIGRATION_H

#include "db_migration.h"

namespace data_source
{
    class DefaultParamsMigration: public DbMigration
    {
    public:
        bool up() override;
        bool down() override;

        QString version() const override;
    };
}

#endif // DEFAULT_PARAMS_MIGRATION_H
