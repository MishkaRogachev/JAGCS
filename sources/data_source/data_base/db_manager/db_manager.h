#ifndef DB_MANAGER_H
#define DB_MANAGER_H

// Qt
#include <QObject>
#include <QSqlDatabase>

class QSqlDatabase;

namespace data_source
{
    class DbManager: public QObject
    {
        Q_OBJECT

    public:
        explicit DbManager(QObject* parent = nullptr);
        ~DbManager() override;

        bool open(const QString& dbName);

        bool create();
        bool drop();

    private:
        QSqlDatabase m_db;
    };
}

#endif // DB_MANAGER_H
