#ifndef DB_MANAGER_H
#define DB_MANAGER_H

// Qt
#include <QObject>
#include <QSqlDatabase>

class QSqlDatabase;

namespace data_source
{
    class DbMigrator;

    class DbManager: public QObject
    {
        Q_OBJECT

    public:
        explicit DbManager(QObject* parent = nullptr);
        ~DbManager() override;

        bool open(const QString& dbName);
        bool migrateLastVersion();
        bool drop();
        void clarify();
        void close();
        void clearLog();

        bool isOpen() const;
        QDateTime migrationVersion() const;

        QStringList dbLog() const;

    private slots:
        void onMigratorMessage(const QString& error);

    signals:
        void logChanged(const QStringList& log);

    private:
        QSqlDatabase m_db;
        DbMigrator* m_migrator;
        QStringList m_dbLog;
    };
}

#endif // DB_MANAGER_H
