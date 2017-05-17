#ifndef DB_MIGRATION_FACTORY_H
#define DB_MIGRATION_FACTORY_H

// Qt
#include <QMap>
#include <QScopedPointer>
#include <QDateTime>

// Internal
#include "db_migration.h"

namespace db
{
    using MigrationMap = QMap<QDateTime, DbMigration* >;

    class DbMigrationFactory
    {
    public:
        MigrationMap create();
    };
}

#endif // DB_MIGRATION_FACTORY_H
