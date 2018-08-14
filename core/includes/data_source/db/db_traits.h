#ifndef DB_TRAITS_H
#define DB_TRAITS_H

// Qt
#include <QSharedPointer>
#include <QList>

namespace data_source
{
    class AbstractMigration;

    using DbMigrationPtr = QSharedPointer<AbstractMigration>;
    using DbMigrationPtrList = QList<DbMigrationPtr>;
}

#endif // DB_TRAITS_H

