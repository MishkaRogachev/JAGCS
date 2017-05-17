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
        explicit DbMigrator(QObject* parent = nullptr);

    public slots:
        void create();
        void drop();
        void migrate(const QDateTime& time = QDateTime::currentDateTime());

    signals:
        void currentChanged(QDateTime current);
        void error(const QString& error);

    private:
        MigrationMap m_migrations;
        QDateTime m_current;
    };
}

#endif // DB_MIGRATOR_H
