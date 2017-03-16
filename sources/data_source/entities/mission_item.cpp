#include "mission_item.h"

// Qt
#include <QtGlobal>

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


