#ifndef DB_MIGRATOR_H
#define DB_MIGRATOR_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

class QSqlDatabase;

namespace data_source
{
    class DbMigrator: public QObject
    {
        Q_OBJECT

    public:
        DbMigrator(QSqlDatabase& db, QObject* parent = nullptr);
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

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DB_MIGRATOR_H
