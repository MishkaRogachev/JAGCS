#include "mission_item.h"

// Qt
#include <QMetaEnum>
#include <QMap>
#include <QDebug>

// Internal
#include "mission.h"

using namespace dao;

namespace
{
    static QMap <MissionItem::Command, QList<MissionItem::Parameter> > commandParameters =
    {
        { MissionItem::Takeoff, { MissionItem::Pitch } },
        { MissionItem::Landing, { MissionItem::AbortAltitude, MissionItem::Yaw } },
        { MissionItem::Waypoint, { MissionItem::Radius } },
        { MissionItem::LoiterUnlim, {  MissionItem::Radius, MissionItem::Clockwise, MissionItem::Yaw } },
        { MissionItem::LoiterTime, { MissionItem::Radius, MissionItem::Clockwise, MissionItem::Yaw, MissionItem::Time } },
        { MissionItem::LoiterTurns, { MissionItem::Radius, MissionItem::Clockwise, MissionItem::Yaw, MissionItem::Repeats } },
        { MissionItem::LoiterAltitude, { MissionItem::Radius, MissionItem::Clockwise, MissionItem::HeadingRequired } },
        { MissionItem::SetSpeed, { MissionItem::Speed, MissionItem::IsGroundSpeed, MissionItem::Throttle } }
    };
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

MissionItem::Command MissionItem::command() const
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

MissionItem::Status MissionItem::status() const
{
    return m_status;
}

void MissionItem::setStatus(Status status)
{
    m_status = status;
}

bool MissionItem::isReached() const
{
    return m_reached;
}

void MissionItem::setReached(bool reached)
{
    m_reached = reached;
}

QString MissionItem::parameters() const
{
    QStringList list;
    int enumIndex = MissionItem::staticMetaObject.indexOfEnumerator("Parameter");
    QMetaEnum enumerator = MissionItem::staticMetaObject.enumerator(enumIndex);

    for (Parameter parameter: m_parameters.keys())
    {
        list.append(QString(enumerator.valueToKey(parameter)) + ":" + m_parameters.value(parameter).toString());
    }

    return list.join(";");
}

void MissionItem::setParameters(const QString& arguments)
{
    int enumIndex = MissionItem::staticMetaObject.indexOfEnumerator("Parameter");
    QMetaEnum enumerator = MissionItem::staticMetaObject.enumerator(enumIndex);

    m_parameters.clear();
    for (const QString& pairs: arguments.split(";"))
    {
        QStringList pairList = pairs.split(":");
        if (pairList.count() < 2) continue;

        Parameter param = static_cast<Parameter>(enumerator.keyToValue(qPrintable(pairList.at(0))));
        if (param != UnknownParameter) m_parameters[param] = pairList.at(1);
    }
}

QVariant MissionItem::parameter(Parameter key, const QVariant& parameter)
{
    return m_parameters.value(key, parameter);
}

void MissionItem::setParameter(MissionItem::Parameter key, const QVariant& parameter)
{
    if (::commandParameters[m_command].contains(key)) m_parameters[key] = parameter;
}

void MissionItem::clearParameters()
{
    m_parameters.clear();
}

void MissionItem::clearSuperfluousParameters()
{
    for (Parameter parameter: m_parameters.keys())
    {
        if (::commandParameters[m_command].contains(parameter)) continue;

        m_parameters.remove(parameter);
    }
}
