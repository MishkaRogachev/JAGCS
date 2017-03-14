#include "mission_item.h"

// Qt
#include <QtGlobal>

using namespace data_source;

MissionItem::MissionItem(int id):
    m_id(id),
    m_sequence(-1),
    m_command(Command::UnknownCommand),
    m_altitude(0),
    m_altitudeRelative(false),
    m_latitude(0), // FIXME: use qQNaN values!
    m_longitude(0),
    m_radius(0),
    m_pitch(0),
    m_turns(0)
{}

int MissionItem::id() const
{
    return m_id;
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

int MissionItem::turns() const
{
    return m_turns;
}

void MissionItem::setTurns(int turns)
{
    m_turns = turns;
}

bool MissionItem::operator ==(const MissionItem& other) const
{
    return m_id == other.id() &&
            m_sequence == other.sequence() &&
            m_command == other.command() &&
            qFuzzyCompare(m_altitude, other.altitude()) ;//&&
//            m_altitudeRelative == other.isAltitudeRelative() &&
//            qFuzzyCompare(m_latitude, other.latitude()) &&
//            qFuzzyCompare(m_longitude, other.longitude()) &&
//            qFuzzyCompare(m_radius, other.radius()) &&
//            qFuzzyCompare(m_pitch, other.pitch()) &&
//            m_turns == other.turns();
}

