#ifndef INIT_MIGRATION_H
#define INIT_MIGRATION_H

#include "abstract_migration.h"

namespace data_source
{
    class InitMigration: public AbstractMigration
    {
    public:
        bool upImpl() override;
        bool downImpl() override;

        QString version() const override;
    };
}

#endif // INIT_MIGRATION_H
