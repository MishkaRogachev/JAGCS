#ifndef DB_MIGRATOR_H
#define DB_MIGRATOR_H

// Qt
#include <QObject>

// Internal
#include "i_db_provider.h"
#include "db_traits.h"

namespace data_source
{
    class DbMigrator: public QObject
    {
        Q_OBJECT

    public:
        DbMigrator(IDbProvider* provider, QObject* parent = nullptr);
        ~DbMigrator() override;

        QStringList versions() const;

    public slots:
        void checkMissing();
        void addMigrations(const DbMigrationPtrList& migrations);
        void removeMigrations(const DbMigrationPtrList& migrations, bool drop = false);
        void removeAll();
        void clarifyVersions();

    signals:
        void error(const QString& error);

    private slots:
        void commit(const QString& version);
        void rollback(const QString& version);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DB_MIGRATOR_H
