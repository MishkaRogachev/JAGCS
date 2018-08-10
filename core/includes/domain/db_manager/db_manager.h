#ifndef DB_MANAGER_H
#define DB_MANAGER_H

// Qt
#include <QObject>

// Internal
#include "i_db_plugin.h"

namespace domain
{
    class DbManager: public QObject
    {
        Q_OBJECT

    public:
        explicit DbManager(QObject* parent = nullptr);
        ~DbManager() override;

        static DbManager* instance();

        bool open(const QString& dbName);
        bool migrateLastVersion();
        bool drop();
        void clarify();
        void close();
        void clearLog();

        bool isOpen() const;
        QDateTime migrationVersion() const;

        QStringList dbLog() const;

        void addPlugin(IDbPlugin* plugin);
        void removePlugin(IDbPlugin* plugin);

    private slots:
        void onMigratorMessage(const QString& error);

    signals:
        void logChanged(const QStringList& log);

    private:
        class Impl;
        QScopedPointer<Impl> const d;

        static DbManager* lastCreatedManager;
    };
}

#define dbManager (domain::DbManager::instance())

#endif // DB_MANAGER_H
