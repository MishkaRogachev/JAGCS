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

        bool migrate(const QDateTime& version = QDateTime::currentDateTime());
        bool drop();
        bool readVersion();

        QDateTime version() const;

    signals:
        void versionChanged(QDateTime version);
        void error(const QString& error);

    private slots:
        void setVersion(const QDateTime& version);

    private:
        MigrationList m_migrations;
        QDateTime m_version;
    };
}

#endif // DB_MIGRATOR_H
