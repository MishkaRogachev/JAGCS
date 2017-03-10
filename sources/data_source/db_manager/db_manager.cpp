#include "db_manager.h"

using namespace data_source;

DbManager::DbManager(QObject* parent):
    QObject(parent),
    m_db(QSqlDatabase::addDatabase("QSQLITE"))
{}

bool DbManager::open(const QString& dbName)
{
    m_db.setDatabaseName(dbName);
    return m_db.open();
}
