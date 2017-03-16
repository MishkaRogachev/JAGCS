#include "db_manager.h"

// Qt
#include <QSqlQuery>

using namespace data_source;

DbManager::DbManager(QObject* parent):
    QObject(parent),
    m_db(QSqlDatabase::addDatabase("QSQLITE"))
{}

DbManager::~DbManager()
{
    m_db.close();
}

bool DbManager::open(const QString& dbName)
{
    m_db.setDatabaseName(dbName);
    return m_db.open();
}


bool DbManager::create()
{
    QSqlQuery query;
    query.prepare("CREATE TABLE mission_items ("
                     "id INTEGER PRIMARY KEY NOT NULL,"
                     "mission_id INTEGER,"
                     "sequence INTEGER,"
                     "command INTEGER,"
                     "altitude REAL,"
                     "altitude_relative BOOLEAN,"
                     "latitude DOUBLE,"
                     "longitude DOUBLE,"
                     "radius REAL,"
                     "pitch REAL,"
                     "periods INTEGER)");

    return query.exec();
}

bool DbManager::drop()
{
    QSqlQuery query;
    query.prepare("DROP TABLE mission_items");
    return query.exec();
}
