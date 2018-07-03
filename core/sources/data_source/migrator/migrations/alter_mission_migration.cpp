#include "alter_mission_migration.h"

// Qt
#include <QDebug>

using namespace db;

bool AlterMissionMigration::up()
{
    if (!m_query.prepare("DROP TABLE mission_items") || !m_query.exec()) return false;

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

    return DbMigration::up();
}

bool AlterMissionMigration::down()
{
    if (!m_query.prepare("DROP TABLE mission_items") || !m_query.exec()) return false;

    if (!m_query.prepare("CREATE TABLE mission_items ("
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
                         "FOREIGN KEY(missionId) REFERENCES missions(id))") ||
            !m_query.exec()) return false;

    return true;
}

QDateTime AlterMissionMigration::version() const
{
    return QDateTime::fromString("2017.08.01-14:46:42", format);
}
