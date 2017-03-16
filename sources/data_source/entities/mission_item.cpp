#include "mission_item.h"

// Qt
#include <QSqlQuery>
#include <QVariant>

using namespace data_source;

MissionItem::MissionItem(int id):
    BaseEntity(id),
    m_missionId(-1),
    m_sequence(-1),
    m_command(Command::UnknownCommand),
    m_altitude(qQNaN()),
    m_altitudeRelative(false),
    m_latitude(qQNaN()),
    m_longitude(qQNaN()),
    m_radius(qQNaN()),
    m_pitch(qQNaN()),
    m_periods(0)
{}

QString MissionItem::tableName()
{
    return "mission_items";
}

QString MissionItem::insertString()
{
    return "(mission_id, sequence, command, altitude, altitude_relative, "
            "latitude, longitude, radius, pitch, periods) "
           "VALUES (NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL)";
}

QString MissionItem::updateString()
{
    return "mission_id = :mission_id,"
           "sequence = :sequence,"
           "command = :command,"
           "altitude = :altitude,"
           "altitude_relative = :altitude_relative,"
           "latitude = :latitude,"
           "longitude = :longitude,"
           "radius = :radius,"
           "pitch = :pitch,"
           "periods = :periods ";
}

void MissionItem::bindQuery(QSqlQuery& query) const
{
    query.bindValue(":mission_id", m_missionId);
    query.bindValue(":sequence", m_sequence);
    query.bindValue(":command", int(m_command));
    query.bindValue(":altitude", m_altitude);
    query.bindValue(":altitude_relative", m_altitudeRelative);
    query.bindValue(":latitude", m_latitude);
    query.bindValue(":longitude", m_longitude);
    query.bindValue(":radius", m_radius);
    query.bindValue(":pitch", m_pitch);
    query.bindValue(":periods", m_periods);
}

void MissionItem::updateFromQuery(const QSqlQuery& query)
{
    m_missionId = query.value("mission_id").toInt();
    m_sequence = query.value("sequence").toInt();
    m_command = Command(query.value("command").toInt());
    m_altitude = query.value("altitude").toFloat();
    m_altitudeRelative = query.value("altitude_relative").toBool();
    m_latitude = query.value("latitude").toDouble();
    m_longitude = query.value("longitude").toDouble();
    m_radius = query.value("radius").toFloat();
    m_pitch = query.value("pitch").toFloat();
    m_periods = query.value("periods").toInt();

    this->setValid(true);
}

int MissionItem::missionId() const
{
    return m_missionId;
}

void MissionItem::setMissionId(int missionId)
{
    m_missionId = missionId;
}

int MissionItem::sequence() const
{
    return m_sequence;
}

void MissionItem::setSequence(int sequence)
{
    m_sequence = sequence;
}

Command MissionItem::command() const
{
    return m_command;
}

void MissionItem::setCommand(Command command)
{
    m_command = command;
}

float MissionItem::altitude() const
{
    return m_altitude;
}

void MissionItem::setAltitude(float altitude)
{
    m_altitude = altitude;
}

bool MissionItem::isAltitudeRelative() const
{
    return m_altitudeRelative;
}

void MissionItem::setAltitudeRelative(bool altitudeRelative)
{
    m_altitudeRelative = altitudeRelative;
}

double MissionItem::latitude() const
{
    return m_latitude;
}

void MissionItem::setLatitude(double latitude)
{
    m_latitude = latitude;
}

double MissionItem::longitude() const
{
    return m_longitude;
}

void MissionItem::setLongitude(double longitude)
{
    m_longitude = longitude;
}

float MissionItem::radius() const
{
    return m_radius;
}

void MissionItem::setRadius(float radius)
{
    m_radius = radius;
}

float MissionItem::pitch() const
{
    return m_pitch;
}

void MissionItem::setPitch(float pitch)
{
    m_pitch = pitch;
}

int MissionItem::periods() const
{
    return m_periods;
}

void MissionItem::setPeriods(int periods)
{
    m_periods = periods;
}


