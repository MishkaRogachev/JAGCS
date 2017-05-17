#ifndef DB_MIGRATION_FACTORY_H
#define DB_MIGRATION_FACTORY_H

// Qt
#include <QScopedPointer>

// Internal
#include "db_migration.h"

namespace db
{
    using MigrationList = QList<DbMigration*>;

    class DbMigrationFactory
    {
    public:
        MigrationList create();
    };
}

#endif // DB_MIGRATION_FACTORY_H
