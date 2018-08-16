#include "init_migration.h"

// Qt
#include <QDebug>

using namespace data_source;

bool InitMigration::upImpl()
{
    if (!this->exec("PRAGMA FOREIGN_KEYS=ON;")) return false;

    if (!this->exec("CREATE TABLE schema_versions ("
                    "version STRING NOT NULL UNIQUE)")) return false;

    if (!this->exec("CREATE TABLE link_descriptions ("
                    "id INTEGER PRIMARY KEY NOT NULL,"
                    "name STRING,"
                    "type SMALLINT,"
                    "protocol STRING,"
                    "parameters TEXT,"
                    "protocolId INTEGER,"
                    "autoConnect BOOLEAN)")) return false;

    if (!this->exec("CREATE TABLE vehicles ("
                    "id INTEGER PRIMARY KEY NOT NULL,"
                    "mavId INTEGER UNIQUE,"
                    "name STRING,"
                    "type SMALLINT)")) return false;

    if (!this->exec("CREATE TABLE missions ("
                    "id INTEGER PRIMARY KEY NOT NULL,"
                    "name STRING,"
                    "count INTEGER)")) return false;

    if (!this->exec("CREATE TABLE mission_items ("
                    "id INTEGER PRIMARY KEY NOT NULL,"
                    "missionId INTEGER,"
                    "sequence INTEGER,"
                    "command SMALLINT,"
                    "altitude REAL,"
                    "altitudeRelative BOOLEAN,"
                    "latitude DOUBLE,"
                    "longitude DOUBLE,"
                    "parameters TEXT,"
                    "FOREIGN KEY(missionId) REFERENCES missions(id))")) return false;

    if (!this->exec("CREATE TABLE mission_assignments ("
                    "id INTEGER PRIMARY KEY NOT NULL,"
                    "missionId INTEGER,"
                    "vehicleId INTEGER,"
                    "FOREIGN KEY(missionId) REFERENCES missions(id),"
                    "FOREIGN KEY(vehicleId) REFERENCES vehicles(id))")) return false;

    if (!this->exec("CREATE TABLE video_sources ("
                    "id INTEGER PRIMARY KEY NOT NULL,"
                    "type SMALLINT,"
                    "source STRING)")) return false;

    return true;
}

bool InitMigration::downImpl()
{
    if (!this->exec("DROP TABLE video_sources")) return false;
    if (!this->exec("DROP TABLE mission_assignments")) return false;
    if (!this->exec("DROP TABLE mission_items")) return false;
    if (!this->exec("DROP TABLE missions")) return false;
    if (!this->exec("DROP TABLE vehicles")) return false;
    if (!this->exec("DROP TABLE link_descriptions")) return false;
    if (!this->exec("DROP TABLE schema_versions")) return false;

    return true;
}

QString InitMigration::version() const
{
    return "core_2018.08.07-09:37_init";
}
