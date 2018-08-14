#ifndef DB_MIGRATION_H
#define DB_MIGRATION_H

// Qt
#include <QSqlQuery>

namespace data_source
{
    class DbMigration
    {
    public:
        DbMigration();
        virtual ~DbMigration();

        QString errorSring() const;

        virtual bool up();
        virtual bool down();

        virtual QString version() const = 0;

    protected:
        QSqlQuery m_query;
    };
}

#endif // DB_MIGRATION_H
