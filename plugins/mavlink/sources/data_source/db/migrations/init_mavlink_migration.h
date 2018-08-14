#ifndef DEFAULT_PARAMS_MIGRATION_H
#define DEFAULT_PARAMS_MIGRATION_H

#include "abstract_migration.h"

namespace data_source
{
    class InitMavlinkMigration: public AbstractMigration
    {
    public:
        bool upImpl() override;
        bool downImpl() override;

        QString version() const override;
    };
}

#endif // DEFAULT_PARAMS_MIGRATION_H
