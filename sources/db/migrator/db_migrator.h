#ifndef DB_MIGRATOR_H
#define DB_MIGRATOR_H

// Qt
#include <QObject>

// Internal
#include "db_migration_factory.h"

namespace db
{
    class DbMigrator: public QObject
    {
        Q_OBJECT

    public:
        explicit DbMigrator(DbMigrationFactory* factory, QObject* parent = nullptr);
        ~DbMigrator() override;

        bool migrate(const QDateTime& time = QDateTime::currentDateTime());
        bool drop();

    signals:
        void versionChanged(QDateTime current);
        void error(const QString& error);

    private:
        MigrationMap m_migrations;
        QDateTime m_version;
    };
}

#endif // DB_MIGRATOR_H
