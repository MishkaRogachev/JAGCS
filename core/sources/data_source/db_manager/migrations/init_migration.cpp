#include "init_migration.h"

// Qt
#include <QDebug>

using namespace data_source;

bool InitMigration::up()
{
    if (!m_query.prepare("PRAGMA FOREIGN_KEYS=ON;") || !m_query.exec()) return false;

    if (!m_query.prepare("CREATE TABLE schema_versions ("
                         "version STRING NOT NULL UNIQUE)") || !m_query.exec()) return false;

    if (!m_query.prepare("CREATE TABLE link_descriptions ("
                         "id INTEGER PRIMARY KEY NOT NULL,"
                         "name STRING,"
                         "type SMALLINT,"
                         "parameters TEXT,"
                         "protocolId INTEGER,"
                         "autoConnect BOOLEAN)") || !m_query.exec()) return false;

    if (!m_query.prepare("CREATE TABLE link_protocols ("
                         "id INTEGER PRIMARY KEY NOT NULL,"
                         "name STRING,"
                         "description STRING)") || !m_query.exec()) return false;

    if (!m_query.prepare("CREATE TABLE vehicles ("
                         "id INTEGER PRIMARY KEY NOT NULL,"
                         "mavId INTEGER UNIQUE,"
                         "name STRING,"
                         "type SMALLINT)") || !m_query.exec()) return false;

    if (!m_query.prepare("CREATE TABLE missions ("
                         "id INTEGER PRIMARY KEY NOT NULL,"
                         "name STRING,"
                         "count INTEGER)") || !m_query.exec()) return false;

    if (!m_query.prepare("CREATE TABLE mission_items ("
                         "id INTEGER PRIMARY KEY NOT NULL,"
                         "missionId INTEGER,"
                         "sequence INTEGER,"
                         "command SMALLINT,"
                         "altitude REAL,"
                         "altitudeRelative BOOLEAN,"
                         "latitude DOUBLE,"
                         "longitude DOUBLE,"
                         "parameters TEXT,"
                         "FOREIGN KEY(missionId) REFERENCES missions(id))") ||
        !m_query.exec()) return false;

    if (!m_query.prepare("CREATE TABLE mission_assignments ("
                         "id INTEGER PRIMARY KEY NOT NULL,"
                         "missionId INTEGER,"
                         "vehicleId INTEGER,"
                         "FOREIGN KEY(missionId) REFERENCES missions(id),"
                         "FOREIGN KEY(vehicleId) REFERENCES vehicles(id))") ||
        !m_query.exec()) return false;

    if (!m_query.prepare("CREATE TABLE video_sources ("
                         "id INTEGER PRIMARY KEY NOT NULL,"
                         "type SMALLINT,"
                         "source STRING)") ||
        !m_query.exec()) return false;

    return DbMigration::up();
}

bool InitMigration::down()
{
    if (!m_query.prepare("DROP TABLE video_sources") || !m_query.exec()) return false;
    if (!m_query.prepare("DROP TABLE mission_assignments") || !m_query.exec()) return false;
    if (!m_query.prepare("DROP TABLE mission_items") || !m_query.exec()) return false;
    if (!m_query.prepare("DROP TABLE missions") || !m_query.exec()) return false;
    if (!m_query.prepare("DROP TABLE vehicles") || !m_query.exec()) return false;
    if (!m_query.prepare("DROP TABLE link_protocols") || !m_query.exec()) return false;
    if (!m_query.prepare("DROP TABLE link_descriptions") || !m_query.exec()) return false;
    if (!m_query.prepare("DROP TABLE schema_versions") || !m_query.exec()) return false;

    return true;
}

QDateTime InitMigration::version() const
{
    return QDateTime::fromString("2018.08.07-09:37:45", format);
}
