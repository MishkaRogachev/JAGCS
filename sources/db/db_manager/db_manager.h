#ifndef DB_MANAGER_H
#define DB_MANAGER_H

// Qt
#include <QObject>
#include <QSqlDatabase>

class QSqlDatabase;

namespace db
{
    class DbMigrator;

    class DbManager: public QObject
    {
        Q_OBJECT

    public:
        explicit DbManager(QObject* parent = nullptr);
        ~DbManager() override;

        bool open(const QString& dbName);
        bool migrate();
        bool drop();

    private slots:
        void onDbError(const QString& error);

    private:
        QSqlDatabase m_db;
        DbMigrator* m_migrator;
    };
}

#endif // DB_MANAGER_H
