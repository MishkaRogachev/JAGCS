#ifndef SQLITE_PROVIDER_H
#define SQLITE_PROVIDER_H

// Qt
#include <QSqlDatabase>

// Internal
#include "i_db_provider.h"

namespace data_source
{
    class SqliteProvider: public IDbProvider
    {
    public:
        SqliteProvider();
        ~SqliteProvider() override;

        QSqlDatabase& database() override;
        bool open(bool& exists) override;

        void setName(const QString& dbName);
        QString dbName() const;

    private:
        QSqlDatabase m_database;
    };
}

#endif // SQLITE_PROVIDER_H
