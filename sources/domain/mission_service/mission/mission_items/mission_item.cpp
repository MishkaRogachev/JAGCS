#include "mission_item.h"

// QT
#include <QDebug>

// Internal
#include "mission.h"

using namespace domain;

MissionItem::MissionItem(Mission* mission, Command command):
    QObject(mission),
    m_mission(mission),
    m_command(command),
    m_pitch(pitch),
    m_yaw(yaw),
    m_radius(radius),
    m_current(false)
{}

Mission* MissionItem::mission() const
{
    return m_mission;
}

unsigned MissionItem::sequence() const
{
    return m_mission->sequence((MissionItem*)this);
}

MissionItem::Command MissionItem::command() const
{
    return m_command;
}

float MissionItem::yaw() const
{
    return m_yaw;
}

float MissionItem::pitch() const
{
    return m_pitch;
}

float MissionItem::radius() const
{
    return m_radius;
}

bool MissionItem::hasPosition() const
{
    return m_command != Continue && m_command != Return;
}

bool MissionItem::isCurrent() const
{
    return m_current;
}

void MissionItem::setCommand(MissionItem::Command command)
{
    if (m_command == command) return;

    m_command = command;
    emit commandChanged(command);
}

void MissionItem::setYaw(float yaw)
{
    if (m_yaw == yaw) return;

    m_yaw = yaw;
    emit yawChanged(yaw);
}

void MissionItem::setPitch(float pitch)
{
    if (m_pitch == pitch) return;

    m_pitch = pitch;
    emit pitchChanged(pitch);
}

void MissionItem::setRadius(float radius)
{
    if (m_radius == radius) return;

    m_radius = radius;
    emit radiusChanged(radius);
}

void MissionItem::setCurrent(bool current)
{
    if (m_current == current) return;

    m_current = current;
    emit currentChanged(current);
}
