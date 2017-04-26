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
    QSqlQuery query;
    bool result = false;

    result = query.exec("PRAGMA FOREIGN_KEYS=ON;");
    if (!result)
    {
        qDebug() << query.lastError();
        return false;
    }

    result = query.exec("CREATE TABLE links ("
                        "id INTEGER PRIMARY KEY NOT NULL,"
                        "name STRING,"
                        "type SMALLINT,"
                        "port INTEGER,"
                        "device STRING,"
                        "baudRate INTEGER,"
                        "autoConnect BOOLEAN)");
    if (!result)
    {
        qDebug() << query.lastError();
        return false;
    }

    result = query.exec("CREATE TABLE vehicles ("
                        "id INTEGER PRIMARY KEY NOT NULL,"
                        "mavId INTEGER UNIQUE,"
                        "name STRING)");
    if (!result)
    {
        qDebug() << query.lastError();
        return false;
    }

    result = query.exec("CREATE TABLE missions ("
                        "id INTEGER PRIMARY KEY NOT NULL,"
                        "name STRING)");
    if (!result)
    {
        qDebug() << query.lastError();
        return false;
    }

    result = query.exec("CREATE TABLE mission_items ("
                        "id INTEGER PRIMARY KEY NOT NULL,"
                        "missionId INTEGER,"
                        "sequence INTEGER,"
                        "command SMALLINT,"
                        "altitude REAL,"
                        "altitudeRelative BOOLEAN,"
                        "latitude DOUBLE,"
                        "longitude DOUBLE,"
                        "radius REAL,"
                        "pitch REAL,"
                        "periods INTEGER,"
                        "FOREIGN KEY(missionId) REFERENCES missions(id))");

    if (!result)
    {
        qDebug() << query.lastError();
        return false;
    }

    result = query.exec("CREATE TABLE mission_assignments ("
                        "id INTEGER PRIMARY KEY NOT NULL,"
                        "missionId INTEGER,"
                        "vehicleId INTEGER,"
                        "status SMALLINT,"
                        "FOREIGN KEY(missionId) REFERENCES missions(id),"
                        "FOREIGN KEY(vehicleId) REFERENCES vehicles(id))");

    if (!result)
    {
        qDebug() << query.lastError();
        return false;
    }

    return true;
}

bool DbManager::drop()
{
    QSqlQuery query;

    query.prepare("DROP TABLE mission_items");

    if (!query.exec()) return false;

    query.prepare("DROP TABLE missions");

    if (!query.exec()) return false;

    query.prepare("DROP TABLE vehicles");

    if (!query.exec()) return false;

    query.prepare("DROP TABLE links");

    return query.exec();
}
