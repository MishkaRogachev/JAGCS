#ifndef DB_MANAGER_H
#define DB_MANAGER_H

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

        bool open(const QString& dbName);

    private:
        QSqlDatabase m_db;
    };
}

#endif // DB_MANAGER_H
