#ifndef DB_MANAGER_H
#define DB_MANAGER_H

// Qt
#include <QObject>

// Internal
#include "i_db_plugin.h"
#include "i_db_provider.h"

namespace domain
{
    class DbManager: public QObject
    {
        Q_OBJECT

    public:
        DbManager(QObject* parent = nullptr);
        ~DbManager() override;

        static DbManager* instance();

        data_source::IDbProvider* provider() const;
        QStringList migrationVersions() const;

        bool open(const QString& dbName);

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
