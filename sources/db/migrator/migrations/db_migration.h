#ifndef DB_MIGRATION_H
#define DB_MIGRATION_H

// Qt
#include <QSqlQuery>
#include <QDateTime>

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

        virtual QDateTime version() const = 0;
        static const QString format;

    protected:
        QSqlQuery m_query;
    };
}

#endif // DB_MIGRATION_H
