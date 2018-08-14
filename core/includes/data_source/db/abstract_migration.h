#ifndef ABSTRACT_MIGRATION_H
#define ABSTRACT_MIGRATION_H

// Qt
#include <QSqlQuery>

namespace data_source
{
    class AbstractMigration
    {
    public:
        AbstractMigration();
        virtual ~AbstractMigration();

        QString errorSring() const;

        bool up();
        bool down();

        virtual QString version() const = 0;

    protected:
        bool exec(const QString& sql);

        virtual bool upImpl() = 0;
        virtual bool downImpl() = 0;

        QSqlQuery m_query;
    };
}

#endif // ABSTRACT_MIGRATION_H
