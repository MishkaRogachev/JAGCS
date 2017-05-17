#include "db_manager.h"

// Qt
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

using namespace db;

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

}

bool DbManager::drop()
{

}
