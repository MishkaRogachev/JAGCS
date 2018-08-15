#ifndef ABSTRACT_MIGRATION_H
#define ABSTRACT_MIGRATION_H

// Qt
#include <QScopedPointer>
#include <QString>

class QSqlDatabase;
class QSqlQuery;

namespace data_source
{
    class AbstractMigration
    {
    public:
        AbstractMigration();
        virtual ~AbstractMigration();

        QString errorSring() const;

        bool up(const QSqlDatabase& db);
        bool down(const QSqlDatabase& db);

        virtual QString version() const = 0;

    protected:
        bool exec(const QString& sql);

        virtual bool upImpl() = 0;
        virtual bool downImpl() = 0;

    private:
        QScopedPointer<QSqlQuery> m_query;
    };
}

#endif // ABSTRACT_MIGRATION_H
