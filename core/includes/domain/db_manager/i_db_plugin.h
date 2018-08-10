#ifndef I_DB_PLUIGN_H
#define I_DB_PLUIGN_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

namespace domain
{
    class IDbPlugin
    {
    public:
        virtual QList<data_source::DbMigrationPtr> migrations() const = 0;
    };
}

Q_DECLARE_INTERFACE(domain::IDbPlugin, "domain.IDbPlugin")

#endif // I_DB_PLUIGN_H
