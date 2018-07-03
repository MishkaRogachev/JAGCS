#ifndef ALTER_LINK_DESCRIPTION_MIGRATION_H
#define ALTER_LINK_DESCRIPTION_MIGRATION_H

#include "db_migration.h"

namespace db
{
    class AlterLinkDescriptionMigration: public DbMigration
    {
    public:
        bool up() override;
        bool down() override;

        QDateTime version() const override;
    };
}

#endif // ALTER_LINK_DESCRIPTION_MIGRATION_H
