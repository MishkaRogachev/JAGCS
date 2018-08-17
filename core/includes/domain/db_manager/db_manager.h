#ifndef DB_MANAGER_H
#define DB_MANAGER_H

// Qt
#include <QObject>

// Internal
#include "i_db_plugin.h"

class QSqlDatabase;

namespace domain
{
    class DbManager: public QObject
    {
        Q_OBJECT

    public:
        explicit DbManager(QObject* parent = nullptr);
        ~DbManager() override;

        static DbManager* instance();

        const QSqlDatabase& database() const;

        bool isOpen() const;
        bool open(const QString& dbName);
        QStringList migrationVersions() const;

    public slots:
        void dropDatabase();
        void checkMissing();
        void clarifyVersions();
        void closeConnection();
        void addPlugin(IDbPlugin* plugin);
        void removePlugin(IDbPlugin* plugin, bool dropMigrations = false);

    private:
        class Impl;
        QScopedPointer<Impl> const d;

        static DbManager* lastCreatedManager;
    };
}

#define dbManager (domain::DbManager::instance())

#endif // DB_MANAGER_H
