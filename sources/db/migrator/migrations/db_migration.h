#ifndef DB_MIGRATION_H
#define DB_MIGRATION_H

// Qt
#include <QSqlQuery>

namespace db
{
    class DbMigration
    {
    public:
        DbMigration();
        virtual ~DbMigration();

        QString errorSring() const;

        virtual bool up();
        virtual bool down();

    protected:
        QSqlQuery m_query;
    };
}

#endif // DB_MIGRATION_H
